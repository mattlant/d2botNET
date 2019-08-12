#include "botnet.h"
#include "packetparsing.h"

#include "chatmessage.h"
#include "systemmessage.h"
#include "partymessage.h"
#include "packet.h"
#include "messagingenums.h"
#include "Game.h"
#include "pc.h"

using namespace botNET::Messaging;
using namespace botNET;

bool __stdcall cbBNPacketReceive(BYTE* aPacket, DWORD aLength, bool before)
{

	bool passpacket = true;

	try
	{
		//Create Packet
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);

		if(before)
		{
			if(!ChatMessage::ParsePacket(p))
				passpacket = false;

			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeBattleNetReceive);
			botNET::Messaging::Packet::raise_OnBeforeBattleNetReceive(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterBattleNetReceive);
			botNET::Messaging::Packet::raise_OnAfterBattleNetReceive(NULL, e);
		}

	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}

bool __stdcall cbBNPacketSend(BYTE* aPacket, DWORD aLength, bool before)
{
	bool passpacket = true;

	try
	{
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);
		if(before)
		{

			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeBattleNetSend);
			botNET::Messaging::Packet::raise_OnBeforeBattleNetSend(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterBattleNetSend);
			botNET::Messaging::Packet::raise_OnAfterBattleNetSend(NULL, e);
		}
	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}

bool __stdcall cbRealmPacketReceive(BYTE* aPacket, bool before)
{

	bool passpacket = true;

	WORD aLength = *(WORD*)aPacket;

	try
	{
		//Create Packet
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);

		if(before)
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeRealmReceive);
			botNET::Messaging::Packet::raise_OnBeforeRealmReceive(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterRealmReceive);
			botNET::Messaging::Packet::raise_OnAfterRealmReceive(NULL, e);
		}

	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}

bool __stdcall cbRealmPacketSend(BYTE* aPacket, DWORD aLength, bool before)
{
	bool passpacket = true;

	try
	{
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);
		if(before)
		{

			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeRealmSend);
			botNET::Messaging::Packet::raise_OnBeforeRealmSend(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterRealmSend);
			botNET::Messaging::Packet::raise_OnAfterRealmSend(NULL, e);
		}
	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}

bool __stdcall cbGamePacketReceive(BYTE* aPacket, DWORD aLength, bool before)
{
	bool passpacket = true;

	try
	{
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);

        if(before)
		{
			if(!ChatMessage::ParsePacket(p))
				passpacket = false;

			if(p->GetByte(0) == 0x63)
				botNET::Units::PC::waypoints = p->GetUInt64(7);

			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeGameReceive);
			botNET::Messaging::Packet::raise_OnBeforeGameReceive(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			SystemMessage::ParsePacket(p);
			PartyMessage::ParsePacket(p);
			
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterGameReceive);
			botNET::Messaging::Packet::raise_OnAfterGameReceive(NULL, e);
		}

	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}

bool __stdcall cbGamePacketSend(BYTE* aPacket, DWORD aLength, bool before)
{
	bool passpacket = true;

	try
	{
		botNET::Messaging::Packet* p = new botNET::Messaging::Packet(aPacket, aLength);
		if(before)
		{

			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::BeforeGameSend);
			botNET::Messaging::Packet::raise_OnBeforeGameSend(NULL, e);
			if(!e->_passpacket)
				passpacket = false;
		}
		else
		{
			PacketEventArgs * e = new PacketEventArgs(p, PacketOrigin::AfterGameReceive);
			botNET::Messaging::Packet::raise_OnAfterGameSend(NULL, e);
		}
	}
	catch(Exception* ex)
	{
		Game::Print(ex);
	}

	return passpacket;
}


/*
       switch( Packet[0] )
        {
			case 0x95:
				//Me::RaiseOnHealthManaChangeEvent();
				// TODO: Setup the events **DONE**
				break;
			case 0x63:
				//make sure rest are 0 so it doesnt skew are created UInt64
				parts[12] = 0;
				parts[13] = 0;
				parts[14] = 0;
				PC::me->waypoints = BitConverter::ToUInt64(parts, 7);
				break;
            case 0x9C:
            case 0x9D:
                ItemActionEventArgs* hArgs = new ItemActionEventArgs( Packet );
                switch( hArgs->ActionType )
                {
                    case ItemActionType::AddToContainer:
                        switch( hArgs->Location )
                        {
                            case ItemLocation::Cube:
                                //Me::Cube::OnAddItem( hArgs );
								// TODO: Setup containers and events
                                break;
                            case ItemLocation::Inventory:
                                //Me::Inventory::OnAddItem( hArgs );
                                break;
                            case ItemLocation::Stash:
                                //Me::Stash::OnAddItem( hArgs );
                                break;
                        }
                        break;

                    case ItemActionType::RemoveFromContainer:
                        switch( hArgs->Location )
                        {
                            case ItemLocation::Cube:
                                //Me::Cube::OnRemoveItem( hArgs );
                                break;
                            case ItemLocation::Inventory:
                                //Me::Inventory::OnRemoveItem( hArgs );
                                break;
                            case ItemLocation::Stash:
                                //Me::Stash::OnRemoveItem( hArgs );
                                break;
                        }
                        break;
				}
        }
*/