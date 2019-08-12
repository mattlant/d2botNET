#ifndef MISSILECOLLECTION_H
#define MISSILECOLLECTION_H

#include "UnitCollectionBase.h"


namespace botNET
{

namespace Units
{
	public __gc class Missile;

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class Missiles : public UnitCollectionBase
	{
	public:
		Missiles();
		Missiles(Missile* units[]);
		Missiles(bool all);
		Missiles([ParamArray] String * names[]);
		Missiles([ParamArray] int classid __gc[]);

		__property Missile* get_Item( int index );
		__property void set_Item( int index, Missile* value );
		int Add(Missile* value);
		Missiles* Add(Missile* MissilesToAdd[]);
		Missiles* Add(Missiles* MissilesToAdd);
		int IndexOf(Missile* value);
		void Missiles::Insert(int index, Missile* value); 
		void Missiles::Remove(Missile* value);
		bool Missiles::Contains(Missile* value);


		Missile* GetClosest();
		Missile* GetClosest(System::Drawing::Point c);
		Missile* GetClosest(UnitBase* p);

		Missiles* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		Missiles* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Missiles* GetByMode([ParamArray] int modes __gc[]);
		Missiles* GetByClassID([ParamArray] int classid __gc[]);
		Missiles* GetByState([ParamArray] StateType states __gc[]);
		Missiles* GetByStat([ParamArray] StatType stats __gc[]);

		Missiles* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		Missiles* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Missiles* GetByMode(bool negate, [ParamArray] int modes __gc[]);
		Missiles* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		Missiles* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		Missiles* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);


		static Missiles* op_Addition(Missiles* lhs, Missiles* rhs);
		static Missiles* op_Subtraction(Missiles* lhs, Missiles* rhs);

		Missile* ToArray() __gc[];

	};


}

}

#endif