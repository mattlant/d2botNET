#include "botnet.h"
#include ".\npc.h"

#include "ItemContainer.h"
#include "d2client.h"
#include "unitevents.h"
#include "packet.h"
#include "game.h"

namespace botNET
{

namespace Units
{

	NPC::NPC(void) : PlayerNPCBase(){ this->type = UnitType::NPC; }
	NPC::NPC(UnitAny* u) : PlayerNPCBase(u){}
	NPC::NPC(int ClassID) : PlayerNPCBase(UnitType::NPC, ClassID, -1) {}
	NPC::NPC(int ClassID, int mode) : PlayerNPCBase(UnitType::NPC, ClassID, mode) {}
	NPC::NPC(String* name) : PlayerNPCBase(UnitType::NPC, name, -1) {}
	NPC::NPC(String* name, int mode) : PlayerNPCBase(UnitType::NPC, name, mode) {}
	NPC::NPC(UInt32 UniqueID) : PlayerNPCBase(UnitType::NPC, UniqueID) {}
	NPC::NPC(SerializationInfo* info, StreamingContext* context) : PlayerNPCBase(UnitType::NPC, info->GetUInt32("ID")) {}


	NPC::~NPC(void)
	{
	}

	void NPC::Dispose(bool disposing)
	{
		if(!this->disposed)
		{
            disposed = true;

			try
			{
				if(disposing)
				{
				}

                // cleanup here
			}
			__finally
			{
				__super::Dispose(disposing);
			}
		}
	}

	String* NPC::get_Name() 
	{
		this->IsValidEx(true);
		return Convert::ToString(D2CLIENT::GetNameFromUnit(this->unit));
	}

  	botNET::Units::Store* NPC::get_Store()
	{
        if( !mStore )
        {
            // check if this unit can have a store
            // if not mStore = new botNET::Units::Store();
            mStore = new botNET::Units::Store( this );
        }

        return mStore;
    }

	NPCMode NPC::get_Mode() { return (NPCMode)unit->dwMode; }

	MonsterType NPC::get_MonsterType()
	{ 
		//Boss 08 with none b4
		//Super 0A
		//Regular Unique with something before
		//minions 10
		//Champs 0C
		this->IsValidEx(true);

		if(this->unit->ptMonsterData->monsterType == 0x08)
		{
			if(this->unit->ptMonsterData->monsterTypePre == 0x0)
				return MonsterType::Boss;
			else
				return MonsterType::Unique;
		}
		if(this->unit->ptMonsterData->monsterType == 0x0A)
			return MonsterType::SuperUnique;
		if(this->unit->ptMonsterData->monsterType == 0x0C)
			return MonsterType::Champion;
		if(this->unit->ptMonsterData->monsterType == 0x00)
			return MonsterType::Regular;


		return MonsterType::Unknown; 
	}

	EnchantmentType NPC::get_Enchantments() []
	{	
		this->IsValidEx(true);

		for (int i = 0; i < 10; i++)
		{
			if(!this->unit->ptMonsterData->Enchants[i])
				break;
		}
		EnchantmentType enchants __gc[] = new EnchantmentType[i+1];
		for(int j = 0; j < i+1; j++)
			enchants[j] = (EnchantmentType)this->unit->ptMonsterData->Enchants[j];

		return enchants; 
	}

	bool NPC::HasEnchantment(EnchantmentType enchant)
	{	
		this->IsValidEx(true);

		for (int i = 0; i < 10; i++)
		{
			if((EnchantmentType)unit->ptMonsterData->Enchants[i] == enchant)
				return true;
		}
		return false; 
	}

	UnitBase* NPC::CreateNew()
	{
		return new NPC();
	}

	UnitBase* NPC::CreateNew(UnitAny* u)
	{
		return new NPC(u);
	}

	PlayerNPCBase* NPC::get_Parent()
	{	
		this->IsValidEx(true);

		RosterPet *pets = *D2CLIENT::FirstRosterPet;
		while(pets)
		{
			if(pets->Id == unit->dwId && pets->OwnerId == (*D2CLIENT::PlayerUnit)->dwId) // unit owned by us :)
				return new PlayerNPCBase((UnitAny*)*D2CLIENT::PlayerUnit);

			pets=pets->PetNext;
		} 

		return new PlayerNPCBase();
	}

	botNET::BaseStats::MonStats* NPC::get_BaseStats_Monstats()
	{
		this->IsValidEx(true);
		return botNET::BaseStats::MonStats::Get(this->ClassID);
	}

	botNET::BaseStats::MonStats2* NPC::get_BaseStats_Monstats2()
	{
		this->IsValidEx(true);
		return botNET::BaseStats::MonStats2::Get(this->ClassID);
	}

	void NPC::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(NPC));
		info->AddValue("ID", this->UniqueID);
	}

	void NPC::add_OnSetTarget(OnUnitSetTargetHandler* h)
	{
		this->ePacketAdd();
		this->eOnSetTarget += h;
	}

	void NPC::remove_OnSetTarget(OnUnitSetTargetHandler* h)
	{
		this->ePacketRemove();
		this->eOnSetTarget -= h;
	}

	void NPC::raise_OnSetTarget(Object* sender, SetTargetUnitEventArgs* h)
	{
		if(this->eOnSetTarget)
			this->eOnSetTarget(this, h);
	}


	void NPC::v_processpackets(PacketEventArgs* e)
	{
		Packet* packet = e->Packet;
		switch(e->Packet->_packet[0])
		{
		case 0x68:
			if(e->Packet->GetUInt32(1) == this->id)
			{
				this->raise_OnSetTarget(this, new SetTargetUnitEventArgs(e->Packet));
			}
		}
		__super::v_processpackets(e);

	}

}

}