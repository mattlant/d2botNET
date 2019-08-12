#include "botnet.h"
#include ".\partymessage.h"
#include ".\packet.h"

#include "game.h"
#include "rosterplayer.h"

namespace botNET
{
	namespace Messaging
	{

		PartyMessage::PartyMessage(Packet* packet) : MessageBase(S"Party Message", packet)
		{
			this->_senderid = packet->GetUInt32(3);

			this->_player = botNET::Units::RosterPlayer::Get(this->_senderid);


			this->_type = (PartyMessageType)packet->GetByte(7);
			this->_messagetype = MessageType::PartyMessage;
		}

		UInt32 PartyMessage::get_SenderUniqueID() { return this->_senderid; }
		PartyMessageType PartyMessage::get_Type() { return this->_type; }
		botNET::Units::RosterPlayer* PartyMessage::get_Player() { return this->_player; }

		bool PartyMessage::ParsePacket(Packet* packet)
		{
			if(packet->_packet[0] == 0x5A && packet->_packet[1] == 0x7)
			{
				MessageEventArgs * e = new MessageEventArgs(new PartyMessage(packet));
				raise_OnMessage(NULL, e);
			}

			return true;
		}

		void PartyMessage::add_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage += h;
		}

		void PartyMessage::remove_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage -= h;
		}

		void PartyMessage::raise_OnMessage(Object* sender, MessageEventArgs* e)
		{
			if(InternalOnMessage)
				InternalOnMessage(NULL, e);
		}


	}

}
