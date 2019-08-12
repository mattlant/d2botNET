#ifndef PLAYERNPCBASE_H
#define PLAYERNPCBASE_H

#include "unitbase.h"

namespace botNET
{
namespace Mapping
{
	public __gc class Room;
}
namespace Units
{
	public __gc class PlayerNPCBase : public botNET::Units::UnitBase
	{
	public:
		__property int get_HP();
		__property int get_HPMax();
		__property int get_HPMaxBase();
		__property int get_MP();
		__property int get_MPMax();
		__property int get_MPMaxBase();
		__property int get_Stamina();
		__property int get_StaminaMax();
		__property int get_StaminaMaxBase();

		virtual void Overhead(String * msg);

		__property botNET::Mapping::Room* get_CurrentRoom(void);

	public private:
		PlayerNPCBase(void);
		PlayerNPCBase(UnitAny* u);
		PlayerNPCBase(UnitType type, int ClassID, int mode);
		PlayerNPCBase(UnitType type, String* name, int mode);
		PlayerNPCBase(UnitType type, UInt32 UniqueID);
		~PlayerNPCBase(void);

    protected:
		virtual void Dispose(bool disposing);

	private:
		bool disposed;
	};
}

}

#endif