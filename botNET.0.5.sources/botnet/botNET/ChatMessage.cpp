#include "botnet.h"
#include ".\chatmessage.h"
#include ".\packet.h"

#include "game.h"

namespace botNET
{
	namespace Messaging
	{

		ChatMessage::ChatMessage(Packet* packet, ChatOrigin type) : MessageBase(S"", packet)
		{
			this->_origin = type;
			this->_messagetype = MessageType::ChatMessage;
			if(type == ChatOrigin::Game)
			{
				//Chat in game
				this->_name = packet->GetString(10);  //testi snull becomes a space, or if still null, then do IndexOf
				this->_text = packet->GetString(10); // TODO: see above
				this->_type = (ChatType)packet->GetByte(1);
				this->_style = packet->GetByte(3);
				this->_senderid = packet->GetUInt32(4);
				this->_color = packet->GetByte(8);
			}
			else if(type == ChatOrigin::BattleNet)
			{
				//Battlenet chat from lobby and whispers, etc
				this->_name = packet->GetString(28);
				this->_text = packet->GetString(28);
				this->_type = (ChatType)packet->GetByte(4);

				this->_style = 0;
				this->_senderid = 0;
				this->_color = 0;
			}

			else if(type == ChatOrigin::BattleNet)
			{
				//Battlenet chat from lobby and whispers, etc
				this->_name = packet->GetString(28);
				this->_text = packet->GetString(28);
				this->_type = (ChatType)packet->GetByte(4);

				this->_style = 0;
				this->_senderid = 0;
				this->_color = 0;
			}
		}

		ChatMessage::ChatMessage(String* msg) : MessageBase(msg, NULL)
		{
			this->_origin = ChatOrigin::ChatLine;
			this->_name = "";
			this->_type = ChatType::Normal;
			this->_style = 0;
			this->_senderid = 0;
			this->_color = 0;
		}



		Byte ChatMessage::get_Color() { return this->_color; }
		String* ChatMessage::get_Name() { return this->_name; }
		UInt32 ChatMessage::get_SenderUniqueID() { return this->_senderid; }
		Byte ChatMessage::get_Style() { return this->_style; }
		ChatType ChatMessage::get_Type() { return this->_type; }
		ChatOrigin ChatMessage::get_Origin() { return this->_origin; }

		bool ChatMessage::ParsePacket(Packet* packet)
		{
			bool passpacket = true;

			//Process for Messages
			if(packet->_packet[0] == 0x26)
			{
				//System::Windows::Forms::MessageBox::Show(S"Hit A Message");
				ChatMessage* msg = new ChatMessage(packet, ChatOrigin::Game);
				MessageEventArgs * e = new MessageEventArgs(msg);
				//Raise it
				raise_OnMessage(NULL, e);
				return e->PassMessage;
			}
			else if(packet->_packet[0] == 0xFF && packet->_packet[1] == 0x0F)
			{
				//parse message packets
				ChatMessage* msg = new ChatMessage(packet, ChatOrigin::BattleNet);
				MessageEventArgs * e = new MessageEventArgs(msg);
				//Raise it
				raise_OnMessage(NULL, e);
				return e->PassMessage;
			}

			return passpacket;
		}

		void ChatMessage::add_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage += h;
		}

		void ChatMessage::remove_OnMessage(OnMessageHandler* h)
		{
			InternalOnMessage -= h;
		}

		void ChatMessage::raise_OnMessage(Object* sender, MessageEventArgs* e)
		{
			if(InternalOnMessage)
				InternalOnMessage(NULL, e);
		}


	}

}
