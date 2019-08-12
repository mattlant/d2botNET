#include "botnet.h"
#include ".\gameobject.h"
#include "rosterplayer.h"
#include "presetunit.h"
#include "d2client.h"

namespace botNET
{

namespace Units
{


	GameObject::GameObject(void) : UnitBase(){ this->type = UnitType::GameObject; }
	GameObject::GameObject(UnitAny* u) : UnitBase(u){}
	GameObject::GameObject(PresetUnit* p) : UnitBase(p){}
	GameObject::GameObject(int ClassID) : UnitBase(UnitType::GameObject, ClassID, -1) {}
	GameObject::GameObject(int ClassID, int mode) : UnitBase(UnitType::GameObject, ClassID, mode) {}
	GameObject::GameObject(String* name) : UnitBase(UnitType::GameObject, name, -1) {}
	GameObject::GameObject(String* name, int mode) : UnitBase(UnitType::GameObject, name, mode) {}
	GameObject::GameObject(UInt32 UniqueID) : UnitBase(UnitType::GameObject, UniqueID) {}
	GameObject::GameObject(SerializationInfo* info, StreamingContext* context) : UnitBase(UnitType::GameObject, info->GetUInt32("ID")) {}


	GameObject::~GameObject(void)
	{
	}

	void GameObject::Dispose(bool disposing)
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

	String* GameObject::get_Name() 
	{
		this->IsValidEx(true);

		return Convert::ToString(D2CLIENT::GetNameFromUnit(this->unit));
	}

	GameObjectMode GameObject::get_Mode() { 		this->IsValidEx(true);
		return (GameObjectMode)unit->dwMode; }

	AreaLevel GameObject::get_DestinationArea()
	{
		this->IsValidEx(true);
		return (AreaLevel)this->unit->ptObjectData->Destination;
	}

	RosterPlayer* GameObject::get_Parent()
	{
		this->IsValidEx(true);
		return RosterPlayer::Get(Convert::ToString(unit->ptObjectData->parent));
	}

	Byte GameObject::get_Flags()
	{
		this->IsValidEx(true);
		return this->unit->ptObjectData->Flags;
	}

	bool GameObject::Interact(AreaLevel destination)
	{
		this->IsValidEx(true);
		if(!(*D2CLIENT::IsNotInteractedWithWP) && *D2CLIENT::InteractedWPUniqueID == unit->dwId)
		{
			D2CLIENT::PrePacket2(0x49, *D2CLIENT::InteractedWPUniqueID, destination);
			return true;
		}
		throw new ApplicationException("Problem using waypoint. Maybe you are not interacted with waypoint?");
	}

	UnitBase* GameObject::CreateNew()
	{
		return new GameObject();
	}

	UnitBase* GameObject::CreateNew(UnitAny* u)
	{
		return new GameObject(u);
	}

	botNET::BaseStats::Objects* GameObject::get_BaseStats_Objects()
	{
		this->IsValidEx(true);
		return botNET::BaseStats::Objects::Get(this->ClassID);
	}

	void GameObject::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(GameObject));
		info->AddValue("ID", this->UniqueID);
	}
}

}