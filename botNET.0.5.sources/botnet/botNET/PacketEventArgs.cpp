#include "botnet.h"
#include ".\packeteventargs.h"
#include ".\packet.h"



namespace botNET
{
	namespace Messaging
	{


		///////////////////////////////////////////////////////////
		//PacketReceiveEventArgs
		///////////////////////////////////////////////////////////
		PacketEventArgs::PacketEventArgs(botNET::Messaging::Packet* packet, botNET::Messaging::PacketOrigin origin)
		{
			this->_packet = packet;
			this->_passpacket = true;
			this->_packetorigin = origin;
		}

		bool PacketEventArgs::get_PassPacket()
		{
			return this->_passpacket;
		}

		void PacketEventArgs::set_PassPacket(bool value)
		{
			this->_passpacket = value;
		}

		botNET::Messaging::PacketOrigin PacketEventArgs::get_PacketOrigin()
		{
			return this->_packetorigin;
		}

		botNET::Messaging::Packet* PacketEventArgs::get_Packet()
		{
			return _packet;
		}

	}

}
