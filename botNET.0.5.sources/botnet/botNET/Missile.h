#ifndef MISSILEUNIT_H
#define MISSILEUNIT_H

#include "unitbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{

namespace Units
{

	public __gc class PlayerNPCBase;

	public __gc class Missile : public UnitBase, public ISerializable
	{
	public:
		Missile(void);
		Missile(int ClassID);
		Missile(UInt32 UniqueID);
		Missile(SerializationInfo* info, StreamingContext* context);
		~Missile(void);

		//__property Unit * get_Parent();
		__property PlayerNPCBase * get_Target();
		__property int get_Mode();

		void GetObjectData(SerializationInfo* info, StreamingContext context);

	public private:
		Missile(UnitAny* u);
		virtual UnitBase* CreateNew(UnitAny* u);
		virtual UnitBase* CreateNew();
		__property botNET::BaseStats::Missiles* get_BaseStats_Missiles();

    protected:
        virtual void Dispose(bool disposing);

	private:
		bool disposed;
	};

}

}

#endif
