#ifndef VERIFY_H
#define VERIFY_H

#include ".\rosterPlayer.h"
#include ".\presetunit.h"

using namespace botNET::Units;

namespace botNET
{
	__gc public __interface IValid;
	namespace Units
	{
			__gc public class UnitBase;
	}
	namespace Utils
	{
		__gc public class Verify
		{
		public:

			static void Verify::IsValidArgEx(botNET::IValid* unit);

			static bool Verify::IsValid(RosterPlayer * player);

			static bool Verify::IsValid(botNET::Units::PresetUnit * presetunit);


			static bool Verify::IsInvalid(botNET::Units::PresetUnit * presetunit);

			static bool Verify::IsInvalid(RosterPlayer * player);



		};
	}
}

#endif