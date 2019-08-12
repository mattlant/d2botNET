#ifndef PC_H
#define PC_H

#include "player.h"
#include "definitions.h"

namespace botNET
{

namespace Units
{
 	namespace Messaging
	{
		public __gc class PresetUnit;
	}

   public __delegate void HealthManaChangeHandler(UnitBase* source, EventArgs* e);
	
    // forward declarations
	public __gc class NPC;
	public __gc class GameObject;
	public __gc class Belt;
	public __gc class Cube;
	public __gc class Item;
	public __gc class Inventory;
    public __gc class Stash;
	public __gc class Warps;
	public __gc class Items;

	public __gc class PC : public botNET::Units::Player
	{
	public:		
		void Interact(UnitBase * UnitToInteractWith);

        void ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, System::Drawing::Point c);
		void ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, int x, int y);
		void ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, UnitBase * UnitToClick);

        void ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, Item * ItemToClick);
		void ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, ItemLocation Location, int XCoord, int YCoord);
		void ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, ItemLocation Location);

        void ClickEquipment(EquipmentLocation Location);

        void ClickMerc();
		void ClickMerc(EquipmentLocation loc);

        void ClickBelt(ClickType ClickTypeToUse, bool UseShiftKey, int BeltSlot);

        int GetSkillLevel(SkillType SkillToCheck);
		int GetSkillLevel(SkillType SkillToCheck, GetSkillLevelMode mode);

		Item* GetPotion(PotionType pt, bool BeltOnly);

        void DepositGold(int Amount);
		void WithdrawGold(int Amount);
		void DropGold(int Amount);

		__property int get_Gold(void);
		__property UnitBase * get_SelectedUnit(void);
		void SetSkill(SkillType SkillToSet, SkillHand HandToUse);
		SkillType GetSkillOnHand(SkillHand HandToCheck);
		__property void set_LeftSkill(SkillType skill);
		__property SkillType get_LeftSkill(void);
		__property void set_RightSkill(SkillType skill);
		__property SkillType get_RightSkill(void);
		__property Item * get_CursorItem(void);
		__property UInt64 get_Waypoints(void);

		__property int get_CurrentWeaponSlot();  // maybe move to Equipment
		void SwitchWeaponSlot(int Slot);         // maybe move to Equipment

		__property botNET::Units::Belt*         get_Belt(void);
        __property botNET::Units::Inventory*    get_Inventory(void);
		__property botNET::Units::Cube*         get_Cube(void);
		__property botNET::Units::Stash*        get_Stash(void);

        __property UnitBase* get_InteractedUnit(void);

        bool HasWaypoint(AreaLevel WPNumber);
        bool HasWaypoint(WaypointArea WPNumber);
        __property bool get_HasWaypointList();

		PC(void);

		//********************* EVENTSTUFF ******************************
		__event void add_OnHealthManaChangeEvent( HealthManaChangeHandler* h);
		__event void remove_OnHealthManaChangeEvent( HealthManaChangeHandler* h) ;
		__event void raise_OnHealthManaChangeEvent(UnitBase* source, EventArgs* e);

	public private:
		static PC* me;
		void delay();
		static UInt64 waypoints = 0;

    protected:
		void v_processpackets(botNET::Messaging::PacketEventArgs* e);

		virtual void Dispose(bool disposing);

    protected:
        botNET::Units::Belt*      mBelt;
        botNET::Units::Inventory* mInventory;
        botNET::Units::Cube*      mCube;
        botNET::Units::Stash*     mStash;

	private:
		HealthManaChangeHandler * InternalOnHealthManaChange;
        bool disposed;
	};

}

}

#endif