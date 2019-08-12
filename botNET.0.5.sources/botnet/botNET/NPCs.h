#ifndef NPCCOLLECTION_H
#define NPCCOLLECTION_H

#include "UnitCollectionBase.h"

namespace botNET
{

namespace Units
{

	public __gc class NPC;

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class NPCs : public UnitCollectionBase
	{
	public:
		NPCs();
		NPCs(NPC* units[]);
		NPCs(bool all);
		NPCs([ParamArray] String * names[]);
		NPCs([ParamArray] int classid __gc[]);

		__property NPC* get_Item( int index );
		__property void set_Item( int index, NPC* value );
		int Add(NPC* value);
		NPCs* Add(NPC* NPCsToAdd[]);
		NPCs* Add(NPCs* NPCsToAdd);
		int IndexOf(NPC* value);
		void NPCs::Insert(int index, NPC* value); 
		void NPCs::Remove(NPC* value);
		bool NPCs::Contains(NPC* value);


		NPC* GetClosest();
		NPC* GetClosest(System::Drawing::Point c);
		NPC* GetClosest(UnitBase* p);

		NPCs* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		NPCs* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		NPCs* GetByMode([ParamArray] NPCMode modes __gc[]);
		NPCs* GetByClassID([ParamArray] int classid __gc[]);
		NPCs* GetByState([ParamArray] StateType states __gc[]);
		NPCs* GetByStat([ParamArray] StatType stats __gc[]);
		NPCs* GetByName([ParamArray] String* names[]);

		NPCs* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		NPCs* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		NPCs* GetByMode(bool negate, [ParamArray] NPCMode modes __gc[]);
		NPCs* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		NPCs* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		NPCs* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);
		NPCs* GetByName(bool negate, [ParamArray] String* names[]);

		NPCs* GetByResistance([ParamArray] StatType resistances __gc[]);
		NPCs* GetByResistance(bool negate, [ParamArray] StatType resistances __gc[]);

		NPCs* GetByEnchantment([ParamArray] EnchantmentType enchants __gc[]);
		NPCs* GetByEnchantment(bool negate, [ParamArray] EnchantmentType enchants __gc[]);

		static NPCs* op_Addition(NPCs* lhs, NPCs* rhs);
		static NPCs* op_Subtraction(NPCs* lhs, NPCs* rhs);

		NPC* ToArray() __gc[];

	};


}

}

#endif