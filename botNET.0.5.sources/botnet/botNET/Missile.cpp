#include "botnet.h"
#include ".\missile.h"

#include "playernpcbase.h"

namespace botNET
{

namespace Units
{


	Missile::Missile(void) : UnitBase(){ this->type = UnitType::Missile; }
	Missile::Missile(UnitAny* u) : UnitBase(u){}
	Missile::Missile(int ClassID) : UnitBase(UnitType::Missile, ClassID, -1) {}
	Missile::Missile(UInt32 UniqueID) : UnitBase(UnitType::Missile, UniqueID) {}
	Missile::Missile(SerializationInfo* info, StreamingContext* context) : UnitBase(UnitType::Missile, info->GetUInt32("ID")) {}


	Missile::~Missile(void)
	{
	}

	void Missile::Dispose(bool disposing)
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

	PlayerNPCBase* Missile::get_Target()
	{
		this->IsValidEx(true);
		return new PlayerNPCBase(this->unit->hPath->ptTarget);
	}

	int Missile::get_Mode() { 		this->IsValidEx(true);
		return unit->dwMode; }

	UnitBase* Missile::CreateNew()
	{
		return new Missile();
	}

	UnitBase* Missile::CreateNew(UnitAny* u)
	{
		return new Missile(u);
	}

	botNET::BaseStats::Missiles* Missile::get_BaseStats_Missiles()
	{
		this->IsValidEx(true);
		return botNET::BaseStats::Missiles::Get(this->ClassID);
	}

	void Missile::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(Missile));
		info->AddValue("ID", this->UniqueID);
	}

}

}