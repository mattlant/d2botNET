#include "botnet.h"
#include ".\gameobjects.h"

#include "gameobject.h"
#include "pc.h"


namespace botNET
{

namespace Units
{

	GameObjects::GameObjects()
	{
	}

	GameObjects::GameObjects(GameObject* units[])
	{
		this->Add(units);
	}

	GameObjects::GameObjects(bool all) : UnitCollectionBase(new GameObject(), all)
	{
	}

	GameObjects::GameObjects([ParamArray] String * names[]) : UnitCollectionBase(new GameObject(), names)
	{
	}

	GameObjects::GameObjects([ParamArray] int classid __gc[]) : UnitCollectionBase(new GameObject(), classid)
	{
	}

	GameObject* GameObjects::get_Item(int index)
	{
		return static_cast<GameObject*>(List->Item[index]);
	}

	void GameObjects::set_Item(int index, GameObject* value)
	{
		List->Item[index] = value;
	}

	int GameObjects::Add(GameObject* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	GameObjects* GameObjects::Add(GameObject* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	GameObjects* GameObjects::Add(GameObjects* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int GameObjects::IndexOf(GameObject* value)
	{
		return (List->IndexOf(value));
	}

	void GameObjects::Insert(int index, GameObject* value) 
	{
		List->Insert(index, value);
	}

	void GameObjects::Remove(GameObject* value)
	{
		List->Remove(value);
	}

	bool GameObjects::Contains(GameObject* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//GameObjects* GameObjects::Get(GameObjectMode Modes[]) 
	//{
	//	return 0;
	//}


	GameObject* GameObjects::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	GameObject* GameObjects::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	GameObject* GameObjects::GetClosest(System::Drawing::Point c)
	{
		GameObject* ret = static_cast<GameObject*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new GameObject();
	}

	GameObjects* GameObjects::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	GameObjects* GameObjects::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	GameObjects* GameObjects::GetByMode([ParamArray] GameObjectMode modes __gc[])
	{
		return GetByMode(false, modes);
	}

	GameObjects* GameObjects::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	GameObjects* GameObjects::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	GameObjects* GameObjects::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	GameObjects* GameObjects::GetByName([ParamArray] String* names[])
	{
		return GetByName(false, names);
	}

	GameObjects* GameObjects::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	GameObjects* GameObjects::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	GameObjects* GameObjects::GetByMode(bool negate, [ParamArray] GameObjectMode modes __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByMode(temp, negate, static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	GameObjects* GameObjects::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	GameObjects* GameObjects::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	GameObjects* GameObjects::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	GameObjects* GameObjects::GetByName(bool negate, [ParamArray] String* names[])
	{
		GameObjects* temp = new GameObjects();
		__super::GetByName(temp, negate, names);
		return temp;
	}

	GameObject* GameObjects::ToArray() __gc[]
	{
		GameObject* temp __gc[] = new GameObject* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}


	GameObjects* GameObjects::op_Addition(GameObjects* lhs, GameObjects* rhs)
	{
		GameObjects* temp = new GameObjects();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	GameObjects* GameObjects::op_Subtraction(GameObjects* lhs, GameObjects* rhs)
	{
		GameObjects* temp = new GameObjects();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
}


}