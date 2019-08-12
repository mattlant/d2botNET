#ifndef WARPCOLLECTION_H
#define WARPCOLLECTION_H

using namespace System;
using namespace System::Collections;

#include "UnitCollectionBase.h"


namespace botNET
{

namespace Units
{

	public __gc class Warp;

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class Warps : public UnitCollectionBase
	{
	public:
		Warps();
		Warps(Warp* units[]);
		Warps(bool all);
		Warps([ParamArray] String * names[]);
		Warps([ParamArray] int classid __gc[]);

		__property Warp* get_Item( int index );
		__property void set_Item( int index, Warp* value );
		int Add(Warp* value);
		Warps* Add(Warp* WarpsToAdd[]);
		Warps* Add(Warps* WarpsToAdd);
		int IndexOf(Warp* value);
		void Warps::Insert(int index, Warp* value); 
		void Warps::Remove(Warp* value);
		bool Warps::Contains(Warp* value);


		Warp* GetClosest();
		Warp* GetClosest(System::Drawing::Point c);
		Warp* GetClosest(UnitBase* p);

		Warps* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		Warps* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Warps* GetByMode([ParamArray] int modes __gc[]);
		Warps* GetByClassID([ParamArray] int classid __gc[]);
		Warps* GetByState([ParamArray] StateType states __gc[]);
		Warps* GetByStat([ParamArray] StatType stats __gc[]);

		Warps* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		Warps* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		Warps* GetByMode(bool negate, [ParamArray] int modes __gc[]);
		Warps* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		Warps* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		Warps* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);


		static Warps* op_Addition(Warps* lhs, Warps* rhs);
		static Warps* op_Subtraction(Warps* lhs, Warps* rhs);

		Warp* ToArray() __gc[];

	};


}

}

#endif