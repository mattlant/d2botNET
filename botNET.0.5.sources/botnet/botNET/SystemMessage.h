#ifndef SYSTEMMESSAGE_H
#define SYSTEMMESSAGE_H

#include "messagebase.h"
#include "messagingenums.h"

namespace botNET
{
	namespace Messaging
	{

		__gc public class Packet;
		__gc public class SystemMessage : public MessageBase
		{
		public:

			__property String* get_Name();
			__property SystemMessageType get_Type();
			__property Byte get_SubType();
			__property Byte get_Color();
			__property UInt32 get_SenderUniqueID();


			__event static void add_OnMessage(OnMessageHandler* h);
			__event static void remove_OnMessage(OnMessageHandler* h);

		public private:
			__event static void raise_OnMessage(Object* sender, MessageEventArgs* e);

			static OnMessageHandler * InternalOnMessage;

			SystemMessage(Packet* packet);
			static bool ParsePacket(Packet* packet);

			String* _name;
			SystemMessageType _type;
			Byte _subtype;
			Byte _color;
			UInt32 _senderid;


		};

	}

}

#endif