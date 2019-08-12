#include "botnet.h"
#include ".\rosterplayer.h"
#include ".\player.h"
#include "d2client.h"


namespace botNET
{
namespace Units
{



	RosterPlayer::RosterPlayer(Roster * ros)
	{

		r = ros;
		id = r->PlayerId;
	}

	RosterPlayer * RosterPlayer::Get()[]
	{
		Roster * r = *D2CLIENT::FirstRosterPlayer;

		ArrayList * al = new ArrayList();

		while(r)
		{
			al->Add(new RosterPlayer(r));
			r = r->ptNext;
		}

		if(al->Count > 0)
		{ 
			RosterPlayer * pls __gc[] = new RosterPlayer * [al->Count];
			al->CopyTo(pls);
			return pls;
		}
		else
			return new RosterPlayer * [0];
	}

	RosterPlayer * RosterPlayer::Get(String * Name)
	{
		Roster * r = *D2CLIENT::FirstRosterPlayer;
		while(r)
		{
			if(!String::Compare(Convert::ToString(r->Name)->ToLower(), Name->ToLower()))
				return new RosterPlayer(r);
			r = r->ptNext;
		}
		return NULL;
	}

	RosterPlayer * RosterPlayer::Get(UInt32 ID)
	{
		Roster * r = *D2CLIENT::FirstRosterPlayer;
		while(r)
		{
			if(r->PlayerId == ID)
				return new RosterPlayer(r);
			r = r->ptNext;
		}
		return NULL;
	}

	String * RosterPlayer::get_Name() 
	{
		return Convert::ToString(r->Name);
	}

	bool RosterPlayer::IsValid() 
	{
		return (id == r->PlayerId ? true : false);
	}

	void RosterPlayer::IsValidEx(void) 
	{
		if(id != r->PlayerId)
			throw new ApplicationException("Not Valid");
	}

	UInt32 RosterPlayer::get_UniqueID() 
	{
		return r->PlayerId;
	}

	int RosterPlayer::get_ClassID() 
	{
		return r->ClassId;
	}

	UnitType RosterPlayer::get_Type()
	{
		return UnitType::Player;
	}

	AreaLevel RosterPlayer::get_Area() 
	{
		Player * fplayer = new Player((Int32)r->PlayerId);
		
		if(!(fplayer->IsValid()))
			return (AreaLevel)r->AreaId;

		return fplayer->Area;
	}

	int RosterPlayer::get_X() 
	{
		Player * fplayer = new Player((Int32)r->PlayerId);
		
		if(!fplayer->IsValid())
			return r->Xpos;

		return fplayer->X;
	}
    
	int RosterPlayer::get_Y() 
	{
		Player * fplayer = new Player((Int32)r->PlayerId);
		
		if(!fplayer->IsValid())
			return r->Ypos;		
					
		return fplayer->Y;
	}

	System::Drawing::Point RosterPlayer::get_Position() 
	{	
		return System::Drawing::Point(this->X, this->Y);
	}

	UInt16 RosterPlayer::get_PartyID() 
	{
		return r->PartyID;
	}

	UInt16 RosterPlayer::get_CharacterLevel() 
	{
		return r->CharLevel;
	}

	bool RosterPlayer::get_IsValidData()
	{
		return !((r->Ypos == 0 || r->Xpos == 0 || r->AreaId == 0) && (!((new Player((Int32)r->PlayerId))->IsValid())));
	}

	bool RosterPlayer::get_IsSynchronized()
	{
		return (!((new Player((Int32)r->PlayerId))->IsValid()));
	}
}
}