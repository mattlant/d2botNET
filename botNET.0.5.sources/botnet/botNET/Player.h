#ifndef PLAYERUNIT_H
#define PLAYERUNIT_H

#include "playernpcbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{

namespace Units
{
    // forward declarations
    public __gc class Equipment;
    public __gc class Trade;
	public __gc class NPC;
	public __gc class NPCs;
	public __gc class RosterPlayer;

	public __gc class Player : public botNET::Units::PlayerNPCBase, public ISerializable
	{
	public:
		Player(void);
		Player(int ClassID);
		Player(int ClassID, int mode);
		Player(String* name);
		Player(String* name, int mode);
		Player(UInt32 UniqueID);
		Player(SerializationInfo* info, StreamingContext* context);
		~Player(void);

        __property botNET::Units::Equipment*    get_Equipment(void);
		__property botNET::Units::Trade*        get_Trade(void);
		__property virtual String * get_Name();
		__property PlayerMode get_Mode();
		__property NPCs* get_Minions();
		__property bool get_IsInTown(void);
		__property int get_CharacterLevel(void);
		bool IsInParty(RosterPlayer * player);
		__property NPC * get_Mercenary(void);
		__property Player * get_Corpse(void);

		void GetObjectData(SerializationInfo* info, StreamingContext context);
		//OLD 

	public private:
		Player(UnitAny* u);

		virtual UnitBase* CreateNew(UnitAny* u);
		virtual UnitBase* CreateNew();

    protected:
        virtual void Dispose(bool disposing);

    protected:
        botNET::Units::Equipment* mEquipment;
        botNET::Units::Trade*     mTrade;

    private:
        void Player::Init();

	private:
		bool disposed;
    };

}

}
#endif
