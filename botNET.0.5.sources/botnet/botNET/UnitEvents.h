#ifndef UNITEVENTS_H
#define UNITEVENTS_H

using namespace botNET::Messaging;
using namespace System::Drawing;

#include "UnitInfo.h"


namespace botNET
{
	namespace Messaging
	{
		__gc public class Packet;
	}

	namespace Units
	{
		__gc public class PlayerNPCBase;

		__gc public class UnitEventArgs : public EventArgs
		{
			public:
				UnitEventArgs(Packet* packet);

				__property Packet*			get_OriginatingPacket(void);
				__property UnitInfo			get_OriginatingUnitInfo(void);

			protected:
				Packet*			mPacket;
				UnitInfo		mOriginatingUnitInfo;
		};

		__gc public class UnitPositionEventArgs : public UnitEventArgs
		{
			public:
				UnitPositionEventArgs(Packet* packet);

				__property Point get_Position();

			protected:
				Point mPosition;
		};

		__gc public class SetTargetUnitEventArgs : public UnitPositionEventArgs
		{
			public:
				SetTargetUnitEventArgs(Packet* packet);

				__property UnitInfo get_TargetInfo();

			protected:
				UnitInfo mTargetInfo;
		};




		__gc public class UnitEvents
		{
		public:
			__event static void add_OnSetTarget(OnUnitSetTargetHandler* h) { dOnSetTarget += h; }
			__event static void remove_OnSetTarget(OnUnitSetTargetHandler* h)  { dOnSetTarget -= h; }
			__event static void raise_OnSetTarget(Object* sender, SetTargetUnitEventArgs* e) { if(dOnSetTarget) dOnSetTarget(0, e); }

		public private:
			static void Process(Packet* packet);
			static OnUnitSetTargetHandler * dOnSetTarget;


		};

	}

}


#endif
