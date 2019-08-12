#include "botnet.h"
#include ".\messagebase.h"


namespace botNET
{
	namespace Messaging
	{

		MessageBase::MessageBase(String* text, Packet* packet) : _text(text), _packet(packet)
		{
		}

		String* MessageBase::get_Text()
		{
			return String::Copy(_text);
		}

		Packet* MessageBase::GetPacket()
		{
			return _packet;
		}

		MessageType MessageBase::GetMessageType()
		{
			return this->_messagetype;
		}
	}

}