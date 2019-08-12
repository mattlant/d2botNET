#ifndef READLINEOBJECT_H
#define READLINEOBJECT_H

#include "botnet.h"

namespace botNET
{
	private __gc class ReadLineObject
	{
	public:
		String * Message;
		bool PassTheMessage;

		ReadLineObject::ReadLineObject(bool PassMessage)
		{
			PassTheMessage = PassMessage;
			Message = S"";
		}
		void ReadLineObject::EventHandle(Object* sender, ChatLineMessageEventArgs* e)
		{
			Message = e->Message;
			e->PassMessage = PassTheMessage;
		}
	};


}

#endif