#include "botnet.h"
#include ".\player.h"

#include "ItemContainer.h"
#include "npc.h"
#include "npcs.h"
#include "players.h"
#include "rosterplayer.h"

#include "d2client.h"
#include "d2common.h"

namespace botNET
{

namespace Units
{

	Player::Player(void)
        : PlayerNPCBase()
    {
        Init();

        type = UnitType::Player;
    }

    Player::Player(UnitAny* u)
        : PlayerNPCBase(u)
    {
        Init();
    }

    Player::Player(int ClassID)
        : PlayerNPCBase(UnitType::Player, ClassID, -1)
    {
        Init();
    }

    Player::Player(int ClassID, int mode)
        : PlayerNPCBase(UnitType::Player, ClassID, mode)
    {
        Init();
    }

    Player::Player(String* name)
        : PlayerNPCBase(UnitType::Player, name, -1)
    {
        Init();
    }

    Player::Player(String* name, int mode)
        : PlayerNPCBase(UnitType::Player, name, mode)
    {
        Init();
    }

    Player::Player(UInt32 UniqueID)
        : PlayerNPCBase(UnitType::Player, UniqueID)
    {
        Init();
    }

	Player::Player(SerializationInfo* info, StreamingContext* context) 
		: PlayerNPCBase(UnitType::Player, info->GetUInt32("ID")) 
	{
        Init();
	}

	Player::~Player(void)
	{
	}

    void Player::Init()
    {
        mEquipment  = new botNET::Units::Equipment( this );
        mTrade      = new botNET::Units::Trade( this );
    }

    void Player::Dispose(bool disposing)
    {
        if(!this->disposed)
        {
            disposed = true;

            if(disposing)
            {
            }

            __super::Dispose(disposing);
        }
    }

	int Player::get_CharacterLevel()
	{
		return D2COMMON::GetAddedStat(this->unit, 12, 0);
	}

	Player * Player::get_Corpse()
	{
		// TODO: Optimize
		Players * people = new Players();
		for(int i = 0; i < people->Count; i++)
		{
			if(!String::Compare(people->Item[i]->Name, this->Name) && people->Item[i]->Mode == PlayerMode::Dead)
				return people->Item[i];
		}
		return new Player();
	}

    botNET::Units::Equipment* Player::get_Equipment()
    {
        return mEquipment;
    }

	bool Player::get_IsInTown()
	{
		switch(this->Area)
		{
			case AreaLevel::RogueEncampment: 
			case AreaLevel::LutGholein: 
			case AreaLevel::KurastDocks: 
			case AreaLevel::ThePandemoniumFortress: 
			case AreaLevel::Harrogath: 
				return true;

			default:
				return false;
		}
	}

	NPCs* Player::get_Minions()
	{
		RosterPet * r = *D2CLIENT::FirstRosterPet;
		NPCs* units = new NPCs();

		while (r)
		{
			if (r->OwnerId == this->unit->dwId)
			{
				units->Add(new NPC((UInt32)(r->Id)));
			}
			r = r->PetNext;
		}

		return units;
	}

	PlayerMode Player::get_Mode()
    {
        return (PlayerMode)unit->dwMode;
    }

	String* Player::get_Name() 
	{
		return Convert::ToString(this->unit->ptPlayerData->PlayerName);
	}

	NPC * Player::get_Mercenary()
	{
		const int mercIDs __gc[] = {271, 338, 359, 561};
		
		/*NPCs * people = new NPCs(mercIDs);
		for(int i = 0; i < people->Count; i++)
		{
			if(people->Item[i]->Parent->IsValid())
			{
				Player* p = new Player(people->Item[i]->Parent->unit);
				if(!String::Compare(p->Name, this->Name))
					return people->Item[i];
			}
		}
		return new NPC();*/

		//r1ch: Changed to this method, previous was sometimes unreliable for some reason. Perhaps merc being out of range/stuck somewhere.
		NPCs *mercs = this->Minions->GetByClassID (mercIDs);
		if (mercs->Count == 1)
			return mercs->Item[0];

		return new NPC();
	}

	botNET::Units::Trade* Player::get_Trade()
	{
        return mTrade;
	}

	UnitBase* Player::CreateNew()
	{
		return new Player();
	}

	UnitBase* Player::CreateNew(UnitAny* u)
	{
		return new Player(u);
	}

	bool Player::IsInParty(RosterPlayer * player)
	{
		if(player->PartyID == 0xFFFFFFFF)
            return false;

        return ((RosterPlayer::Get(this->unit->dwId))->PartyID == player->PartyID);
	}

	void Player::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(Player));
		info->AddValue("ID", this->UniqueID);
	}

}

}