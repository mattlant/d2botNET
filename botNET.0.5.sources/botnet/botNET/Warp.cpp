#include "botnet.h"
#include ".\warp.h"
#include "presetunit.h"

namespace botNET
{

namespace Units
{


	Warp::Warp(void) : UnitBase(){ this->type = UnitType::Warp; }
	Warp::Warp(PresetUnit* p) : UnitBase(p){}
	Warp::Warp(UnitAny* u) : UnitBase(u){}
	Warp::Warp(int ClassID) : UnitBase(UnitType::Warp, ClassID, -1) {}
	Warp::Warp(UInt32 UniqueID) : UnitBase(UnitType::Warp, UniqueID) {}
	Warp::Warp(SerializationInfo* info, StreamingContext* context) : UnitBase(UnitType::Warp, info->GetUInt32("ID")) {}

	int Warp::get_Mode() { 		this->IsValidEx(true);
		return unit->dwMode; }

	Warp::~Warp(void)
	{
	}

	void Warp::Dispose(bool disposing)
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

	UnitBase* Warp::CreateNew()
	{
		return new Warp();
	}

	UnitBase* Warp::CreateNew(UnitAny* u)
	{
		return new Warp(u);
	}

	void Warp::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(Warp));
		info->AddValue("ID", this->UniqueID);
	}


}

}