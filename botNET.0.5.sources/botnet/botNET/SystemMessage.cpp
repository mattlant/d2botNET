#include "botnet.h"
#include ".\systemmessage.h"
#include ".\packet.h"

#include "game.h"

namespace botNET
{
	namespace Messaging
	{

		SystemMessage::SystemMessage(Packet* packet) : MessageBase(S"", packet)
		{
			this->_senderid = packet->GetUInt32(3);
			this->_type = (SystemMessageType)packet->GetByte(1);
			this->_color = packet->GetByte(2);
			this->_subtype = packet->GetByte(6);
			this->_name = packet->GetString(8);
			this->_text = String::Concat(((int)this->_type).ToString(), S":", ((int)this->_subtype).ToString());
			this->_messagetype = MessageType::SystemMessage;
		}

		Byte SystemMessage::get_Color() { return this->_color; }
		String* SystemMessage::get_Name() { return this->_name; }
		UInt32 SystemMessage::get_SenderUniqueID() { return this->_senderid; }
		Byte SystemMessage::get_SubType() { return this->_subtype; }
		SystemMessageType SystemMessage::get_Type() { return this->_type; }

		bool SystemMessage::ParsePacket(Packet* packet)
		{
 			//Process for System Messages
			if(packet->_packet[0] == 0x5A)
			{
				MessageEventArgs * e = new MessageEventArgs(new botNET::Messaging::SystemMessage(packet));
				raise_OnMessage(NULL, e);
			}
			return true;
		}

		void SystemMessage::add_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage += h;
		}

		void SystemMessage::remove_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage -= h;
		}

		void SystemMessage::raise_OnMessage(Object* sender, MessageEventArgs* e)
		{
			if(InternalOnMessage)
				InternalOnMessage(NULL, e);
		}


	}

}
