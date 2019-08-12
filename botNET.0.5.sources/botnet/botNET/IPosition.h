#ifndef IPOSITIONABLE_H
#define IPOSITIONABLE_H

using namespace System;

namespace botNET
{
	__gc public __interface IPosition
	{
	public:
		__property System::Drawing::Point get_Position();
		__property int get_X();
		__property int get_Y();
	};
}

#endif