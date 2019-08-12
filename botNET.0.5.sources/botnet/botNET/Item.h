#pragma once

#include "unitbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{

namespace Units
{
	// TODO: Add Items* item.SocketItems property

	public __gc class PlayerNPCBase;

	public __gc class Item : public Units::UnitBase, public ISerializable
	{
	public:
		Item(void);
		Item(int ClassID);
		Item(String* code);
		Item(UInt32 UniqueID);
		Item(SerializationInfo* info, StreamingContext* context);
		~Item(void);

		__property String * get_Name();
		__property ItemMode get_Mode();

		int GetPrice(PriceType pricetype, int NPCClassID);
		__property String* get_FullName()[];
		__property String* get_AllStats()[];
		__property EquipmentLocation get_EquippedLocation();
		__property ItemLocation get_Location();
		__property PlayerNPCBase * get_Owner();
		__property UInt32 get_UnitFlags();
		__property UInt32 get_UnitFlags2();
		__property UInt32 get_ItemFlags();
		bool HasUnitFlag(UInt32 flag);
		bool HasUnitFlag2(UInt32 flag);
		bool HasItemFlag(ItemFlag flag);
		__property ItemType get_ItemType();
		__property String * get_Code();
		__property ItemClass get_ItemClass();
		__property String * get_Prefix();
		__property String * get_Suffix();
		__property QualityType get_Quality();

		__property Byte get_XSize();
		__property Byte get_YSize();

		__property botNET::BaseStats::Items* get_BaseStats_Items();

		void GetObjectData(SerializationInfo* info, StreamingContext context);

	public private:
		Item(UnitAny* u);
		virtual UnitBase* CreateNew(UnitAny* u);
		virtual UnitBase* CreateNew();

    protected:
        virtual void Dispose(bool disposing);

	private:
		bool disposed;
	};

}

}
