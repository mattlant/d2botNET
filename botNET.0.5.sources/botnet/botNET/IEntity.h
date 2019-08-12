#ifndef IENTITY_H
#define IENTITY_H

#include "iposition.h"
#include "ivalid.h"

using namespace System;

namespace botNET
{
namespace Units
{
	__gc public __interface IEntity : public IPosition
	{
	public:
		__property UnitType get_Type();
		__property int get_ClassID();
		__property AreaLevel get_Area();
	};
}
}

#endif