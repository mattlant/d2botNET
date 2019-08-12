#include "botnet.h"
#include ".\playernpcbase.h"

#include "item.h"
#include "items.h"
#include "room.h"


#include "d2client.h"
#include "d2common.h"

namespace botNET
{

namespace Units
{

	PlayerNPCBase::PlayerNPCBase() : UnitBase() {}
	PlayerNPCBase::PlayerNPCBase(UnitAny* u) : UnitBase(u) {}
	PlayerNPCBase::PlayerNPCBase(UnitType type, int ClassID, int mode) : UnitBase(type, ClassID, mode) {}
	PlayerNPCBase::PlayerNPCBase(UnitType type, String* name, int mode) : UnitBase(type, name, mode) {}
	PlayerNPCBase::PlayerNPCBase(UnitType type, UInt32 UniqueID) : UnitBase(type, UniqueID) {}

    PlayerNPCBase::~PlayerNPCBase(void)
	{
	}

	void PlayerNPCBase::Overhead(String* mesg)
	{
		this->IsValidEx(true);
		char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(mesg).ToPointer());

		ChatMsg msg;
		msg.Identifier = 0x26;
		msg.Unk1 = 0x00;
		msg.Style = 0;
		msg.MessageType = 5;
		msg.UnitId = this->unit->dwId;
		msg.Color = 0;
		msg.Name[0] = 0;

		//r1ch: strcpy -> strncpy
		strncpy (msg.Message, pStr, sizeof(msg.Message)-1);
		msg.Message[sizeof(msg.Message)-1] = 0;

		D2CLIENT::PrintMessage(&msg);

		Marshal::FreeHGlobal(pStr);

	}

	int PlayerNPCBase::get_HP() 
	{ 		
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 6, 0) >> 8;
	}

	int PlayerNPCBase::get_HPMax() 
	{			
		this->IsValidEx(true);
		return D2COMMON::GetMaxHealth(unit) >> 8;	
	}

	int PlayerNPCBase::get_HPMaxBase() 
	{			
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 7, 0) >> 8;	
	}

	int PlayerNPCBase::get_MP() 
	{ 		
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 8, 0) >> 8;	
	}

	int PlayerNPCBase::get_MPMax() 
	{			
		this->IsValidEx(true);
		return D2COMMON::GetMaxMana(unit) >> 8;	
	}

	int PlayerNPCBase::get_MPMaxBase() 
	{			
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 9, 0) >> 8;	
	}

	int PlayerNPCBase::get_Stamina() 
	{ 		
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 10, 0) >> 8; 
	}

	int PlayerNPCBase::get_StaminaMax() 
	{ 		
		this->IsValidEx(true);
		return D2COMMON::GetMaxStamina(unit) >> 8; 
	}

	int PlayerNPCBase::get_StaminaMaxBase() 
	{ 		
		this->IsValidEx(true);
		return D2COMMON::GetAddedStat(unit, 11, 0) >> 8;
	}

	::botNET::Mapping::Room* botNET::Units::PlayerNPCBase::get_CurrentRoom()
	{
		this->IsValidEx(true);
		return new botNET::Mapping::Room(this->unit->hPath->ptRoom->ptRoomOther);
	}

	void PlayerNPCBase::Dispose(bool disposing)
	{
		if(!this->disposed)
		{
            disposed = true;

			try
			{
				if(disposing)
				{
				}
			}
			__finally
			{
				__super::Dispose(disposing);
			}
		}
	}
}

}