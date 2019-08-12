#ifndef PARTYMESSAGE_H
#define PARTYMESSAGE_H

#include "messagebase.h"
#include "messagingenums.h"

namespace botNET
{
	namespace Units
	{
		__gc public class RosterPlayer;
	}
	namespace Messaging
	{

		__gc public class Packet;
		__gc public class PartyMessage : public MessageBase
		{
		public:

			__property PartyMessageType get_Type();
			__property UInt32 get_SenderUniqueID();
			__property botNET::Units::RosterPlayer* get_Player();

			__event static void add_OnMessage(OnMessageHandler* h);
			__event static void remove_OnMessage(OnMessageHandler* h);


		public private:
			__event static void raise_OnMessage(Object* sender, MessageEventArgs* e);

			static OnMessageHandler * InternalOnMessage;

			PartyMessage(Packet* packet);
			static bool ParsePacket(Packet* packet);

			PartyMessageType _type;
			UInt32 _senderid;
			botNET::Units::RosterPlayer* _player;


		};

	}

}

#endif