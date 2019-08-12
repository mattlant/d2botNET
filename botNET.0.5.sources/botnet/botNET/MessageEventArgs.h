#ifndef MESSAGEEVENTARGS_H
#define MESSAGEEVENTARGS_H

#include "messagingenums.h"

namespace botNET
{
	namespace Messaging
	{

		__gc public class MessageBase;
		__gc public class MessageEventArgs : public EventArgs
		{
			public:
				MessageEventArgs(MessageBase * msg);

				__property MessageBase * get_Message(void);
				__property bool get_PassMessage(void);
				__property void set_PassMessage(bool value);
				__property MessageType get_Type();

			private:
				MessageBase * _message;
				bool _passmessage;
				MessageType _messagetype;
		};

	}

}

#endif