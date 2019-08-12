#ifndef UNITSTAT_H
#define UNITSTAT_H

//#include

namespace botNET
{
	namespace Units
	{

		public __value struct UnitStat
		{
		public:
			UnitStat(UInt16 id, UInt16 index, UInt32 value) : Index(index), ID(id), Value(value) {}
			UInt16 Index;
			UInt16 ID;
			UInt32 Value;
		};

	}

}

#endif