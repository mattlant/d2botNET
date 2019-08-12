#include "botnet.h"
#include ".\pc.h"

#include "npc.h"
#include "game.h"
#include "gameobject.h"
#include "warp.h"
#include "item.h"
#include "items.h"
#include "ItemContainer.h"
#include "verify.h"
#include "packet.h"
#include "PacketEventArgs.h"
#include "ui.h"

#include "d2common.h"
#include "d2client.h"

#include "asm_naked_funcs.h"

using namespace botNET::Messaging;
using namespace botNET::Imports;

//typedef void __fastcall clickequip(UnitPlayer * pl, d2_Inventory * i, int loc);

namespace botNET
{

namespace Units
{

	PC::PC(void)
	{
		this->setunit(*D2CLIENT::PlayerUnit);

        mBelt = new botNET::Units::Belt( this );
        mInventory = new botNET::Units::Inventory( this );
        mCube = new botNET::Units::Cube( this );
        mStash = new botNET::Units::Stash( this );
	}

	PC * PC::get_Me() /* life */
	{
		if(!PC::mMe->IsValid(true))
		{
			PC::mMe = new PC();

			if(!PC::mMe->IsValid(false))
				throw new System::ApplicationException("Newly instanced PC is invalid!");
		}		
        
		return mMe;
	}

	void PC::set_Me(PC * AnotherMe) /* life */
	{
		if(AnotherMe == NULL || !AnotherMe->IsValid())
			throw new System::ArgumentException("Cannot set PC.Me to a null or invalid instance of PC!");

		PC::mMe = AnotherMe;
	}

	void PC::Dispose(bool disposing)
	{
		if(!this->disposed)
		{
            disposed = true;

			try
			{
				if(disposing)
				{
					this->InternalOnHealthManaChange = NULL;
				}

			}
			__finally
			{
				__super::Dispose(disposing);
			}
		}
	}

	void PC::Interact(UnitBase * u)
	{
		this->ClickMap(ClickType::LeftDown, false, u);
		delay();
		this->ClickMap(ClickType::LeftUp, false, u);
	}

	void PC::ClickBelt(ClickType ClickTypeToUse, bool UseShiftKey, int BeltSlot)
	{
		try
		{
			Game::InGameCheck();
			switch(ClickTypeToUse)
			{
			case ClickType::LeftDown:
				if(this->CursorItem->IsValid())
				{
					//check for item under
					Item * under = mBelt->GetItem(BeltSlot);
					if(under->IsValid())
						D2CLIENT::PrePacket2(pp_SwapBeltItem, this->CursorItem->UniqueID, under->UniqueID);
					else
						D2CLIENT::PrePacket2(pp_DropInBelt, this->CursorItem->UniqueID, BeltSlot);
				}
				else
				{
					Item * under = mBelt->GetItem(BeltSlot);
					if(under->IsValid())
						D2CLIENT::PrePacket1(pp_PickupFromBelt, under->UniqueID);
				}
				break;
			case ClickType::RightDown:
				Item * under = mBelt->GetItem(BeltSlot);
				if(under->IsValid())
					D2CLIENT::PrePacket3(pp_RightClickBeltItem, under->UniqueID, UseShiftKey, 0);
				break;
			}
		}
		catch(Exception* ex)
		{
			Game::Print(ex);
		}
	}

	void PC::ClickEquipment(EquipmentLocation Location)
	{
		Game::InGameCheck();
		//coreClickEquipmentLocation((int)Location);
	}

	void PC::ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, Units::Item* ItemToClick)
	{
		Utils::Verify::IsValidArgEx(ItemToClick);

		if(ClickTypeToUse != ClickType::LeftDown && ClickTypeToUse != ClickType::RightDown)
			throw new ArgumentException("Me.ClickItem -> Only LeftDown and RightDown are used");

		if (ItemToClick->unit->ptItemData->ItemFlags == 0xFFFFFFFF) //what is this?
		{
			// Verify we can actually buy
			if (D2CLIENT::GetUIState (UIState::StorePanel) == 0)
				throw new ApplicationException ("Can't buy item, not interacted with an NPC");
			D2CLIENT::PrePacket4(pp_Buy, *D2CLIENT::InteractedNPCUniqueID, ItemToClick->UniqueID, (UseShiftKey?0x80000000:0x0), ItemToClick->GetPrice(PriceType::Buy, *D2CLIENT::InteractedNPCClassID));
		}
		else
		{
			//switch(ItemToClick->unit->ptItemData->Location)
			switch (ItemToClick->Location)
			{
			case ItemLocation::Ground: //ground
				this->Interact(ItemToClick);
				break;
			case ItemLocation::Equipped: //equipslot

				//clickequip * click = reinterpret_cast<clickequip*>(*(D2CLIENT::ClickEquipmentLocationBase + ItemToClick->EquippedLocation));
				//click(*D2CLIENT::PlayerUnit, (*D2CLIENT::PlayerUnit)->ptInventory, ItemToClick->EquippedLocation);

				break;
			case ItemLocation::Belt: //belt
				this->ClickBelt(ClickTypeToUse, UseShiftKey, ItemToClick->X);
				break;

			case ItemLocation::Inventory:
			case ItemLocation::Stash:
			case ItemLocation::Cube:
			case ItemLocation::Trade:
				// TODO: Are any of these even legal in trade?
				if(Game::CursorMode == CursorMode::Identify)
				{
					D2CLIENT::PrePacket2(pp_IdentifyItem, ItemToClick->id, (*D2CLIENT::IdentifyingScroll)->dwId);
					break;
				}
				if(UseCtrlKey)
				{
					// Verify we can actually sell
					if (D2CLIENT::GetUIState (UIState::StorePanel) == 0)
						throw new ApplicationException ("Can't sell item, not interacted with an NPC");
					//Sell
					if(ClickTypeToUse == ClickType::LeftDown)
						D2CLIENT::PrePacket4(pp_Sell, *D2CLIENT::InteractedNPCUniqueID, ItemToClick->UniqueID, 0, ItemToClick->GetPrice(PriceType::Sell, *D2CLIENT::InteractedNPCClassID));
				}
				else if(UseShiftKey)
				{
					//Move to belt
					if(ClickTypeToUse == ClickType::LeftDown)
						D2CLIENT::PrePacket1(pp_MoveToBelt, ItemToClick->UniqueID);
					else
						D2CLIENT::PrePacket3(pp_RightClickInventory, ItemToClick->UniqueID, this->X, this->Y);
				}
				else
				{
					if(ClickTypeToUse == ClickType::LeftDown)
						D2CLIENT::PrePacket1(pp_PickupFromInventory, ItemToClick->UniqueID);
					else
					{
						Game::lastrightclickitem = ItemToClick->UniqueID;
                        D2CLIENT::PrePacket3(pp_RightClickInventory, ItemToClick->UniqueID, this->X, this->Y);
					}
				}

				break;
			case ItemLocation::Store:
				//Shop
				// Verify we can actually buy
				if (D2CLIENT::GetUIState (UIState::StorePanel) == 0)
					throw new ApplicationException ("Can't buy item, not interacted with an NPC");
				D2CLIENT::PrePacket4(pp_Buy, *D2CLIENT::InteractedNPCUniqueID, ItemToClick->UniqueID, (UseShiftKey?0x80000000:0x0), ItemToClick->GetPrice(PriceType::Buy, *D2CLIENT::InteractedNPCClassID));
				break;
			default:
				throw new ApplicationException("Could not click the item");
			}
		}
	}

	void PC::ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, ItemLocation Location, int XCoord, int YCoord)
	{
		Game::InGameCheck();

		if (XCoord < 0 || YCoord < 0)
			throw new ArgumentOutOfRangeException ("Negative click coordinates");

		if (this->CursorItem)
		{
			//drop moves;
			switch(Location)
			{
				case ItemLocation::Ground:
					break;
				case ItemLocation::Belt:
					//dropinbelt or swap

					// Note, ClickBelt will throw exception on bad XCoord. Maybe we should also validate it here to avoid
					// ambiguity.
					this->ClickBelt(ClickTypeToUse, UseShiftKey, XCoord);
					break;

				case ItemLocation::Inventory:
					if (XCoord > mInventory->Size.Width || YCoord > mInventory->Size.Height)
						throw new ArgumentOutOfRangeException ("Attempt to click outside container bounds");

					if (XCoord + this->CursorItem->XSize > mInventory->Size.Width || YCoord + this->CursorItem->YSize > mInventory->Size.Height)
						throw new ArgumentOutOfRangeException ("Item size exceeds container bounds");

					D2CLIENT::PrePacket4(pp_DropToInventory, this->CursorItem->UniqueID, XCoord, YCoord, Location - 3);
					break;

				case ItemLocation::Cube:
					//TODO: Verify player actually has a cube and is in a legal state to be able to shift items around in it.
					if (XCoord > mCube->Size.Width || YCoord > mCube->Size.Height)
						throw new ArgumentOutOfRangeException ("Attempt to click outside container bounds");

					if (XCoord + this->CursorItem->XSize > mCube->Size.Width || YCoord + this->CursorItem->YSize > mCube->Size.Height)
						throw new ArgumentOutOfRangeException ("Item size exceeds container bounds");

					D2CLIENT::PrePacket4(pp_DropToInventory, this->CursorItem->UniqueID, XCoord, YCoord, Location - 3);
					break;

				case ItemLocation::Stash:
					if (XCoord > mStash->Size.Width || YCoord > mStash->Size.Height)
						throw new ArgumentOutOfRangeException ("Attempt to click outside container bounds");

					if (XCoord + this->CursorItem->XSize > mStash->Size.Width || YCoord + this->CursorItem->YSize > mStash->Size.Height)
						throw new ArgumentOutOfRangeException ("Item size exceeds container bounds");

					D2CLIENT::PrePacket4(pp_DropToInventory, this->CursorItem->UniqueID, XCoord, YCoord, Location - 3);
					break;

				case ItemLocation::Trade:
					if (XCoord > mTrade->Size.Width || YCoord > mTrade->Size.Height)
						throw new ArgumentOutOfRangeException ("Attempt to click outside container bounds");

					if (XCoord + this->CursorItem->XSize > mTrade->Size.Width || YCoord + this->CursorItem->YSize > mTrade->Size.Height)
						throw new ArgumentOutOfRangeException ("Item size exceeds container bounds");

					D2CLIENT::PrePacket4(pp_DropToInventory, this->CursorItem->UniqueID, XCoord, YCoord, Location - 3);
					break;

				default:
					break;
			}
		}
	}

	void PC::ClickItem(ClickType ClickTypeToUse, bool UseShiftKey, bool UseCtrlKey, ItemLocation Location)
	{
		Game::InGameCheck();

//TODO: Add in HasSpace function, check for space, if space, drop in there
	}

	void PC::ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, int x, int y)
	{
		Game::InGameCheck();

		BYTE ClickFlag = 0x0;
		if(*D2CLIENT::AlwaysRun)
			ClickFlag = 0x8;
		if(UseShiftKey)
			ClickFlag |= 0x4;

		D2CLIENT_ClickMapASM(ClickTypeToUse, ClickFlag, NULL, x, y);
	}

	void PC::ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, System::Drawing::Point c)
	{
		this->ClickMap(ClickTypeToUse, UseShiftKey, c.X, c.Y);
	}

	void PC::ClickMap(ClickType ClickTypeToUse, bool UseShiftKey, UnitBase * UnitToClick)
	{
		//ignore validity check on Up clicks (gold)
		if(ClickTypeToUse == ClickType::LeftDown || ClickTypeToUse == ClickType::RightDown)
			Utils::Verify::IsValidArgEx(UnitToClick);
		Game::InGameCheck();

		BYTE ClickFlag = 0x0;
		if(*D2CLIENT::AlwaysRun)
			ClickFlag = 0x8;
		if(UseShiftKey)
			ClickFlag |= 0x4;

		D2CLIENT_ClickMapASM(ClickTypeToUse, ClickFlag, UnitToClick->unit, 0, 0);
	}

	void PC::ClickMerc()
	{
		Game::InGameCheck();
		if(!this->Mercenary->IsValid())
			throw new ApplicationException("You have no Mercenary to use ClickMerc on");
		D2CLIENT::PrePacketOther1(pp_ClickMerc, 0);
	}

	void PC::ClickMerc(EquipmentLocation loc)
	{
		Game::InGameCheck();
		if(!this->Mercenary->IsValid())
			throw new ApplicationException("You have no Mercenary to use ClickMerc on");
		D2CLIENT::PrePacketOther1(pp_ClickMerc, (int) loc);
	}

	SkillType PC::GetSkillOnHand(SkillHand HandToCheck)
	{
		Game::InGameCheck();
		Skill * pSkill = (HandToCheck == SkillHand::Left)?D2COMMON::GetLeftSkill((UnitPlayer*)this->unit):D2COMMON::GetRightSkill((UnitPlayer*)this->unit);
		return (SkillType)pSkill->pSkillInfo->Id;
	}

	void PC::SetSkill(SkillType SkillToSet, SkillHand HandToUse)
	{
		Game::InGameCheck();
		D2CLIENT::PrePacket2(pp_SetSkill, (SkillToSet | HandToUse), 0xFFFFFFFF);
	}

	int PC::GetSkillLevel(SkillType SkillToCheck)
	{
		//TODO: test this on other players later
		Game::InGameCheck();
		Skill * pSkill = D2COMMON::GetUnitSkill((UnitPlayer*)this->unit, (int)SkillToCheck, -1);
		if(pSkill)
			return pSkill->SkillLevel + D2COMMON::GetAddedStat((UnitPlayer*)this->unit, 0x61, (int)SkillToCheck);
		return 0;
	}

	int PC::GetSkillLevel(SkillType SkillToCheck, GetSkillLevelMode mode)
	{
		//TODO: test this on other players later
		Game::InGameCheck();
		Skill * pSkill = D2COMMON::GetUnitSkill((UnitPlayer*)this->unit, (int)SkillToCheck, -1);
		if(pSkill)
		{
			if(mode == GetSkillLevelMode::Base)
				return pSkill->SkillLevel;
			else if(mode == GetSkillLevelMode::Bonus)
				return D2COMMON::GetAddedStat((UnitPlayer*)this->unit, 0x61, (int)SkillToCheck);
			else 
				return pSkill->SkillLevel + D2COMMON::GetAddedStat((UnitPlayer*)this->unit, 0x61, (int)SkillToCheck);
		}
		return 0;
	}

    Item* PC::GetPotion(PotionType type, bool BeltOnly)
    {
        Items* potions;

		// Get all locations where we could want potions from
		ItemLocation locations [] = {ItemLocation::Inventory, ItemLocation::Belt};
		potions = new Items (locations);		

		// Filter by wanted type
		switch( type )
        {
			case AnyHealing:
			{
				int classids __gc[] =
				{
					PotionType::MinorHealing,
					PotionType::LightHealing,
					PotionType::Healing,
					PotionType::GreaterHealing,
					PotionType::SuperHealing
				};
                potions = potions->GetByClassID (classids);
				break;
			}
            case AnyMana:
            {
				int classids __gc[] =
				{
					PotionType::MinorMana,
					PotionType::LightMana,
					PotionType::Mana,
					PotionType::GreaterMana,
					PotionType::SuperMana
				};
                potions = potions->GetByClassID (classids);
				break;
            }
            case AnyRejuvenation:
            {
				int classids __gc[] = { PotionType::Rejuvenation, PotionType::LargeRejuvenation };
                potions = potions->GetByClassID (classids);
				break;
            }
            default:
            {
                int classids __gc[] = { type };
                potions = potions->GetByClassID (classids);
				break;
            }
		}
		
		// Filter some more if belt only
        if( BeltOnly )
        {
            IEnumerator* enumerator = potions->GetEnumerator();
            while( enumerator->MoveNext() )
            {
                Item* potion = static_cast<Item*>(enumerator->Current);
                if( potion->Location == ItemLocation::Belt )
                    return potion;
            }
        }
        else
        {
            return potions->Item[0];
        }

        return new Item();
    }

    void PC::DepositGold (int Amount)
	{
		Game::InGameCheck();

		// Check stash
		if (D2CLIENT::GetUIState(UIState::StashPanel) == 0)
			throw new ApplicationException ("Stash not opened");

		// No action, no exception here since in D2 you can deposit 0 gold and nothing happens
		if (Amount == 0)
			return;

		// Check for invalid transaction
		if (Amount < 0)
			throw new ArgumentOutOfRangeException ("Amount is negative");

		// Check we have enough or we get C/I
		if (mInventory->Gold < Amount)
			throw new ArgumentOutOfRangeException ("Amount exceeds available gold in Inventory");

		D2CLIENT::TransferGold(0x4F, 0x14, Amount >> 16, Amount & 0xFFFF);
	}

	void PC::WithdrawGold (int Amount)
	{
		Game::InGameCheck();

		// Check stash
		if (D2CLIENT::GetUIState(UIState::StashPanel) == 0)
			throw new ApplicationException ("Stash not opened");

		// No action, no exception here since in D2 you can deposit 0 gold and nothing happens
		if (Amount == 0)
			return;

		// Check for invalid transaction
		if (Amount < 0)
			throw new ArgumentOutOfRangeException ("Amount is negative");

		// Check we have enough and we can hold it or we get C/I
		if (mStash->Gold < Amount)
			throw new ArgumentOutOfRangeException ("Amount exceeds available gold in Stash");
		
		if (Amount > CharacterLevel * 10000)
			throw new ArgumentOutOfRangeException ("Amount exceeds maximum holdable by character");

		D2CLIENT::TransferGold(0x4F, 0x13, Amount >> 16, Amount & 0xFFFF);
	}

	void PC::DropGold(int Amount)
	{
		Game::InGameCheck();

		// No point sending a packet for invalid transaction
		if (Amount <= 0)
			throw new ArgumentOutOfRangeException ("Invalid amount");

		// Check we have enough or we get C/I
		if (mInventory->Gold < Amount)
			throw new ArgumentOutOfRangeException ("Amount exceeds available gold in Inventory");

		D2CLIENT::PrePacket2(0x50, this->unit->dwId, Amount);
	}

	SkillType PC::get_LeftSkill()
	{
		Game::InGameCheck();
		return (SkillType)D2COMMON::GetLeftSkill((UnitPlayer*)this->unit)->pSkillInfo->Id;
	}

	void  PC::set_LeftSkill(SkillType skill)
	{
		Game::InGameCheck();
		D2CLIENT::PrePacket2(pp_SetSkill, (skill | SkillHand::Left), 0xFFFFFFFF);
	}

	SkillType PC::get_RightSkill()
	{
		Game::InGameCheck();
		return (SkillType)D2COMMON::GetRightSkill((UnitPlayer*)this->unit)->pSkillInfo->Id;
	}

	void PC::set_RightSkill(SkillType skill)
	{
		Game::InGameCheck();
		D2CLIENT::PrePacket2(pp_SetSkill, (skill | SkillHand::Right), 0xFFFFFFFF);
	}

	int PC::get_CurrentWeaponSlot()
	{
		Game::InGameCheck();
		return *D2CLIENT::CurrentWeaponSlot+1;
	}


	void PC::SwitchWeaponSlot(int Slot)
	{
		Game::InGameCheck();
		if(*D2CLIENT::CurrentWeaponSlot+1 != Slot)
			D2CLIENT::WeaponSwitch();
	}

	UnitBase * PC::get_SelectedUnit(void) 
	{
 		Game::InGameCheck();
		UnitAny * unit = D2CLIENT::GetSelectedUnit();
		if(unit)
		{
			switch(unit->dwType)
			{
			case 0:
				return new Player(unit);
			case 1:
				return new NPC(unit);
			case 2:
				return new GameObject(unit);
			case 4:
				return new Item(unit);
			case 5:
				return new Warp(unit);
			}
		}
		unit = *D2CLIENT::SelectedInventoryUnit;
		if(unit)
			return new Item(unit);

		return new UnitBase();
	}

	Item * PC::get_CursorItem()
	{
 		//Game::InGameCheck();
		return new Item(D2COMMON::GetCursorItem(unit->ptInventory));
		//return new Item(botNET::D2COMMON::GetCursorItem(IntPtr(unit->ptInventory)));

	}

    int PC::get_Gold()
    {
 		Game::InGameCheck();
        return mStash->Gold + mInventory->Gold;
    }

	UInt64 PC::get_Waypoints()
	{
		//TODO: CHange to use d2 functions
		return PC::waypoints;
	}

	bool PC::HasWaypoint(WaypointArea WPArea) 
	{
		UInt64 bit = (UInt64)1 << (UInt64)WPArea;
		//botNET::Game::Print(String::Concat("Checking WPArea : ",(__box(WPArea))->ToString(), " and it is ", ((bit & PC::waypoints) > 0 ? "aquired." : "missing.")));
		return (PC::waypoints & bit) > 0;
	}

	bool PC::HasWaypoint(AreaLevel WPArea)
	{
		System::String * AreaToString = __box(WPArea)->ToString();

		//FieldInfo * F = __typeof(WaypointArea)->GetField(AreaToString);

		//if(F == NULL)
		//{
		//	throw new ArgumentException("The specified AreaLevel does not have a corresponding WaypointArea.");
		//	return false; // Return false if you comment out the exception
		//}
		//else
	//	{
			AreaLevel WP = *static_cast<__box botNET::AreaLevel*>(Enum::Parse(__typeof(WaypointArea), AreaToString, false));

			//Object* WP = (Enum::Parse(__typeof(WaypointArea), __box(WPArea)->ToString(), false));
			UInt64 bit = (UInt64)1 << (UInt64)WP;
			//botNET::Game::Print(String::Concat("Checking Waypoint AreaLevel : ",(__box(WPArea))->ToString(), " and it is ", ((bit & PC::waypoints) > 0 ? "aquired." : "missing.")));
			return (PC::waypoints & bit) > 0;
	//	}
	}

	bool PC::get_HasWaypointList()
	{
		return (PC::waypoints != 0);
	}
	
	botNET::Units::Belt* PC::get_Belt()
	{
        return mBelt;
    }

	botNET::Units::Cube* PC::get_Cube()
	{
		return mCube;
	}

	botNET::Units::Inventory* PC::get_Inventory()
	{
		return mInventory;
	}

	botNET::Units::Stash* PC::get_Stash()
	{
		return mStash;
	}

    UnitBase* PC::get_InteractedUnit(void)
    {
        Game::InGameCheck();

        if( *D2CLIENT::InteractedNPCUniqueID )
            return new NPC((UInt32)(*D2CLIENT::InteractedNPCUniqueID));
        else if( *D2CLIENT::InteractedWPUniqueID )
            return new GameObject((UInt32)(*D2CLIENT::InteractedWPUniqueID));
        else
            return new UnitBase();
    }

	void PC::add_OnHealthManaChangeEvent( HealthManaChangeHandler* h)
	{ 
		this->ePacketAdd();
		InternalOnHealthManaChange += h;
	}

	void PC::remove_OnHealthManaChangeEvent( HealthManaChangeHandler* h) 
	{ 
		this->ePacketRemove();
		InternalOnHealthManaChange -= h; 
	}

	void PC::raise_OnHealthManaChangeEvent(UnitBase* source, EventArgs* e) 
	{ 
		InternalOnHealthManaChange(source, e); 
	}

	void PC::delay()
	{
		Thread::Sleep(((new Random())->Next(75, 125)));
	}

	void PC::v_processpackets(PacketEventArgs* e)
	{
		switch(e->Packet->_packet[0])
		{
		case 0x95:
			this->raise_OnHealthManaChangeEvent(this, new EventArgs());		
		
		}
		__super::v_processpackets(e);

	}
}

}
