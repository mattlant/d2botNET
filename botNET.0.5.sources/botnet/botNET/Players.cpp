#include "botnet.h"
#include ".\players.h"

#include "player.h"
#include "pc.h"


namespace botNET
{

namespace Units
{

	Players::Players()
	{
	}

	Players::Players(Player* units[])
	{
		this->Add(units);
	}

	Players::Players(bool all) : UnitCollectionBase(new Player(), all)
	{
	}

	Players::Players([ParamArray] String * names[]) : UnitCollectionBase(new Player(), names)
	{
	}

	Players::Players([ParamArray] int classid __gc[]) : UnitCollectionBase(new Player(), classid)
	{
	}

	Player* Players::get_Item(int index)
	{
		return static_cast<Player*>(List->Item[index]);
	}

	void Players::set_Item(int index, Player* value)
	{
		List->Item[index] = value;
	}

	int Players::Add(Player* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	Players* Players::Add(Player* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	Players* Players::Add(Players* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int Players::IndexOf(Player* value)
	{
		return (List->IndexOf(value));
	}

	void Players::Insert(int index, Player* value) 
	{
		List->Insert(index, value);
	}

	void Players::Remove(Player* value)
	{
		List->Remove(value);
	}

	bool Players::Contains(Player* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//Players* Players::Get(PlayerMode Modes[]) 
	//{
	//	return 0;
	//}


	Player* Players::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	Player* Players::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	Player* Players::GetClosest(System::Drawing::Point c)
	{
		Player* ret = static_cast<Player*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new Player();
	}

	Players* Players::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	Players* Players::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	Players* Players::GetByMode([ParamArray] PlayerMode modes __gc[])
	{
		return GetByMode(false, modes);
	}

	Players* Players::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	Players* Players::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	Players* Players::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	Players* Players::GetByName([ParamArray] String* names[])
	{
		return GetByName(false, names);
	}

	Players* Players::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		Players* temp = new Players();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	Players* Players::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		Players* temp = new Players();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	Players* Players::GetByMode(bool negate, [ParamArray] PlayerMode modes __gc[])
	{
		Players* temp = new Players();
		__super::GetByMode(temp, negate, static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	Players* Players::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		Players* temp = new Players();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	Players* Players::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		Players* temp = new Players();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	Players* Players::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		Players* temp = new Players();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	Players* Players::GetByName(bool negate, [ParamArray] String* names[])
	{
		Players* temp = new Players();
		__super::GetByName(temp, negate, names);
		return temp;
	}

	Player* Players::ToArray() __gc[]
	{
		Player* temp __gc[] = new Player* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}

	Players* Players::op_Addition(Players* lhs, Players* rhs)
	{
		Players* temp = new Players();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	Players* Players::op_Subtraction(Players* lhs, Players* rhs)
	{
		Players* temp = new Players();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
    
}


}