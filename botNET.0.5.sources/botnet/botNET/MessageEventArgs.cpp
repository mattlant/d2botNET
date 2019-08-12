#include "botnet.h"
#include ".\messageeventargs.h"
#include ".\messagebase.h"

namespace botNET
{
	namespace Messaging
	{

		MessageEventArgs::MessageEventArgs(MessageBase* msg)
		{
			_message = msg;
			_passmessage = true;
			this->_messagetype = msg->_messagetype;
		}

		MessageBase* MessageEventArgs::get_Message()
		{
			return _message;
		}

		bool MessageEventArgs::get_PassMessage()
		{
			return this->_passmessage;
		}

		void MessageEventArgs::set_PassMessage(bool value)
		{
			this->_passmessage = value;
		}

		MessageType MessageEventArgs::get_Type()
		{
			return this->_messagetype;
		}

	}



}

