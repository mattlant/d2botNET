#include "botnet.h"
#include ".\missiles.h"

#include "missile.h"
#include "pc.h"

namespace botNET
{

namespace Units
{

	Missiles::Missiles()
	{
	}

	Missiles::Missiles(Missile* units[])
	{
		this->Add(units);
	}

	Missiles::Missiles(bool all) : UnitCollectionBase(new Missile(), all)
	{
	}

	Missiles::Missiles([ParamArray] String * names[]) : UnitCollectionBase(new Missile(), names)
	{
	}

	Missiles::Missiles([ParamArray] int classid __gc[]) : UnitCollectionBase(new Missile(), classid)
	{
	}

	Missile* Missiles::get_Item(int index)
	{
		return static_cast<Missile*>(List->Item[index]);
	}

	void Missiles::set_Item(int index, Missile* value)
	{
		List->Item[index] = value;
	}

	int Missiles::Add(Missile* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	Missiles* Missiles::Add(Missile* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	Missiles* Missiles::Add(Missiles* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int Missiles::IndexOf(Missile* value)
	{
		return (List->IndexOf(value));
	}

	void Missiles::Insert(int index, Missile* value) 
	{
		List->Insert(index, value);
	}

	void Missiles::Remove(Missile* value)
	{
		List->Remove(value);
	}

	bool Missiles::Contains(Missile* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//Missiles* Missiles::Get(MissileMode Modes[]) 
	//{
	//	return 0;
	//}


	Missile* Missiles::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	Missile* Missiles::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	Missile* Missiles::GetClosest(System::Drawing::Point c)
	{
		Missile* ret = static_cast<Missile*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new Missile();
	}

	Missiles* Missiles::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	Missiles* Missiles::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	Missiles* Missiles::GetByMode([ParamArray] int modes __gc[])
	{
		return GetByMode(false, static_cast<UnitBaseMode __gc[]>(modes));
	}

	Missiles* Missiles::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	Missiles* Missiles::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	Missiles* Missiles::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	Missiles* Missiles::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	Missiles* Missiles::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	Missiles* Missiles::GetByMode(bool negate, [ParamArray] int modes __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByMode(temp, negate, static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	Missiles* Missiles::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	Missiles* Missiles::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	Missiles* Missiles::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		Missiles* temp = new Missiles();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	Missile* Missiles::ToArray() __gc[]
	{
		Missile* temp __gc[] = new Missile* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}

	Missiles* Missiles::op_Addition(Missiles* lhs, Missiles* rhs)
	{
		Missiles* temp = new Missiles();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	Missiles* Missiles::op_Subtraction(Missiles* lhs, Missiles* rhs)
	{
		Missiles* temp = new Missiles();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
}


}