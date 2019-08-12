#ifndef UNITBASE_H
#define UNITBASE_H

#include "ivalid.h"
#include "definitions.h"
#include "unitstat.h"
#include "ientity.h"


using namespace System::Drawing;

namespace botNET
{

	namespace Messaging
	{
		public __gc class PresetUnit;
	}

	namespace Units
	{


	public __gc class InvalidUnitException;
	public __gc class PresetUnit;
	public __gc class UnitBase : public IDisposable, public botNET::IValid, public botNET::Units::IEntity
		{
		public:
			UnitBase(void);


			bool CompareTo(UnitBase * CompareUnit);

			bool IsValid();
			bool IsValid(bool refresh); //re get if not valid before returning false. return false if reget failed
			//Throw exception if not valid. Useful in libraries.
			void IsValidEx();
			void IsValidEx(bool refresh); //re get if not valid before returning false. return false if reget failed
			//Refresh internal reference
			bool Refresh(); //return false if refresh did not find valid reference

			__property UnitType get_Type();

			__property bool get_Busy();

			__property int get_ClassID();
			__property UInt32 get_UniqueID();

			bool GetState(StateType state);

			int GetStat(StatType stat);
			int GetStat(StatType stat, int sub);

			int GetBaseStat(StatType stat);
			int GetBaseStat(StatType stat, int sub);

			int GetStat3(StatType stat);
			int GetStat3(StatType stat, int sub);

			//Mapping stuff
			__property AreaLevel get_Area();
			__property int get_Act();
			__property int get_X();
			__property int get_Y();
			__property Point get_Position();

			//Misc
			__property IntPtr get_Pointer();

			__property UnitStat get_Stats(void)[];
			__property virtual String* get_Name(); 

			void Dispose();
			bool Equals(UnitBase* ub);
			static bool op_Equality(UnitBase* lhs, UnitBase* rhs);
			static bool op_Inequality(UnitBase* lhs, UnitBase* rhs);

		public private:  //internal to dll

			~UnitBase(void);
			UnitBase(UnitAny* u);
			UnitBase(UnitType type, int ClassID, int mode);
			UnitBase(UnitType type, String* name, int mode);
			UnitBase(UnitType type, UInt32 UniqueID);
			UnitBase(PresetUnit* p);

			virtual UnitBase* CreateNew(UnitAny* u);
			virtual UnitBase* CreateNew();


			static  UnitBase* Find(int type, int id, String* name, int mode)[];
			UnitAny* unit;
			UInt32 id;
			DWORD type;

		protected:
            virtual void Dispose(bool disposing);

			//events system
			void processpackets(Object* sender, botNET::Messaging::PacketEventArgs* e);
			void virtual v_processpackets(botNET::Messaging::PacketEventArgs* e);
			int mPackReceiveSubscriptionCount;

			//ctor helpers
			void setunit(UnitAny* u);
			void setunitnull();

			void ePacketAdd();
			void ePacketRemove();

		private:
			bool disposed;
		};

	}

}



#endif