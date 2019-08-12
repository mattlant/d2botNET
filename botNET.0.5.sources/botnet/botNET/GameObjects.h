#ifndef GAMEOBJECTCOLLECTION_H
#define GAMEOBJECTCOLLECTION_H

#include "UnitCollectionBase.h"


namespace botNET
{

namespace Units
{

	public __gc class GameObject;

	[System::Reflection::DefaultMemberAttribute(S"Item")]
	public __gc class GameObjects : public UnitCollectionBase
	{
	public:
		GameObjects();
		GameObjects(GameObject* units[]);
		GameObjects(bool all);
		GameObjects([ParamArray] String * names[]);
		GameObjects([ParamArray] int classid __gc[]);

		__property GameObject* get_Item( int index );
		__property void set_Item( int index, GameObject* value );
		int Add(GameObject* value);
		GameObjects* Add(GameObject* GameObjectsToAdd[]);
		GameObjects* Add(GameObjects* GameObjectsToAdd);
		int IndexOf(GameObject* value);
		void GameObjects::Insert(int index, GameObject* value); 
		void GameObjects::Remove(GameObject* value);
		bool GameObjects::Contains(GameObject* value);


		GameObject* GetClosest();
		GameObject* GetClosest(System::Drawing::Point c);
		GameObject* GetClosest(UnitBase* p);

		GameObjects* GetByRectangle([ParamArray] System::Drawing::Rectangle r __gc[]);
		GameObjects* GetByPoint(int radius, [ParamArray] System::Drawing::Point c __gc[]);
		GameObjects* GetByMode([ParamArray] GameObjectMode modes __gc[]);
		GameObjects* GetByClassID([ParamArray] int classid __gc[]);
		GameObjects* GetByState([ParamArray] StateType states __gc[]);
		GameObjects* GetByStat([ParamArray] StatType stats __gc[]);
		GameObjects* GetByName([ParamArray] String* names[]);

		GameObjects* GetByRectangle(bool negate, [ParamArray] System::Drawing::Rectangle r __gc[]);
		GameObjects* GetByPoint(bool negate, int radius, [ParamArray] System::Drawing::Point c __gc[]);
		GameObjects* GetByMode(bool negate, [ParamArray] GameObjectMode modes __gc[]);
		GameObjects* GetByClassID(bool negate, [ParamArray] int classid __gc[]);
		GameObjects* GetByState(bool negate, [ParamArray] StateType states __gc[]);
		GameObjects* GetByStat(bool negate, [ParamArray] StatType stats __gc[]);
		GameObjects* GetByName(bool negate, [ParamArray] String* names[]);

		static GameObjects* op_Addition(GameObjects* lhs, GameObjects* rhs);
		static GameObjects* op_Subtraction(GameObjects* lhs, GameObjects* rhs);

		GameObject* ToArray() __gc[];

	};


}

}

#endif