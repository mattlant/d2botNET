#include "botnet.h"
#include ".\unitcollectionbase.h"

#include "unitbase.h"
#include "distance.h"
#include "pc.h"

#include "d2client.h"
#include "d2common.h"


namespace botNET
{

namespace Units
{

	UnitCollectionBase::UnitCollectionBase()
	{
	}

	UnitCollectionBase::UnitCollectionBase(UnitBase* list[])
	{
		IEnumerator* ub = list->GetEnumerator();
		while(ub->MoveNext())
		{
			UnitBase* temp = static_cast<UnitBase*>(ub->Current);
			if(temp->IsValid())
				this->Add(static_cast<UnitBase*>(ub->Current));
		}
	}

	UnitCollectionBase::UnitCollectionBase(UnitBase* type, bool all)
	{
		if(all)
		{
			::Room1 * room = (*D2CLIENT::PlayerUnit)->hPath->ptRoom;

			for(int i = 0; i < room->NumRooms; i++)
			{
				if(room) 
				{ //found a room, so lets get the units in it
					UnitAny * u = room->ptRoomList[i]->ptFirstUnit;
					if(u) 
					{
						do 
						{
							if(u->dwType == type->Type)
								this->Add(type->CreateNew(u));
						}while(u = u->ptListNext);
					}
				}
			}	
		}
	}

	UnitCollectionBase::UnitCollectionBase(UnitBase* type, [ParamArray] String * names[])
	{
		Int32 empty[] = __gc new Int32[0];
		this->Populate(type, empty, names);
	}

	UnitCollectionBase::UnitCollectionBase(UnitBase* type, [ParamArray] int classid __gc[])
	{
		this->Populate(type, classid, new String* __gc[0]);
	}

	void UnitCollectionBase::Reverse()
	{
		this->InnerList->Reverse();
	}

	void UnitCollectionBase::Reverse(int index, int count)
	{
		this->InnerList->Reverse();
	}

	void UnitCollectionBase::Sort()
	{
		this->InnerList->Sort();
	}

	void UnitCollectionBase::Sort(IComparer* comparer)
	{
		this->InnerList->Sort(comparer);
	}

	void UnitCollectionBase::Sort(int index, int count, IComparer* comparer)
	{
		this->InnerList->Sort(index, count, comparer);
	}

	bool UnitCollectionBase::get_IsSynchronized()
	{
		return this->InnerList->IsSynchronized;
	}

	System::Object* UnitCollectionBase::get_SyncRoot()
	{
		return this->InnerList->SyncRoot;
	}

	UnitBase* UnitCollectionBase::GetClosest()
	{
		return this->GetClosest(PC::Me->Position);
	}

	UnitBase* UnitCollectionBase::GetClosest(UnitBase* p)
	{
		return this->GetClosest(p->Position);
	}

	UnitBase* UnitCollectionBase::GetClosest(System::Drawing::Point c)
	{
		UnitBase* closest;
		int closestdist = Int32::MaxValue;

		IEnumerator* ub = this->GetEnumerator();
		while(ub->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ub->Current);
			if(!curr->IsValid()) continue;
			int currdist = (int)Distance::Euclidian(c, curr->Position);
			if(currdist < closestdist)
			{
				closest = curr;
				closestdist = currdist;
			}
		}

		return closest?closest:new UnitBase(); //check for valid in child class
	}

	void UnitCollectionBase::GetByRectangle(UnitCollectionBase* coll, bool negate, [ParamArray] System::Drawing::Rectangle r __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < r->Length; n++)
			{
				if(negate ? !r[n].Contains(curr->Position) : r[n].Contains(curr->Position) )
					coll->Add(curr);
			}
		}
	}

	void UnitCollectionBase::GetByPoint(UnitCollectionBase* coll, bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < c->Length; n++)
			{
				if(negate ? !(Distance::Euclidian(curr->Position, c[n]) < radius) : (Distance::Euclidian(curr->Position, c[n]) < radius))
					coll->Add(curr);
			}
		}
	}

	void UnitCollectionBase::GetByMode(UnitCollectionBase* coll, bool negate, [ParamArray] UnitBaseMode modes __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < modes->Length; n++)
			{
				if(negate ? !(curr->unit->dwMode == modes[n]) : (curr->unit->dwMode == modes[n]) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
	}

	void UnitCollectionBase::GetByClassID(UnitCollectionBase* coll, bool negate, [ParamArray] int classid __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < classid->Length; n++)
			{
				if(negate ? !(curr->unit->dwClassId == classid[n]) : (curr->unit->dwClassId == classid[n]) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
	}

	void UnitCollectionBase::GetByState(UnitCollectionBase* coll, bool negate, [ParamArray] StateType states __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < states->Length; n++)
			{
				if(negate ? !(curr->GetState(states[n])) : (curr->GetState(states[n])) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
	}

	void UnitCollectionBase::GetByStat(UnitCollectionBase* coll, bool negate, [ParamArray] StatType stats __gc[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < stats->Length; n++)
			{
				if(negate ? !(curr->GetStat(stats[n]) > 0) : (curr->GetStat(stats[n]) > 0) )
				{
					coll->Add(curr);
					break;
				}
			}
		}
	}

	void UnitCollectionBase::GetByName(UnitCollectionBase* coll, bool negate, [ParamArray] String* names[])
	{
		IEnumerator* ecoll = this->List->GetEnumerator();
		while(ecoll->MoveNext())
		{
			UnitBase* curr = static_cast<UnitBase*>(ecoll->Current);
			if(!curr->IsValid()) continue;
			for(int n = 0; n < names->Length; n++)
			{
				if(negate ? !(String::Compare(curr->Name, 0, names[n], 0, names[n]->Length, true) == 0) : (String::Compare(curr->Name, 0, names[n], 0, names[n]->Length, true) == 0))
				{
					coll->Add(curr);
					break;
				}
			}
		}
	}

	///Private
	void UnitCollectionBase::Populate(UnitBase* type, int id __gc[], String* name[])
	{
		//Add in check if in game
		//::Room * room = D2COMMON::GetRoomFromUnit(player);
		::Room1 * room = (*D2CLIENT::PlayerUnit)->hPath->ptRoom;

		for(int i = 0; i < room->NumRooms; i++)
		{
			if(room) 
			{ //found a room, so lets get the units in it
				UnitAny * u = room->ptRoomList[i]->ptFirstUnit;
				if(u) 
				{
					do 
					{
						//make sure it is the right type
						if((int)u->dwType != type->type) continue;
						//check id's
						for(int n = 0; n < id->Length; n++)
							if(u->dwClassId == id[n]) goto outofloop;

						//check names
						for(int n = 0; n < name->Length; n++)
							if(String::Compare(Convert::ToString(D2CLIENT::GetNameFromUnit(u)), 
								0, name[n], 0, name[n]->Length, true) == 0) goto outofloop;
						//continue if we reach this point since nothing matched
						continue;
outofloop:
						//Now we have a valid unit to add to the collection
						this->Add(type->CreateNew(u));
					}while(u = u->ptListNext);
				}
			}
		}
	}


}

}