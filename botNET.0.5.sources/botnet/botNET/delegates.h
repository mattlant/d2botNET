#ifndef DELEGATES_H
#define DELEGATES_H

#include "eventargs.h"
#include "messageeventargs.h"
#include "packeteventargs.h"

namespace botNET
{
    private __delegate void OnDrawSHHandler();

	
	public __delegate void OnItemActionHandler( System::Object* sender, ItemActionEventArgs* e );
    public __delegate void OnDrawHandler(System::Object* sender, EventArgs* e);
    public __delegate void OnBeginGameHandler(System::Object* sender, GameEventArgs* e);
    public __delegate void OnEndGameHandler(System::Object* sender, GameEventArgs* e);
    public __delegate void OnChatLineHandler(System::Object* sender, ChatLineMessageEventArgs* e);
    public __delegate void OnKeyPressHandler(System::Object* sender, KeyPressEventArgs* e);
    public __delegate void OnMouseActionHandler(System::Object* sender, MouseActionEventArgs* e);
    public __delegate void OnPacketHandler(System::Object* sender, botNET::Messaging::PacketEventArgs* e);
	public __delegate void OnMessageHandler(System::Object* sender, botNET::Messaging::MessageEventArgs* e);
	public __delegate void OnTextChangedHandler( System::Object* sender, TextChangedEventArgs* e );

	namespace Units
	{
		public __gc class SetTargetUnitEventArgs;
		public __delegate void OnUnitSetTargetHandler( System::Object* sender, SetTargetUnitEventArgs* e );
	}

}

#endif