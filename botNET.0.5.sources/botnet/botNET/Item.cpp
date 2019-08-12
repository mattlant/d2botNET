#include "botnet.h"
#include ".\item.h"

#include ".\playernpcbase.h"

#include ".\d2common.h"
#include ".\d2client.h"

namespace botNET
{

namespace Units
{

	Item::Item(void) : UnitBase(){ this->type = UnitType::Item; }
	Item::Item(UnitAny* u) : UnitBase(u){}
	Item::Item(int ClassID) : UnitBase(UnitType::Item, ClassID, -1) {}
	Item::Item(String* code) : UnitBase(UnitType::Item, code, -1) {}
	Item::Item(UInt32 UniqueID) : UnitBase(UnitType::Item, UniqueID) {}
	Item::Item(SerializationInfo* info, StreamingContext* context) : UnitBase(UnitType::Item, info->GetUInt32("ID")) {}

	Item::~Item(void)
	{
	}

	void Item::Dispose(bool disposing)
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

	String* Item::get_Name() 
	{
		this->IsValidEx(true);
		return Convert::ToString(D2CLIENT::GetNameFromUnit(this->unit));
	}

	ItemMode Item::get_Mode() { 		this->IsValidEx(true);
		return (ItemMode)unit->dwMode; }

	int Item::GetPrice(PriceType pricetype, int NPCClassID) 
	{
		this->IsValidEx(true);
		return D2COMMON::GetUnitPrice(*D2CLIENT::PlayerUnit, (UnitItem*)this->unit, 0, 
			*D2CLIENT::ItemPriceGameInfoUnk, NPCClassID, (int)pricetype);
	}

	String* Item::get_FullName()[] 
	{
		this->IsValidEx(true);
		wchar_t str [0x100];
		D2CLIENT::GetItemNameString((UnitItem*)this->unit, str, 0x100);

		String* name[] = Convert::ToString(str)->Split((S"\n")->ToCharArray());
		// A multiline full name is in reverse line order
		Array::Reverse( name);
		return name;
	}

	PlayerNPCBase * Item::get_Owner()
	{
		this->IsValidEx(true);
		//TODO: get item owner
		return new PlayerNPCBase();
	}
	
	String* Item::get_AllStats()[]
	{
		this->IsValidEx(true);
		wchar_t str [0x400];

		D2CLIENT::GetItemStatsString((UnitItem*)this->unit, str, 0x400, 1, 0, 0xAB, 0x40, 1);

		String* desc[] = Convert::ToString(str)->Split((S"\n")->ToCharArray());

		// When split the last split token is often blank.  Remove it.
		int lastLen = desc->Length - 1;
		if( desc[ lastLen]->Length == 0){
			String* trimmed[] = new String*[ lastLen];
			Array::Copy( desc, trimmed, lastLen);

			// List is also reversed
			Array::Reverse( trimmed);
			return trimmed;
		}

		// No trimming needed
		// List is also reversed
		Array::Reverse( desc);
		return desc;
	}

	EquipmentLocation Item::get_EquippedLocation() 
	{
		this->IsValidEx(true);
		if(unit->ptItemData->Location == 1)
			return (EquipmentLocation)unit->ptItemData->EquippedLocation;
		else
			return EquipmentLocation::NotEquipped;
	}

	ItemLocation Item::get_Location() 
	{
		this->IsValidEx(true);

		switch(this->unit->dwMode)
		{
		case ItemMode::OnCursor:
			return ItemLocation::Cursor;
		case ItemMode::Dropping:
			return ItemLocation::Dropping;
		case ItemMode::OnGround:
			return ItemLocation::Ground;
		case ItemMode::Socketed:
			return ItemLocation::Socket;
		default:
            return (ItemLocation)unit->ptItemData->Location;
		}
	}

	UInt32 Item::get_UnitFlags() 
	{
		this->IsValidEx(true);
		return unit->dwFlags; 
	}

	UInt32 Item::get_UnitFlags2() 
	{
		this->IsValidEx(true);
		return unit->dwFlags2; 
	}

	UInt32 Item::get_ItemFlags() 
	{
		this->IsValidEx(true);
		return this->unit->ptItemData->dwFlags;
	}

	bool Item::HasUnitFlag(UInt32 Flag)
	{
		this->IsValidEx(true);
		return (this->unit->dwFlags & (DWORD)Flag) > 0;
	}

	bool Item::HasUnitFlag2(UInt32 Flag)
	{
		this->IsValidEx(true);
		return (this->unit->dwFlags2 & (DWORD)Flag) > 0;
	}

	bool Item::HasItemFlag(ItemFlag Flag)
	{
		this->IsValidEx(true);
		return (this->unit->ptItemData->dwFlags & (DWORD)Flag) > 0;
	}

	ItemType Item::get_ItemType() 
	{	
		this->IsValidEx(true);
		BYTE type = D2COMMON::GetItemBinFromClass(unit->dwClassId)->Type;
		return ((botNET::ItemType)((int)type)); 
	}

	String* Item::get_Code() 
	{
		this->IsValidEx(true);
		return (Convert::ToString(D2COMMON::GetItemBinFromClass(unit->dwClassId)->Codes)->Split((S" ")->ToCharArray()))[0];
	}

	ItemClass Item::get_ItemClass() 
	{
		this->IsValidEx(true);

		String * codes __gc[] = (Convert::ToString(D2COMMON::GetItemBinFromClass(unit->dwClassId)->Codes)->Split((S" ")->ToCharArray()));

		if(codes->Count == 2) // classless -- amulets return { "amu", "" }
			return ItemClass::None;

		if(!String::Compare(codes[0], codes[1]))
			return ItemClass::Normal;
		if(!String::Compare(codes[0], codes[2]))
			return ItemClass::Exceptional;
		if(!String::Compare(codes[0], codes[3]))
			return ItemClass::Elite;

		return ItemClass::None;
	}

	String* Item::get_Prefix() 
	{	
		this->IsValidEx(true);
		return Convert::ToString(D2COMMON::GetItemMagicalMods(unit->ptItemData->Prefix)); 
	}

	String* Item::get_Suffix() 
	{	
		this->IsValidEx(true);
		return Convert::ToString(D2COMMON::GetItemMagicalMods(unit->ptItemData->Suffix)); 
	}

	QualityType Item::get_Quality() 
	{ 
		this->IsValidEx(true);
		return (QualityType)unit->ptItemData->Quality1;
	}


	Byte Item::get_XSize() { 		this->IsValidEx(true);
		return D2COMMON::GetItemBinFromClass(unit->dwClassId)->SizeX; }
	Byte Item::get_YSize() { 		this->IsValidEx(true);
		return D2COMMON::GetItemBinFromClass(unit->dwClassId)->SizeY; }

	UnitBase* Item::CreateNew()
	{
		return new Item();
	}

	UnitBase* Item::CreateNew(UnitAny* u)
	{
		return new Item(u);
	}

	botNET::BaseStats::Items* Item::get_BaseStats_Items()
	{
		this->IsValidEx(true);
		return botNET::BaseStats::Items::Get(this->ClassID);
	}


	void Item::GetObjectData(SerializationInfo* info, StreamingContext context)
	{
		info->SetType(__typeof(Item));
		info->AddValue("ID", this->UniqueID);
	}

}

}