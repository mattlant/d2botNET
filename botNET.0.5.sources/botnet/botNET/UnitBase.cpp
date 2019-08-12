//Common include
#include "botnet.h"

//import namespaces
using namespace botNET::Messaging;

//include this header
#include ".\unitbase.h"

//include dependant headers
#include "distance.h"
#include "Game.h"
#include "presetunit.h"
#include "verify.h"
#include "Packet.h"
#include "PacketEventArgs.h"
#include "botnetexceptions.h"

#include "d2client.h"
#include "d2common.h"


namespace botNET
{

namespace Units
{

	UnitBase::UnitBase()
	{
		Game::InGameCheck();
		this->setunitnull();
	}

	UnitBase::~UnitBase()
	{
	}


	UnitBase::UnitBase(UnitAny* u)
	{
		Game::InGameCheck();
		this->setunit(u);
	}

	UnitBase::UnitBase(UnitType type, int classid, int mode) 
	{ 
		Game::InGameCheck();
		UnitBase * temp __gc[] = UnitBase::Find(type, classid, NULL, mode); 
		if(temp->Length > 0)
			this->setunit(temp[0]->unit);
		else
			this->setunitnull();
	}

	UnitBase::UnitBase(PresetUnit* p) 
	{ 
		Game::InGameCheck();
		UnitBase * temp __gc[] = UnitBase::Find(p->Type, p->id, NULL, -1); 
		if(temp->Length > 0)
		{
			for(int i = 0; i < temp->Length; i++)
			{
				if(temp[i]->X == p->X && temp[i]->Y == p->Y)
				{
					this->setunit(temp[i]->unit);
					break;
				}
			}
			if(this->unit)
				return;
		}
		this->setunitnull();
	}

	UnitBase::UnitBase(UnitType type, String* name, int mode) 
	{ 
		Game::InGameCheck();
		UnitBase * temp __gc[] = UnitBase::Find(type, -1, name, mode); 
		if(temp->Length > 0)
			this->setunit(temp[0]->unit);
		else
			this->setunitnull();
	}

	UnitBase::UnitBase(UnitType type, UInt32 UniqueID)
	{
		Game::InGameCheck();
		UnitAny * u = D2CLIENT::GetUnitFromId(UniqueID, type);
		if(u)
			this->setunit(u);
		else
			this->setunitnull();
	}

	void UnitBase::setunit(UnitAny* u)
	{
		if(u)
		{
			this->unit = u;
			this->type = u->dwType;
			this->id = u->dwId;
		}
		else
			this->setunitnull();
	}
	
	void UnitBase::setunitnull()
	{
		this->unit = 0;
		this->type = 6;
		this->id = 0;
	}
	

	bool UnitBase::CompareTo(UnitBase* CompareUnit)
	{
		this->IsValidEx(true);
		Utils::Verify::IsValidArgEx(CompareUnit);

		if(this->unit == CompareUnit->unit)
			return true;
		return false;
	}

	UnitStat UnitBase::get_Stats(void) []
	{
		this->IsValidEx(true);
		UnitStat stats[] = new UnitStat[this->unit->ptStatsList->StatCount2_1];

		d2_Stats * st = unit->ptStatsList->ptStats2;

		for(int i = 0; i < unit->ptStatsList->StatCount2_1; i++)
		{
			stats[i].Index = st->StatIndex;
			stats[i].ID = st->StatID;
			stats[i].Value = st->StatValue;
			st++;
		}

		return stats;
	}

	bool UnitBase::GetState(StateType state) 
	{
		this->IsValidEx(true);
		return D2COMMON::GetUnitState(this->unit, (int)state) > 0;
	}

	int UnitBase::GetStat(StatType stat) 
	{
		this->IsValidEx(true);
		if ( (stat >= 6) && (stat <= 11) )
			return D2COMMON::GetAddedStat(this->unit, stat, 0)>>8;
		else
			return D2COMMON::GetAddedStat(this->unit, stat, 0);
	}

	int UnitBase::GetStat(StatType stat, int sub) 
	{
		this->IsValidEx(true);
		if ( (stat >= 6) && (stat <= 11) )
			return D2COMMON::GetAddedStat(this->unit, stat, sub)>>8;
		else
			return D2COMMON::GetAddedStat(this->unit, stat, sub);
	}

	int UnitBase::GetBaseStat(StatType stat) { 		this->IsValidEx(true);
		return D2COMMON::GetBaseStat(this->unit, stat, 0); }

	int UnitBase::GetBaseStat(StatType stat, int sub) { 		this->IsValidEx(true);
		return D2COMMON::GetBaseStat(this->unit, stat, sub); }

	int UnitBase::GetStat3(StatType stat) { 		this->IsValidEx(true);
		return D2COMMON::GetStatValue3(this->unit, stat, 0); }

	int UnitBase::GetStat3(StatType stat, int sub) { 		this->IsValidEx(true);
		return D2COMMON::GetStatValue3(this->unit, stat, sub); }

	bool UnitBase::IsValid()
	{
		try
		{
			if(!this->unit || this->unit->dwType == 6 || this->unit->dwType != this->type 
				|| this->unit->dwId != this->id || !Game::gIsInGame) return false;
			return true;
		}
		catch(Exception * Ex)
		{
			Ex->get_Message();
			return false;
		}
	}

	bool UnitBase::IsValid(bool refresh)
	{
		if(!this->IsValid())
		{
			if(!refresh || !this->Refresh()) 
			{
				return false;
			}
		}

		return true;
	}

	void UnitBase::IsValidEx()
	{
		if(!this->IsValid()) throw new InvalidUnitException("Unit is invalid", this);
	}

	void UnitBase::IsValidEx(bool refresh)
	{
		if(!this->IsValid(refresh)) throw new InvalidUnitException("Unit is invalid", this);
	}

	bool UnitBase::Refresh()
	{
		UnitAny* u = D2CLIENT::GetUnitFromId(this->id, this->type);
		if(u) 
		{
			this->unit = u;
			return true;
		}
		return false;
	}


	UnitType UnitBase::get_Type() {		return (UnitType)this->type; }

	bool UnitBase::get_Busy() {			this->IsValidEx(true);
		return this->unit->bBusy; }

	AreaLevel UnitBase::get_Area() { 		this->IsValidEx(true);
	return (AreaLevel)D2COMMON::GetLevelIdFromRoom(this->unit->hPath->ptRoom); }

	int UnitBase::get_Act() { 		this->IsValidEx(true);
		return this->unit->dwAct+1; }

	UInt32 UnitBase::get_UniqueID() {	return this->unit->dwId; }

	int UnitBase::get_X() 
	{	
		this->IsValidEx(true);
		if(unit->dwType == 0 || unit->dwType == 1 || unit->dwType == 3)
			return unit->hPath->XPos;
		else
			return unit->hOPath->Xpos;
	}

	int UnitBase::get_Y() 
	{	
		this->IsValidEx(true);
		if(unit->dwType == 0 || unit->dwType == 1 || unit->dwType == 3)
			return unit->hPath->YPos;
		else
			return unit->hOPath->Ypos;
	}

	Point UnitBase::get_Position() 
	{	
		this->IsValidEx(true);
		return Point(this->X, this->Y);
	}

	IntPtr UnitBase::get_Pointer() { this->IsValidEx(true);
		return IntPtr(unit); }

	int UnitBase::get_ClassID() { this->IsValidEx(true);
		return this->unit->dwClassId; }

	String* UnitBase::get_Name() 
	{
		this->IsValidEx(true);
		return Convert::ToString(D2CLIENT::GetNameFromUnit(this->unit));
	}
	

	//Private UnitBase->Find
	UnitBase* UnitBase::Find(int type, int id, String* name, int mode)[]
	{
		::Room1 * room = (*D2CLIENT::PlayerUnit)->hPath->ptRoom;

		ArrayList * unitarr = new ArrayList(); //create empty array so we at least have something to pass back in case nothing found

		for(int i = 0; i < room->NumRooms; i++)
		{
			if(room) { //found a room, so lets get the units in it
				UnitAny * u = room->ptRoomList[i]->ptFirstUnit;
				if(u) 
				{
					do {
						if(type != -1 && (int)u->dwType != type) continue;
						if(id != -1 && (int)u->dwClassId != id) continue;
						if(mode != -1 && (int)u->dwMode != mode) continue;
						if(name != NULL)
						{
							// TODO: Ugly, nasty hack for Player. For whatever reason, GetNameFromUnit returns NULL here
							// but works on the Player.Name property. Weird...
							if (type == UnitType::Player)
							{
								if(String::Compare(u->ptPlayerData->PlayerName, 0, name, 0, name->Length, true)) continue;
							}
							else
							{
								String * uname = Convert::ToString(D2CLIENT::GetNameFromUnit(u));
								if(String::Compare(uname, 0, name, 0, name->Length, true)) continue;
							}
						}
						//Now we have a valid unit to add to the collection
						UnitBase * unittoadd = new UnitBase(u);
						unitarr->Add(unittoadd);
					}while(u = u->ptListNext);
				}
			}
		}

		if(unitarr->Count > 0)
		{ 
			UnitBase* units __gc[] = new UnitBase* [unitarr->Count];
			unitarr->CopyTo(units);
			return units;
		}
		else
			return new UnitBase* [0];
	}

	UnitBase* UnitBase::CreateNew()
	{
		return new UnitBase();
	}

	UnitBase* UnitBase::CreateNew(UnitAny* u)
	{
		return new UnitBase(u);
	}

	void UnitBase::processpackets(Object* sender, PacketEventArgs* e)
	{
		this->v_processpackets(e);
	}

	void UnitBase::v_processpackets(PacketEventArgs* e)
	{

	}

	void UnitBase::ePacketAdd()
	{
		// If our subscription count is 0, we need to add our main subscription to teh packet event
		if(this->mPackReceiveSubscriptionCount == 0)
			Packet::OnAfterGameReceive += new botNET::OnPacketHandler(this, &UnitBase::processpackets);

		// Increment sub count
		this->mPackReceiveSubscriptionCount++;
	}

	void UnitBase::ePacketRemove()
	{
		// If subscription count > 0, then we can decrement
		if(this->mPackReceiveSubscriptionCount > 0)
		{
			this->mPackReceiveSubscriptionCount--;

			// If the above made it 0, then unsubscribe
			if(this->mPackReceiveSubscriptionCount == 0)
				Packet::OnAfterGameReceive -= new botNET::OnPacketHandler(this, &UnitBase::processpackets);
		}
	}
    
	void UnitBase::Dispose()
	{ 
		this->Dispose(true);
		GC::SuppressFinalize(this);
	}

	bool UnitBase::Equals(UnitBase* ub)
	{
		if(!ub)
			return !this->IsValid();

		return this->unit == ub->unit;
	}

	bool UnitBase::op_Equality(UnitBase* lhs, UnitBase* rhs)
	{
		if(!lhs)
		{
			if(!rhs)
                return true;
			else
				return rhs->Equals(lhs);
		}

		return lhs->Equals(rhs);
	}

	bool UnitBase::op_Inequality(UnitBase* lhs, UnitBase* rhs)
	{
		if(!lhs)
		{
			if(!rhs)
                return false;
			else
				return !rhs->Equals(lhs);
		}

		return !lhs->Equals(rhs);
	}

	void UnitBase::Dispose(bool disposing)
	{
		if(!this->disposed)
		{
            disposed = true; 

			try
			{ 
				if(disposing)
				{
				}

			    if(this->mPackReceiveSubscriptionCount > 0)
			    {
				    Packet::OnAfterGameReceive -= new botNET::OnPacketHandler(this, &UnitBase::processpackets);
				    this->mPackReceiveSubscriptionCount = 0;
			    }
			}
			__finally
			{
			}
		}
	}



}

}