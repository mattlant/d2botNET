#ifndef ROOM_H
#define ROOM_H

#include "definitions.h"
#include "ivalid.h"
#include "iposition.h"

namespace botNET {

	namespace Units {
		__gc public class PresetUnit;
	}
	namespace Mapping{

		__gc public class Room : public IValid, public botNET::IPosition
		{
		public:
			static Room	* Get()[]; 
			static Room	* Get(AreaLevel area)[];
			static Room	* Get(AreaLevel area,int x, int y)[];
			static Room	* GetCurrent();

			__property UInt16 get_CollisionData(void)[,]; // inited rooms only
			__property UInt16 get_CollisionDataLowByte(void)[,]; // any room
			__property int get_Number(void);
			__property System::Drawing::Point get_AreaLocation(void);
			__property System::Drawing::Point get_AreaOffsetLocation(void);
			__property AreaLevel get_Area(void);
			__property bool get_IsInitialized(void);
			__property System::Drawing::Point get_Position();
			__property System::Drawing::Rectangle get_Bounds();
			__property System::Drawing::Size get_Size();

			__property int get_X();
			__property int get_Y();





			bool IsValid();
			void IsValidEx();

			///<summary>
			/// Gets the address of the Room. This is good for debugging or exploring memory.
			///</summary>
			__property System::IntPtr get_Pointer();



		public private:
			Room(RoomOther * r);
			static Room * FindRooms(int Area, int x, int y)[];
			RoomOther * room; //the room pointer
			UInt32 internalx;
			UInt32 internaly;

			botNET::Units::PresetUnit* mPresetUnits __gc[];

		};
	}

}

#endif