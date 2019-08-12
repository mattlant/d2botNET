#include "botnet.h"
#include "unitevents.h"
#include "packet.h"



namespace botNET
{
	namespace Units
	{

		UnitEventArgs::UnitEventArgs(Packet* packet)
		{
			this->mPacket = packet;
		}

		Packet* UnitEventArgs::get_OriginatingPacket()
		{
			return this->mPacket;
		}

		UnitInfo UnitEventArgs::get_OriginatingUnitInfo()
		{
			return this->mOriginatingUnitInfo;
		}


		UnitPositionEventArgs::UnitPositionEventArgs(Packet* packet) : UnitEventArgs(packet)
		{
		}

		Point UnitPositionEventArgs::get_Position()
		{
			return this->mPosition;
		}


		SetTargetUnitEventArgs::SetTargetUnitEventArgs(Packet* packet) : UnitPositionEventArgs(packet)
		{
			this->mOriginatingUnitInfo = UnitInfo(UnitType::NPC, packet->GetUInt32(1));
			this->mTargetInfo = UnitInfo((UnitType)packet->GetByte(10), packet->GetUInt32(11));
			this->mPosition = Point(packet->GetUInt16(6), packet->GetUInt16(8));
		}

		UnitInfo SetTargetUnitEventArgs::get_TargetInfo()
		{
			return this->mTargetInfo;
		}



		void UnitEvents::Process(Packet* packet)
		{
			if(dOnSetTarget && packet->_packet[0] == 0x68)
			{
				//someone has subscribed, so lets process this event
				raise_OnSetTarget(0, new SetTargetUnitEventArgs(packet));
			}
		}


	}

}


