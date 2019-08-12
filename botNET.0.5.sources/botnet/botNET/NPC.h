#ifndef NPCUNIT_H
#define NPCUNIT_H

#include "playernpcbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{

namespace Units
{
    // forward declarations
    public __gc class Store;

public __gc class NPC : public botNET::Units::PlayerNPCBase, public ISerializable
	{
	public:
		NPC(void);
		NPC(int ClassID);
		NPC(int ClassID, int mode);
		NPC(String* name);
		NPC(String* name, int mode);
		NPC(UInt32 UniqueID);
		NPC(SerializationInfo* info, StreamingContext* context);
		~NPC(void);

		__property botNET::Units::Store* get_Store(void);

        __property String * get_Name();
		__property NPCMode get_Mode();
		__property MonsterType get_MonsterType();
		__property EnchantmentType get_Enchantments()[];
		bool HasEnchantment(EnchantmentType enchant);
		__property PlayerNPCBase * get_Parent();
		__property botNET::BaseStats::MonStats* get_BaseStats_Monstats();
		__property botNET::BaseStats::MonStats2* get_BaseStats_Monstats2();

		void GetObjectData(SerializationInfo* info, StreamingContext context);

		__event void add_OnSetTarget( OnUnitSetTargetHandler* h);
		__event void remove_OnSetTarget( OnUnitSetTargetHandler* h) ;
		__event void raise_OnSetTarget(Object* sender, SetTargetUnitEventArgs* e);

	public private:
		NPC(UnitAny* u);
		virtual UnitBase* CreateNew(UnitAny* u);
		virtual UnitBase* CreateNew();

    protected:

		virtual void Dispose(bool disposing);

		void v_processpackets(botNET::Messaging::PacketEventArgs* e);
		OnUnitSetTargetHandler* eOnSetTarget;

        botNET::Units::Store* mStore;

	private:
		bool disposed;
    };

}

}
#endif
