#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H


namespace botNET
{
	namespace Messaging
	{

		__gc public class Packet;
		__gc public class MessageBase
		{
		public:
			__property String * get_Text();
			Packet* GetPacket();
			MessageType GetMessageType();
		public private:
			MessageBase(String* text, Packet* packet);

			String* _text;
			Packet* _packet;
			MessageType _messagetype;

		};

	}

}


#endif