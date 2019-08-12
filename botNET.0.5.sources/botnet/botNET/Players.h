#ifndef PLAYERCOLLECTION_H
#define PLAYERCOLLECTION_H

#include "UnitCollectionBase.h"

namespace botNET
{

namespace Units
{

	public __gc class Player;

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class Players : public UnitCollectionBase
	{
	public:
		Players();
		Players(Player* units[]);
		Players(bool all);
		Players([ParamArray] String * names[]);
		Players([ParamArray] int classid __gc[]);

		__property Player* get_Item( int index );
		__property void set_Item( int index, Player* value );
		int Add(Player* value);
		Players* Add(Player* PlayersToAdd[]);
		Players* Add(Players* PlayersToAdd);
		int IndexOf(Player* value);
		void Players::Insert(int index, Player* value); 
		void Players::Remove(Player* value);
		bool Players::Contains(Player* value);


		Player* GetClosest();
		Player* GetClosest(System::Drawing::Point c);
		Player* GetClosest(UnitBase* p);

		Players* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		Players* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Players* GetByMode([ParamArray] PlayerMode modes __gc[]);
		Players* GetByClassID([ParamArray] int classid __gc[]);
		Players* GetByState([ParamArray] StateType states __gc[]);
		Players* GetByStat([ParamArray] StatType stats __gc[]);
		Players* GetByName([ParamArray] String* names[]);

		Players* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		Players* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Players* GetByMode(bool negate, [ParamArray] PlayerMode modes __gc[]);
		Players* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		Players* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		Players* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);
		Players* GetByName(bool negate, [ParamArray] String* names[]);

		static Players* op_Addition(Players* lhs, Players* rhs);
		static Players* op_Subtraction(Players* lhs, Players* rhs);

		Player* ToArray() __gc[];

	};


}

}

#endif