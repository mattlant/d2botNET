#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "messagebase.h"
#include "messagingenums.h"

namespace botNET
{
	namespace Messaging
	{

		__gc public class Packet;
		__gc public class ChatMessage : public MessageBase
		{
		public:

			__property String* get_Name();
			__property ChatType get_Type();
			__property Byte get_Color();
			__property UInt32 get_SenderUniqueID();
			__property Byte get_Style();
			__property ChatOrigin get_Origin();

			__event static void add_OnMessage(OnMessageHandler* h);
			__event static void remove_OnMessage(OnMessageHandler* h);



		public private:
			ChatMessage(Packet* packet, ChatOrigin type);
			ChatMessage(String* msg);
			static bool ParsePacket(Packet* packet);

			String* _name;
			ChatType _type;
			Byte _color;
			UInt32 _senderid;
			Byte _style;
			ChatOrigin _origin;

			__event static void raise_OnMessage(Object* sender, MessageEventArgs* e);
			static OnMessageHandler * InternalOnMessage;

		};

	}

}

#endif