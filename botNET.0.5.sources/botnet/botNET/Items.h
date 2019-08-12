#ifndef ITEMCOLLECTION_H
#define ITEMCOLLECTION_H

#include "UnitBase.h"
#include "UnitCollectionBase.h"

namespace botNET
{

namespace Units
{
    // forward declarations

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class Items : public UnitCollectionBase
	{
	public:
		Items();
		Items(botNET::Units::Item* units[]);
		Items(bool all);
		//Items(ItemLocation location);
		Items([ParamArray] ItemLocation location[]);
		Items([ParamArray] String * names[]);
		Items([ParamArray] int classid __gc[]);

		__property botNET::Units::Item* get_Item( int index );
		__property void set_Item( int index, botNET::Units::Item* value );
		int Add(botNET::Units::Item* value);
		Items* Add(botNET::Units::Item* ItemsToAdd[]);
		Items* Add(Items* ItemsToAdd);
		int IndexOf(botNET::Units::Item* value);
		void Items::Insert(int index, botNET::Units::Item* value); 
		void Items::Remove(botNET::Units::Item* value);
		bool Items::Contains(botNET::Units::Item* value);

		botNET::Units::Item* GetClosest();
		botNET::Units::Item* GetClosest(System::Drawing::Point c);
		botNET::Units::Item* GetClosest(UnitBase* p);

		botNET::Units::Items* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		botNET::Units::Items* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		botNET::Units::Items* GetByMode([ParamArray] ItemMode modes __gc[]);
		botNET::Units::Items* GetByClassID([ParamArray] int classid __gc[]);
		botNET::Units::Items* GetByState([ParamArray] StateType states __gc[]);
		botNET::Units::Items* GetByStat([ParamArray] StatType stats __gc[]);
		botNET::Units::Items* GetByName([ParamArray] String* names[]);
		botNET::Units::Items* GetByItemCode([ParamArray] String* codes[]);

		botNET::Units::Items* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		botNET::Units::Items* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		botNET::Units::Items* GetByMode(bool negate, [ParamArray] ItemMode modes __gc[]);
		botNET::Units::Items* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		botNET::Units::Items* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		botNET::Units::Items* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);
		botNET::Units::Items* GetByName(bool negate, [ParamArray] String* names[]);
		botNET::Units::Items* GetByItemCode(bool negate, [ParamArray] String* codes[]);

		static botNET::Units::Items* op_Addition(botNET::Units::Items* lhs, botNET::Units::Items* rhs);
		static botNET::Units::Items* op_Subtraction(botNET::Units::Items* lhs, botNET::Units::Items* rhs);

		botNET::Units::Item* ToArray() __gc[];

    public private:
		Items(UnitAny* unit);
		Items(UnitAny* unit, ItemLocation location);
	};


}

}

#endif