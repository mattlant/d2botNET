#include "botnet.h"
#include ".\presetunit.h"
#include ".\log.h"

#include "eventargs.h"
#include "Game.h"
#include "room.h"

#include "d2client.h"
#include "d2common.h"

using namespace botNET::Mapping;

namespace botNET {
namespace Units
{
	/////////////////////////////////////////////////////////////////////
	//Preset Unit Implementation
	/////////////////////////////////////////////////////////////////////
	PresetUnit::PresetUnit(UnitType Type, UInt32 ID, int X, int Y, AreaLevel AreaId)
	{
		type = Type;
		id = ID;
		x = X;
		y = Y;
		area = AreaId;
	}

	PresetUnit::~PresetUnit(void)
	{

	}

	PresetUnit * PresetUnit::Get()[]
	{
		return PresetUnit::Get((AreaLevel)NULL, (UnitType)NULL, (UInt32)NULL, NULL);
	}

	PresetUnit * PresetUnit::Get(AreaLevel AreaId)[]
	{
		return PresetUnit::Get(AreaId, (UnitType)NULL, NULL, NULL);
	}

	PresetUnit * PresetUnit::Get(AreaLevel AreaId, UnitType Type)[]
	{
		return PresetUnit::Get(AreaId, Type, NULL, NULL);
	}

	PresetUnit * PresetUnit::Get(AreaLevel AreaId, UnitType Type, UInt32 ID)[]
	{
		return PresetUnit::Get(AreaId, Type, ID, NULL);
	}

	PresetUnit * PresetUnit::Get(AreaLevel AreaId, UnitType Type, UInt32 ID, int RoomID __gc[])[]
	{
		int area = AreaId;
		DWORD type = Type;
		DWORD id = ID;
		DWORD rarrlength = 0;

		if(RoomID != NULL)
			if(RoomID->Count)
				rarrlength = RoomID->Length;

		::d2_PresetUnit *punit;

		Hashtable * presets = new Hashtable();

		::Room1 * room1;

		bool hasopened = false;

		int c = 0;

		//iterate thru all rooms in given area
		RoomOther *room = (*D2CLIENT::PlayerUnit)->hPath->ptRoom->ptRoomOther->ptDrlgLevel->pRoomOtherFirst;

		DrlgLevel * level = (*D2CLIENT::PlayerUnit)->ptAct->ptMisc->pFirstLevel;

		do {
			if(level->LevelNo == area) break;
		} while(level = level->pNext);

		if(level) room = level->pRoomOtherFirst;
		else return new PresetUnit * [0];
		if(!room) return new PresetUnit * [0];

		do
		{

			if(!room->pRoom) {
				EnterCriticalSection(&RoomCritSect);
				hasopened = true;
				try
				{
					D2COMMON::AddRoomData(room->ptDrlgLevel->pDrlg->pAct, room->ptDrlgLevel->LevelNo, 
						room->xPos, 
						room->yPos, 
						*D2CLIENT::PlayerUnit);
				}
				catch (...)
				{
					botNET::Diagnostics::Log::WriteLine("Exception in PresetUnit::Get -> AddRoomData");
					LeaveCriticalSection (&RoomCritSect);
					throw;
				}
			}

			try
			{
				room1 = room->pRoom;
				if(!room1) goto do_exit;

				punit = room->pPresetUnits;
				if(!punit) goto do_exit;

				do {
					if(type) 
						if(punit->nUnitType != type) 
							continue;
					if(id) 
						if(punit->nTxtFileNo != id) 
							continue;

					if(rarrlength > 0)
					{
						
						bool found = false;
						for(unsigned int i = 0; i < rarrlength; i++)
						{
							//int i = (int)o;
							if(room->pPresetType2info->roomNum == RoomID[i]) {
								found = 1;
								break;
							}
						}
						if(!found) continue;
						
					}

					PresetUnit * pu = new PresetUnit((UnitType)punit->nUnitType, punit->nTxtFileNo, 
						punit->xPos + room->xPos*5, punit->yPos + room->yPos*5, (AreaLevel)room->ptDrlgLevel->LevelNo);
	
					try{
						presets->Add(pu->ToString(), pu);
					}
					catch(Exception *)
					{
					}
					__finally
					{
						//Game::Print("PresetCollision");
					}

				} while(punit = punit->pNext);
				
do_exit: ;


			}
			catch(Exception * ex)
			{
				throw ex;
			}
			__finally
			{
				if(hasopened) 
				{
					//if(!room->pRoom->ptFirstUnit)
					D2COMMON::RemoveRoomData(room->ptDrlgLevel->pDrlg->pAct, room->ptDrlgLevel->LevelNo,
						room->xPos, room->yPos, *D2CLIENT::PlayerUnit);
					LeaveCriticalSection(&RoomCritSect);
					hasopened = false;
				}
			}


		} while(room = room->pNext);

		PresetUnit * pres __gc[] = new PresetUnit * [presets->Count];
		presets->Values->CopyTo(pres, 0);
		return pres;
		
	}


	UnitType PresetUnit::get_Type()
	{
		return type;
	}

	int PresetUnit::get_ClassID()
	{
		return id;
	}

	int PresetUnit::get_X()
	{
		return x;
	}

	int PresetUnit::get_Y()
	{
		return y;
	}

	AreaLevel PresetUnit::get_Area()
	{
		return area;
	}

	System::Drawing::Point PresetUnit::get_Position() 
	{	
		return System::Drawing::Point(x, y);
	}


	String* PresetUnit::ToString()
	{
		return String::Concat(Convert::ToString(area), ((int)type).ToString(), id.ToString(), x.ToString(), y.ToString());
	}

	int PresetUnit::GetHashCode()
	{
		return ((area << 8) | id) + ((type * 7) % 3) + (type * 2) + ((x << 16) | y) * 3 +(X % 4) + (x * 5) + (y % 6) + (y * 7);
	}

	bool PresetUnit::Equals(Object* obj)
	{
		return false;
		if (obj == 0 || GetType() != obj->GetType()) return false;
		PresetUnit* pre = dynamic_cast<PresetUnit*>(obj);
		return (pre->x == this->x && pre->y == this->y && pre->type == this->type 
			&& pre->id == this->id && pre->area == this->area);
	}

	bool PresetUnit::op_Equality(PresetUnit* lhs, PresetUnit* rhs)
	{
		return (lhs->x == rhs->x && lhs->y == rhs->y && lhs->type == rhs->type 
			&& lhs->id == rhs->id && lhs->area == rhs->area);
	}

	bool PresetUnit::op_Inequality(PresetUnit* lhs, PresetUnit* rhs)
	{
		return (lhs->x != rhs->x || lhs->y != rhs->y || lhs->type != rhs->type 
			|| lhs->id != rhs->id || lhs->area != rhs->area);
	}
}
}