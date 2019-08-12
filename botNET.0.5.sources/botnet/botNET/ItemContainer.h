#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "botnet.h"

#include "Items.h"
#include "IValid.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

namespace botNET
{
    namespace Units
    {
        // forward declarations
        public __gc class NPC;
        public __gc class PC;
        public __gc class Player;

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class ItemContainer : public botNET::IValid
        {
        public:
            __property Items* get_Items();
			__property System::Drawing::Rectangle get_Bounds();
            __property System::Drawing::Size get_Size();
            __property ItemLocation get_ContainerType();

			__property virtual bool get_IsActive();

            virtual Item* GetItem( Point point );
            virtual Item* GetItem( int x, int y );

            virtual bool HaveSpace( Item* item, [Out] Point* point );
            virtual bool HaveSpace( Item* item, Point point );
            virtual bool HaveSpace( Item* item, int x, int y );
			virtual bool HaveSpace( System::Drawing::Rectangle r );

            virtual bool IsValid();
			virtual void IsValidEx();

        protected:
            ItemContainer();
            ItemContainer( UnitBase* owner, ItemLocation type, int width, int height );

            virtual botNET::Units::Items* GetItemsInContainer();

        protected:
            UnitBase* mOwner;
            ItemLocation mContainerType;
            System::Drawing::Size mSize;
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Belt : public botNET::Units::ItemContainer
        {
        public:
            __property int get_SlotCount();

			__property virtual bool get_IsActive();

			virtual Item* GetItem( int index );
            virtual Item* GetItem( Point point );
            virtual Item* GetItem( int x, int y );

            virtual bool HaveSpace( Item* item, [Out] Point* point );
            virtual bool HaveSpace( Item* item, int index );
            virtual bool HaveSpace( Item* item, Point point );
            virtual bool HaveSpace( Item* item, int x, int y );

        public private:
            Belt( PC* owner );
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Cube : public botNET::Units::ItemContainer
        {
        public:
			__property virtual bool get_IsActive();

		    void Transmute();

//			virtual bool IsValid();
//			virtual void IsValidEx();

        public private:
            Cube( PC* owner );
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Equipment : public botNET::Units::ItemContainer
        {
        public:
			__property virtual bool get_IsActive();

            Item* GetItem( EquipmentLocation location );

        public private:
            Equipment( Player* owner );

        protected:
            virtual botNET::Units::Items* GetItemsInContainer();
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Inventory : public botNET::Units::ItemContainer
        {
        public:
            __property int get_Gold();
			__property int get_GoldMax();

			__property virtual bool get_IsActive();

        public private:
            Inventory( PC* owner );
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Store : public botNET::Units::ItemContainer
        {
        public:
			__property virtual bool get_IsActive();

            bool IsValid();
			void IsValidEx();

        public private:
            Store();
            Store( UnitBase* owner );

        protected:
            virtual botNET::Units::Items* GetItemsInContainer();
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Stash : public botNET::Units::ItemContainer
        {
        public:
            __property int get_Gold();
			__property int get_GoldMax();

			__property virtual bool get_IsActive();

        public private:
            Stash( PC* owner );
        };

        ///////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////
        public __gc class Trade : public botNET::Units::ItemContainer
        {
        public:
			__property virtual bool get_IsActive();

            bool IsValid();
            void IsValidEx();

        public private:
            Trade( Player* owner );

        protected:
            virtual botNET::Units::Items* GetItemsInContainer();
        };
    }
}

#endif
