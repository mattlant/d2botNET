#include "botnet.h"
#include ".\warps.h"

#include "warp.h"
#include "pc.h"

namespace botNET
{

namespace Units
{

	Warps::Warps()
	{
	}

	Warps::Warps(Warp* units[])
	{
		this->Add(units);
	}

	Warps::Warps(bool all) : UnitCollectionBase(new Warp(), all)
	{
	}

	Warps::Warps([ParamArray] String * names[]) : UnitCollectionBase(new Warp(), names)
	{
	}

	Warps::Warps([ParamArray] int classid __gc[]) : UnitCollectionBase(new Warp(), classid)
	{
	}

	Warp* Warps::get_Item(int index)
	{
		return static_cast<Warp*>(List->Item[index]);
	}

	void Warps::set_Item(int index, Warp* value)
	{
		List->Item[index] = value;
	}

	int Warps::Add(Warp* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	Warps* Warps::Add(Warp* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	Warps* Warps::Add(Warps* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int Warps::IndexOf(Warp* value)
	{
		return (List->IndexOf(value));
	}

	void Warps::Insert(int index, Warp* value) 
	{
		List->Insert(index, value);
	}

	void Warps::Remove(Warp* value)
	{
		List->Remove(value);
	}

	bool Warps::Contains(Warp* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//Warps* Warps::Get(WarpMode Modes[]) 
	//{
	//	return 0;
	//}

	Warp* Warps::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	Warp* Warps::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	Warp* Warps::GetClosest(System::Drawing::Point c)
	{
		Warp* ret = static_cast<Warp*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new Warp();
	}

	Warps* Warps::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	Warps* Warps::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	Warps* Warps::GetByMode([ParamArray] int modes __gc[])
	{
		return GetByMode(false, modes);
	}

	Warps* Warps::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	Warps* Warps::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	Warps* Warps::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	Warps* Warps::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	Warps* Warps::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	Warps* Warps::GetByMode(bool negate, [ParamArray] int modes __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByMode(temp, negate, static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	Warps* Warps::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	Warps* Warps::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	Warps* Warps::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		Warps* temp = new Warps();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	Warp* Warps::ToArray() __gc[]
	{
		Warp* temp __gc[] = new Warp* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}

	Warps* Warps::op_Addition(Warps* lhs, Warps* rhs)
	{
		Warps* temp = new Warps();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	Warps* Warps::op_Subtraction(Warps* lhs, Warps* rhs)
	{
		Warps* temp = new Warps();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
}


}