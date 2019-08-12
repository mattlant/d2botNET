#include "botnet.h"
#include ".\items.h"

#include "d2client.h"
#include "d2common.h"

#include "Item.h"
#include "Game.h"
#include "PC.h"

namespace botNET
{

namespace Units
{

	Items::Items()
	{
	}

	Items::Items(botNET::Units::Item* units[])
	{
		this->Add(units);
	}

	Items::Items(bool all) : UnitCollectionBase(new botNET::Units::Item(), all)
	{
	}

    /*Items::Items(ItemLocation location) : UnitCollectionBase()
    {
		return Items (new ItemLocation[] {location});
    }*/

    Items::Items([ParamArray] ItemLocation location[]) : UnitCollectionBase()
    {
 		Game::InGameCheck();

        // if 0 items found, return
		if( (*D2CLIENT::PlayerUnit)->ptInventory->NumItems == 0 )
			return;

        // build item collection
		UnitItem * item = D2COMMON::GetFirstInventoryItem((*D2CLIENT::PlayerUnit)->ptInventory);
		while(item)
		{
			//if (item->ptItemData->Location == location)
			//	Add(new botNET::Units::Item(item));
			for (int i = 0; i < location->Length; i++)
			{
				if (item->ptItemData->Location == location[i])
					Add(new botNET::Units::Item(item));
			}	
			item = D2COMMON::GetNextInventoryItem(item);
		}
	}

    Items::Items(UnitAny* unit, ItemLocation location) : UnitCollectionBase()
    {
        // if 0 items found, return
		if( unit->ptInventory->NumItems == 0 )
			return;

        // build item collection
		UnitItem * item = D2COMMON::GetFirstInventoryItem(unit->ptInventory);

		if(location == ItemLocation::Store)
		{
			while(item)
			{
				List->Add(new botNET::Units::Item(item));
				item = D2COMMON::GetNextInventoryItem(item);
			}
		}
		else
		{
			while(item)
			{
				if(item->ptItemData->Location == location)
					List->Add(new botNET::Units::Item(item));
				item = D2COMMON::GetNextInventoryItem(item);
			}
		}
    }

	Items::Items([ParamArray] String * names[]) : UnitCollectionBase(new botNET::Units::Item(), names)
	{
	}

	Items::Items([ParamArray] int classid __gc[]) : UnitCollectionBase(new botNET::Units::Item(), classid)
	{
	}

    Items::Items(UnitAny* unit)
    {
		if( !unit || !unit->ptInventory->NumItems)
			return;

		UnitItem* item = D2COMMON::GetFirstInventoryItem(unit->ptInventory);
		while(item)
		{
            Add( new botNET::Units::Item(item) );
			item = D2COMMON::GetNextInventoryItem(item);
		}
    }

	botNET::Units::Item* Items::get_Item(int index)
	{
		return static_cast<botNET::Units::Item*>(List->Item[index]);
	}

	void Items::set_Item(int index, botNET::Units::Item* value)
	{
		List->Item[index] = value;
	}

	int Items::Add(botNET::Units::Item* value)
	{
		if(!this->DisableInvalidUnitRemoval && !value->IsValid()) return 0;
		return (List->Add(value));
	}

	Items* Items::Add(botNET::Units::Item* units[])
	{
		for(int i = 0; i < units->Count; i++)
			this->Add(units[i]);
		return this;
	}

	Items* Items::Add(Items* units)
	{
		IEnumerator* pl = units->GetEnumerator();
		while(pl->MoveNext())
			this->List->Add(pl->Current);
		return this;
	}

	int Items::IndexOf(botNET::Units::Item* value)
	{
		return (List->IndexOf(value));
	}

	void Items::Insert(int index, botNET::Units::Item* value) 
	{
		List->Insert(index, value);
	}

	void Items::Remove(botNET::Units::Item* value)
	{
		List->Remove(value);
	}

	bool Items::Contains(botNET::Units::Item* value)
	{
		// If value is not of type Int16, this will return false.
		return (List->Contains(value));
	}

	
	//Items* Items::Get(ItemMode Modes[]) 
	//{
	//	return 0;
	//}


	botNET::Units::Item* botNET::Units::Items::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	botNET::Units::Item* botNET::Units::Items::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	botNET::Units::Item* botNET::Units::Items::GetClosest(System::Drawing::Point c)
	{
		botNET::Units::Item* ret = static_cast<botNET::Units::Item*>(__super::GetClosest(c));
		return ret->IsValid()?ret:new botNET::Units::Item();
	}

	botNET::Units::Items* botNET::Units::Items::GetByRectangle(System::Drawing::Rectangle r __gc[])
	{
		return GetByRectangle(false, r);
	}

	botNET::Units::Items* botNET::Units::Items::GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		return GetByPoint(false, radius, c);
	}

	botNET::Units::Items* botNET::Units::Items::GetByMode([ParamArray] ItemMode modes __gc[])
	{
		return GetByMode(false, modes);
	}

	botNET::Units::Items* botNET::Units::Items::GetByClassID([ParamArray] int classid __gc[])
	{
		return GetByClassID(false, classid);
	}

	botNET::Units::Items* botNET::Units::Items::GetByState([ParamArray] StateType states __gc[])
	{
		return GetByState(false, states);
	}

	botNET::Units::Items* botNET::Units::Items::GetByStat([ParamArray] StatType stats __gc[])
	{
		return GetByStat(false, stats);
	}

	botNET::Units::Items* botNET::Units::Items::GetByName([ParamArray] String* names[])
	{
		return GetByName(false, names);
	}
	
	botNET::Units::Items* botNET::Units::Items::GetByRectangle(bool negate, System::Drawing::Rectangle r __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByRectangle(temp, negate, r);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByPoint(temp, negate, radius, c);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByMode(bool negate, [ParamArray] ItemMode modes __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByMode(temp, negate, static_cast<UnitBaseMode __gc[]>(modes));
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByClassID(bool negate, [ParamArray] int classid __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByClassID(temp, negate, classid);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByState(bool negate, [ParamArray] StateType states __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByState(temp, negate, states);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByStat(bool negate, [ParamArray] StatType stats __gc[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByStat(temp, negate, stats);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByName(bool negate, [ParamArray] String* names[])
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		__super::GetByName(temp, negate, names);
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::GetByItemCode([ParamArray] String* codes[])
	{
		return GetByItemCode(false, codes);
	}

	botNET::Units::Items* botNET::Units::Items::GetByItemCode(bool negate, [ParamArray] String* codes[])
	{
		Items* coll = new Items();
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			botNET::Units::Item* curr = static_cast<botNET::Units::Item*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < codes->Length; n++)
			{
				if(negate ? !(String::Compare(curr->Code, 0, codes[n], 0, codes[n]->Length, true) == 0) : 
					(String::Compare(curr->Code, 0, codes[n], 0, codes[n]->Length, true) == 0) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
		return coll;
	}

	botNET::Units::Item* botNET::Units::Items::ToArray() __gc[]
	{
		botNET::Units::Item* temp __gc[] = new botNET::Units::Item* [this->List->Count];
		for(int i = 0; i < this->Count; i++)
		{
			temp[i] = this->Item[i];
		}
		return temp;
	}

	botNET::Units::Items* botNET::Units::Items::op_Addition(botNET::Units::Items* lhs, botNET::Units::Items* rhs)
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		temp->Add(lhs);
		temp->Add(rhs);
		return temp;
	}
    
	botNET::Units::Items* botNET::Units::Items::op_Subtraction(botNET::Units::Items* lhs, botNET::Units::Items* rhs)
	{
		botNET::Units::Items* temp = new botNET::Units::Items();
		temp->Add(lhs);
		for(int i = 0; i < rhs->Count; i++)
		{
			temp->Remove(rhs->Item[i]);
		}
		return temp;
	}
}

}