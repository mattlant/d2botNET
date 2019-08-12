#ifndef PACKETEVENTARGS_H
#define PACKETEVENTARGS_H

#include "messagingenums.h"

namespace botNET
{
	namespace Messaging
	{

		__gc public class Packet;

		__gc public class PacketEventArgs : public EventArgs
		{
			public:
				PacketEventArgs(botNET::Messaging::Packet* packet, botNET::Messaging::PacketOrigin origin);

				__property botNET::Messaging::Packet* get_Packet();
				__property bool get_PassPacket(void);
				__property void set_PassPacket(bool value);
				__property botNET::Messaging::PacketOrigin get_PacketOrigin(void);

			private public:
				botNET::Messaging::Packet* _packet;
				bool _passpacket;
				botNET::Messaging::PacketOrigin _packetorigin;
		};

	}

}

#endif
