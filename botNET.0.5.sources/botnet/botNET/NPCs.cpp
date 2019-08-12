#include "botnet.h"
#include ".\npcs.h"

#include "pc.h"
#include "npc.h"


namespace botNET
{

namespace Units
{

	NPCs::NPCs()
	{
	}

	NPCs::NPCs(NPC* units[])
	{
		this->Add(units);
	}

	NPCs::NPCs(bool all) : UnitCollectionBase(new NPC(), all)
	{
	}

	NPCs::NPCs([ParamArray] String * names[]) : UnitCollectionBase(new NPC(), names)
	{
	}

	NPCs::NPCs([ParamArray] int classid __gc[]) : UnitCollectionBase(new NPC(), classid)
	{
	}

	NPC* NPCs::get_Item(int index)
	{
		return static_cast<NPC*>(List->Item[index]);
	}

	void NPCs::set_Item(int index, NPC* value)
	{
		List->Item[index] = value;
	}

	int NPCs::Add(NPC* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	NPCs* NPCs::Add(NPC* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	NPCs* NPCs::Add(NPCs* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int NPCs::IndexOf(NPC* value)
	{
		return (List->IndexOf(value));
	}

	void NPCs::Insert(int index, NPC* value) 
	{
		List->Insert(index, value);
	}

	void NPCs::Remove(NPC* value)
	{
		List->Remove(value);
	}

	bool NPCs::Contains(NPC* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//NPCs* NPCs::Get(NPCMode Modes[]) 
	//{
	//	return 0;
	//}

	NPC* NPCs::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	NPC* NPCs::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	NPC* NPCs::GetClosest(System::Drawing::Point c)
	{
		NPC* ret = static_cast<NPC*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new NPC();
	}

	NPCs* NPCs::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	NPCs* NPCs::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	NPCs* NPCs::GetByMode([ParamArray] NPCMode modes __gc[])
	{
		return GetByMode(false, static_cast<UnitBaseMode __gc[]>(modes));
	}

	NPCs* NPCs::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	NPCs* NPCs::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	NPCs* NPCs::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	NPCs* NPCs::GetByName([ParamArray] String* names[])
	{
		return GetByName(false, names);
	}

	NPCs* NPCs::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	NPCs* NPCs::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	NPCs* NPCs::GetByMode(bool negate, [ParamArray] NPCMode modes __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByMode(temp,negate,  static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	NPCs* NPCs::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	NPCs* NPCs::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	NPCs* NPCs::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		NPCs* temp = new NPCs();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	NPCs* NPCs::GetByName(bool negate, [ParamArray] String* names[])
	{
		NPCs* temp = new NPCs();
		__super::GetByName(temp, negate, names);
		return temp;
	}

	NPCs* NPCs::GetByResistance([ParamArray] StatType resistances __gc[])
	{
		return GetByResistance(false, resistances);
	}

	NPCs* NPCs::GetByResistance(bool negate, [ParamArray] StatType resistances __gc[])
	{
		NPCs* coll = new NPCs();
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			NPC* curr = static_cast<NPC*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < resistances->Length; n++)
			{
				if(negate ? !(curr->GetStat(resistances[n]) > 99) : (curr->GetStat(resistances[n]) > 99) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
		return coll;
	}

	NPCs* NPCs::GetByEnchantment([ParamArray] EnchantmentType enchants __gc[])
	{
		return GetByEnchantment(false, enchants);
	}

	NPCs* NPCs::GetByEnchantment(bool negate, [ParamArray] EnchantmentType enchants __gc[])
	{
		NPCs* coll = new NPCs();
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			NPC* curr = static_cast<NPC*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < enchants->Length; n++)
			{
				if(negate ? !(curr->HasEnchantment(enchants[n])) : (curr->HasEnchantment(enchants[n])) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
		return coll;
	}


	NPC* NPCs::ToArray() __gc[]
	{
		NPC* temp __gc[] = new NPC* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}

	NPCs* NPCs::op_Addition(NPCs* lhs, NPCs* rhs)
	{
		NPCs* temp = new NPCs();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	NPCs* NPCs::op_Subtraction(NPCs* lhs, NPCs* rhs)
	{
		NPCs* temp = new NPCs();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
}


}