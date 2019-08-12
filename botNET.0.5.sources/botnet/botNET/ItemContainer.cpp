#include "ItemContainer.h"

#include "d2client.h"
#include "d2common.h"

#include "Game.h"
#include "Item.h"
#include "PC.h"
#include "UnitBase.h"

using namespace System;

namespace botNET
{
	namespace Units
	{
		ItemContainer::ItemContainer()
		{
        	}

		ItemContainer::ItemContainer( UnitBase* owner, ItemLocation type, int width, int height )
			: mOwner( owner ), mContainerType( type ), mSize( System::Drawing::Size( width, height ) )
		{
		}

		Items* ItemContainer::get_Items()
		{
			return GetItemsInContainer();
		}

		System::Drawing::Size ItemContainer::get_Size()
		{
			return mSize;
		}

		System::Drawing::Rectangle ItemContainer::get_Bounds()
		{
			return System::Drawing::Rectangle( 0, 0, mSize.Width, mSize.Height );
		}

		ItemLocation ItemContainer::get_ContainerType()
		{
			return mContainerType;
		}

		bool ItemContainer::get_IsActive()
		{
			return false;
		}

		bool ItemContainer::IsValid()
		{
			return mOwner->IsValid();
		}

		void ItemContainer::IsValidEx()
		{
			mOwner->IsValidEx();
		}

		Items* ItemContainer::GetItemsInContainer()
		{
			ItemLocation loc __gc[] = { mContainerType };
			return new botNET::Units::Items( loc );
		}

		Item* ItemContainer::GetItem( Point point )
		{
			return GetItem( point.X, point.Y );
		}

		Item* ItemContainer::GetItem( int x, int y )
		{
			UnitItem* item = D2COMMON::GetFirstInventoryItem((*D2CLIENT::PlayerUnit)->ptInventory);
			while( item )
			{
				if( item->ptItemData->Location == mContainerType )
				{
					if( ( x >= item->hOPath->Xpos && x < item->hOPath->Xpos + D2COMMON::GetItemBinFromClass( item->dwClassId )->SizeX ) &&
					    ( y >= item->hOPath->Ypos && y < item->hOPath->Ypos + D2COMMON::GetItemBinFromClass( item->dwClassId )->SizeY ) )
					{
						return new Item( item );
					}
				}

				item = D2COMMON::GetNextInventoryItem( item );
			}

			return new Item();
		}

		bool ItemContainer::HaveSpace( Item* item, [Out] Point* point )
		{
			BYTE x, y;

			// TODO: This doesn't seem to work for stash/cube? Should we even keep it?
			bool retval = D2COMMON::CheckPageForRoom( mOwner->unit->ptInventory, (UnitItem*)item->unit, mOwner->ClassID,
			                                          &x, &y, mContainerType-3 );

			if( retval )
			{
				point->X = x;
				point->Y = y;
			}

			return retval;
		}

		bool ItemContainer::HaveSpace( Item* item, Point point )
		{
			return HaveSpace( item, point.X, point.Y );
		}

		bool ItemContainer::HaveSpace ( System::Drawing::Rectangle r )
		{
			/*int lowx  = x;
			int lowy  = y;
			int highx = x + item->XSize;
			int highy = y + item->YSize;*/

			if (r.Left < 0 || r.Top < 0)
				throw new ArgumentOutOfRangeException ("Invalid position");

			// Trying to test outside bounds of container, probably a valid thing to allow
			if (r.Right > mSize.Width || r.Bottom > mSize.Height)
				return false;

			for( int tx = r.Left; tx < r.Right; tx++ )
			{
				for( int ty = r.Top; ty < r.Bottom; ty++ )
				{
					if( GetItem( tx, ty )->IsValid() )
						return false;
				}
			}

			return true;
		}

		bool ItemContainer::HaveSpace( Item* item, int x, int y )
		{
			System::Drawing::Rectangle r = System::Drawing::Rectangle (
				System::Drawing::Point (x, y),
				System::Drawing::Size (item->XSize, item->YSize)
			);
			return HaveSpace (r);
		}
/*
        Belt::Belt()
        {
        }
*/
        Belt::Belt( PC* owner )
            : ItemContainer( owner, ItemLocation::Belt, 0, 0 )
        {
        }

        int Belt::get_SlotCount()
        {
            PC* player = static_cast<PC*>(mOwner);  // will this work if it is another player?
            Item *belt = player->Equipment->GetItem( botNET::EquipmentLocation::Belt );

		    if( !belt || !belt->IsValid() )
                return 4;

		    String * code = belt->Code;
		    if(!String::Compare(code, S"lbl") || !String::Compare(code, S"vbl"))
			    return 8;
		    if(!String::Compare(code, S"mbl") || !String::Compare(code, S"tbl"))
			    return 12;
		    return 16;
        }

		bool Belt::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::BeltOpened ) > 0;
		}

        Item* Belt::GetItem( int slot )
        {
		    Game::InGameCheck();
		    if(slot > SlotCount-1 || slot < 0) throw new ArgumentOutOfRangeException("Beltslot is out of range");
		    return new Item( D2COMMON::GetBeltItem( mOwner->unit->ptInventory, slot ) );
        }

		Item* Belt::GetItem( Point point )
		{
			return GetItem( point.X, point.Y );
		}

		Item* Belt::GetItem( int x, int y )
		{
			return GetItem( y * 4 + x );
		}

		bool Belt::HaveSpace( Item* item, [Out] Point* point )
		{
			// Verify that this is a possible belt item
			if (item->ItemType != ItemType::HealingPotion &&
				item->ItemType != ItemType::RejuvenationPotion &&
				item->ItemType != ItemType::ManaPotion &&
				item->ItemType != ItemType::ThawingPotion &&
				item->ItemType != ItemType::AntidotePotion &&
				item->ItemType != ItemType::StaminaPotion &&
				item->ItemType != ItemType::Scroll
				)
				return false; //maybe exception?
			

			for( int i = 0; i < SlotCount; i++ )
			{
				if( !GetItem( i )->IsValid() )
				{
					point->X = i%4;
					point->Y = i/4;
					return true;
				}
			}
			return false;
		}

		bool Belt::HaveSpace( Item* item, int index )
		{
			return !GetItem( index )->IsValid();
		}

		bool Belt::HaveSpace( Item* item, Point point )
		{
			return HaveSpace( item, point.Y * 4 + point.X );
		}

		bool Belt::HaveSpace( Item* item, int x, int y )
		{
			return HaveSpace( item, y * 4 + x );
		}
/*
        Cube::Cube()
        {
        }
*/
        Cube::Cube( PC* owner )
            : ItemContainer( owner, ItemLocation::Cube, 3, 4 )
        {
        }

		bool Cube::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::CubePanel ) > 0;
		}

       	void Cube::Transmute()
    	{
	    	Game::InGameCheck();

			if (D2CLIENT::GetUIState (UIState::CubePanel) == 0)
				throw new ApplicationException ("Not interacted with Cube");

			// TODO: Use something better than this
		    D2CLIENT::TransferGold(0x4F, 0x18, 0, 0);
	    }
/*
        Equipment::Equipment()
        {
        }
*/
        Equipment::Equipment( Player* owner )
            : ItemContainer( owner, ItemLocation::Equipped, 0, 0 )
        {
        }

		bool Equipment::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::InventoryPanel ) > 0;
		}

        Item* Equipment::GetItem( EquipmentLocation location )
        {
	    	return new Item( D2COMMON::GetEquippedItem( mOwner->unit->ptInventory, location ) );
        }

        Items* Equipment::GetItemsInContainer()
        {
            return new botNET::Units::Items( mOwner->unit, mContainerType );
        }
/*
        Inventory::Inventory()
        {
        }
*/
        Inventory::Inventory( PC* owner )
            : ItemContainer( owner, ItemLocation::Inventory, 10, 4 )
        {
        }

		bool Inventory::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::InventoryPanel ) > 0;
		}

        int Inventory::get_Gold()
        {
			return D2COMMON::GetAddedStat(*D2CLIENT::PlayerUnit, StatType::Gold, 0);
        }

		int Inventory::get_GoldMax()
		{
			PC* player = static_cast<PC*>(mOwner);
			return player->CharacterLevel * 10000;
		}

        Store::Store()
        {
        }

        Store::Store( UnitBase* owner )
            : ItemContainer( owner, ItemLocation::Store, 10, 10 )
        {
        }

        Items* Store::GetItemsInContainer()
        {
            return new botNET::Units::Items( mOwner->unit, mContainerType );
        }

        bool Store::IsValid()
        {
            return D2CLIENT::GetUIState( UIState::StorePanel ) > 0;
        }

        void Store::IsValidEx()
        {
        }

		bool Store::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::StorePanel ) > 0;
		}

/*
        Stash::Stash()
        {
        }
*/
		Stash::Stash( PC* owner ) : ItemContainer (owner, ItemLocation::Stash, 6, D2CLIENT::GetGameType() == GameType::Classic ? 4 : 8)
        {
        }

		int Stash::get_GoldMax ()
		{
			PC* player = static_cast<PC*>(mOwner);

			if (player->CharacterLevel >= 30)
				return 800000 + (int)Math::Floor ((player->CharacterLevel - 30) / 2) * 50000;
			else
				return (int)Math::Floor ((player->CharacterLevel + 10) / 10) * 50000;
		}

        int Stash::get_Gold()
        {
			return D2COMMON::GetAddedStat(*D2CLIENT::PlayerUnit, StatType::GoldBank, 0);
        }

		bool Stash::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::StashPanel ) > 0;
		}

/*
        Trade::Trade()
        {
        }
*/
        Trade::Trade( Player* owner )
            : ItemContainer( owner, ItemLocation::Trade, 10, 4 )
        {
        }

		bool Trade::get_IsActive()
		{
			return D2CLIENT::GetUIState( UIState::PlayerTradeRequest ) > 0;
		}

		Items* Trade::GetItemsInContainer()
        {
            return new botNET::Units::Items( mOwner->unit, mContainerType );
        }

        bool Trade::IsValid()
        {
            return D2CLIENT::GetUIState( UIState::PlayerTradeRequest ) > 0;
        }

        void Trade::IsValidEx()
        {
        }
    }
}
