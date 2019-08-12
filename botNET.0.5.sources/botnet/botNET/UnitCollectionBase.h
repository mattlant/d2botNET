#ifndef UNITBASECOLLECTION_H
#define UNITBASECOLLECTION_H

using namespace botNET::Mapping;

#include "unitstat.h"

namespace botNET
{

namespace Units
{

	public __gc class UnitBase;

	public __gc class UnitCollectionBase : public System::Collections::CollectionBase
	{
	public:
		bool DisableInvalidUnitRemoval;

		void Reverse();
		void Reverse(int index, int count);

		void Sort();
		void Sort(IComparer* comparer);
		void Sort(int index, int count, IComparer* comparer);

		__property bool get_IsSynchronized();
		__property Object* get_SyncRoot();

	public private:
		UnitCollectionBase();
		UnitCollectionBase(UnitBase* list[]);
		UnitCollectionBase(UnitBase* type, bool all);
		UnitCollectionBase(UnitBase* type, [ParamArray] String * names[]);
		UnitCollectionBase(UnitBase* type, [ParamArray] int classid __gc[]);

		UnitBase* GetClosest();
		UnitBase* GetClosest(System::Drawing::Point c);
		UnitBase* GetClosest(UnitBase* p);

		void GetByPoint(UnitCollectionBase* coll,  bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		void GetByRectangle(UnitCollectionBase* coll, bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		void GetByMode(UnitCollectionBase* coll, bool negate, [ParamArray] UnitBaseMode modes __gc[]);
		void GetByClassID(UnitCollectionBase* coll, bool negate, [ParamArray] int classid __gc[]);
		void GetByState(UnitCollectionBase* coll, bool negate, [ParamArray] StateType states __gc[]);
		void GetByStat(UnitCollectionBase* coll, bool negate, [ParamArray] StatType stats __gc[]);
		//void GetByStat(UnitCollectionBase* coll, bool negate, [ParamArray] UnitStat stats __gc[]); //Greater than the stat value
		void GetByName(UnitCollectionBase* coll, bool negate, [ParamArray] String* names[]);


		void Populate(UnitBase* type, int id __gc[], String* name[]);

	
		//UnitBaseCollection* GetLOS

//so rso, LOS, Immunities/enchants/auras, and x,y,radius, getclosest
	};


}

}

#endif