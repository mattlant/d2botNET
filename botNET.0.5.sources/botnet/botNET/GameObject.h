#ifndef OBJECTUNIT_H
#define OBJECTUNIT_H

#include "unitbase.h"

using namespace System::Runtime::Serialization;

namespace botNET
{


namespace Units
{

	public __gc class RosterPlayer;
	public __gc class PresetUnit;

	public __gc class GameObject : public UnitBase, public ISerializable
	{
	public:
		GameObject(void);
		GameObject(PresetUnit* p);
		GameObject(int ClassID);
		GameObject(int ClassID, int mode);
		GameObject(String* name);
		GameObject(String* name, int mode);
		GameObject(UInt32 UniqueID);
		GameObject(SerializationInfo* info, StreamingContext* context);
		~GameObject(void);

		__property String * get_Name();
		__property GameObjectMode get_Mode();
		__property AreaLevel get_DestinationArea();
		__property RosterPlayer * get_Parent();
		__property Byte get_Flags();
		bool Interact(AreaLevel destination);

		__property botNET::BaseStats::Objects* get_BaseStats_Objects();

		void GetObjectData(SerializationInfo* info, StreamingContext context);

	public private:
		GameObject(UnitAny* u);
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
