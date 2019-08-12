#ifndef PRESETUNIT_H
#define PRESETUNIT_H

#include "ientity.h"

namespace botNET {

namespace Mapping{
__gc public class Room;
}

namespace Units
{
	///<summary>
	/// Defines a Preset Unit
	///</summary>
	__gc public class PresetUnit : public IEntity
	{
	public:

		static PresetUnit* Get()[];
		static PresetUnit* Get(AreaLevel AreaID)[];
		static PresetUnit* Get(AreaLevel AreaID, UnitType Type)[];
		static PresetUnit* Get(AreaLevel AreaID, UnitType Type, UInt32 ID)[];
		static PresetUnit* Get(AreaLevel AreaID, UnitType Type, UInt32 ID, int RoomID __gc[])[];

		__property UnitType get_Type();

		__property int get_ClassID();
		__property int get_X();
		__property int get_Y();
		__property AreaLevel get_Area();


		__property System::Drawing::Point get_Position();


		int GetHashCode();
		bool Equals(Object* obj);
		String* ToString();
		static bool op_Equality(PresetUnit* lhs, PresetUnit* rhs);
		static bool op_Inequality(PresetUnit* lhs, PresetUnit* rhs);

	public private:

		///<summary>
		/// Initializes a new instance of the PresetUnit class.
		///</summary>
		/// <param name="X">The X coordinate to click at</param>
		/// <param name="Y">The Y coordinate to click at</param>
		PresetUnit(UnitType Type, UInt32 ID, int X, int Y, AreaLevel areaid);
		~PresetUnit(void);
		UnitType type;
		UInt32 id;
		AreaLevel area;
		int x;
		int y;

	};

}

}

#endif