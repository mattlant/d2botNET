#ifndef AUTOMAP_H
#define AUTOMAP_H

#include "definitions.h"

using namespace botNET::Units;

namespace botNET
{
	namespace Units
	{
		__gc public class UnitBase;
	}

	namespace Mapping
	{

		__gc public class Room;

		__gc public class AutoMap
		{
		public:
			static void RevealRoom(Mapping::Room * RoomToReveal);
			static bool ConvertCoords(UnitBase * unit, int * X, int * Y);
			static bool ConvertCoords(int * X, int * Y);
			__property static bool get_Visible();

			__event static OnDrawHandler * OnDrawItems;

		private public:
			static void DrawItems();


		};

	}

}

#endif