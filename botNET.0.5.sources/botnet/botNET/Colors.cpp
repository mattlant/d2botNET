#include "Colors.h"

namespace botNET
{
	__gc public class Colors
	{
		static Colors() { /* Game.Print("All the pretty colors!"); */ }

	public:

		static const System::String * Black = "\u00ffc6";
		static const System::String * Blue = "\u00ffc3";
		static const System::String * Gold = "\u00ffc4";
		static const System::String * Gold2 = "\u00ffc7";
		static const System::String * Green = "\u00ffc2";
		static const System::String * Green2 = "\u00ffc:";
		static const System::String * Green3 = "\u00ffc<";
		static const System::String * Grey = "\u00ffc5";
		static const System::String * Orange = "\u00ffc8";
		static const System::String * Purple = "\u00ffc;";
		static const System::String * Red = "\u00ffc1";
		static const System::String * Reset = "\u00ffcr"; // Any invalid color works
		static const System::String * White = "\u00ffc0";
		static const System::String * Yellow = "\u00ffc9";

		static const System::String * Bold = "\u00ffc\"";
		static const System::String * Bold2 = "\u00ffc/";
		static const System::String * Bold3 = "\u00ffc'";

		static const System::String * Boldest1 = "\u00ffc.";
		static const System::String * Boldest2 = "\u00ffc,";
		static const System::String * Boldest3 = "\u00ffc-";
		static const System::String * Boldest4 = "\u00ffc+";

		
	};

}