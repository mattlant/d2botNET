#ifndef BASEUNITINFO_H
#define BASEUNITINFO_H

#include "standardenumerations.h"

namespace botNET
{

	namespace Units
	{

		__value public struct UnitInfo
		{
			public:
				UnitInfo(UnitType type, UInt32 uniqueid)
				{
					this->mUniqueID = uniqueid;
					this->mType = type;
				}

				__property UInt32		get_UniqueID(void) { return this->mUniqueID; }
				__property UnitType		get_Type(void) { return this->mType; }

				String* ToString() { return String::Concat(S"{Type: ", this->mUniqueID.ToString(), S" UniqueID: ", ((int)this->mType).ToString(), S"}"); }

			private:
				UInt32		mUniqueID;
				UnitType	mType;
		};

	}

}


#endif
