#ifndef WARPUNIT_H
#define WARPUNIT_H

#include "unitbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{

namespace Units
{

	public __gc class PresetUnit;

	public __gc class Warp : public UnitBase
	{
	public:
		Warp(void);
		Warp(PresetUnit* p);
		Warp(int ClassID);
		Warp(UInt32 UniqueID);
		Warp(SerializationInfo* info, StreamingContext* context);
		~Warp(void);

		__property int get_Mode();
		//__property AreaLevel get_DestinationArea();
		void GetObjectData(SerializationInfo* info, StreamingContext context);


	public private:
		Warp(UnitAny* u);
		virtual UnitBase* CreateNew(UnitAny* u);
		virtual UnitBase* CreateNew();

    protected:
        virtual void Dispose(bool disposing);

	private:
		bool disposed;
	};

}

}

#endif
