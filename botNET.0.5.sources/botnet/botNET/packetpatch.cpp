#include "botnet.h"
#include ".\packetpatch.h"
#include "packetparsing.h"
#include ".\game.h"
#include ".\fog.h"
#include ".\bnclient.h"
#include ".\d2client.h"
#include ".\d2net.h"


namespace botNET
{
namespace Imports
{
namespace Patches
{

void __declspec(naked) GamePacketReceiveSTUB(BYTE* aPacket, DWORD aLength)
{

	__asm
	{
		push edx
		push ecx
		call GamePacketReceiveHANDLER
		ret
	}

}

void __stdcall GamePacketReceiveHANDLER(BYTE* aPacket, DWORD aLength)
{
	DWORD retVal = 0;
	
	//Check if the packet is to be returned, if not then pass a dummy
	if(aLength != 0xFFFFFFFF)
		if(cbGamePacketReceive(aPacket, aLength, true))
			retVal = aLength;

	D2CLIENT::GameReceivePacketHandlerNew(aPacket, retVal);


	if(aLength != 0xFFFFFFFF && retVal)
		cbGamePacketReceive(aPacket, aLength, false);

}

void __stdcall GamePacketSendSTUB(DWORD type, BYTE* packet, DWORD length)
{
	cbGamePacketSend(packet, length, true);
	D2NET::GameSend(type, packet, length);
	cbGamePacketSend(packet, length, false);

}

void __declspec(naked) BNPacketReceiveSTUB(BYTE* aPacket, DWORD aLength)
{

	__asm
	{
		push edx
		push ecx
		call BNPacketReceiveHANDLER
		ret
	}

}

void __stdcall BNPacketReceiveHANDLER(BYTE* aPacket, DWORD aLength)
{
	//Check if the packet is to be returned, if not then pass a dummy
	if(cbBNPacketReceive(aPacket, aLength, true))
	{
		BNCLIENT::ReceiveBNPacket(aPacket, aLength);
		//cbBNPacketReceive(aPacket, length, false);
	}
	else
	{
		BNCLIENT::ReceiveBNPacket(aPacket, 0);
	}

}

void __declspec(naked) RealmPacketReceiveSTUB(BYTE* unk, BYTE* aPacket, DWORD aLength)
{

	__asm
	{
		mov eax, dword ptr ss:[esp+4]
		push eax
		push edx
		push ecx
		call RealmPacketReceiveHANDLER
		ret 4
	}

}

void __stdcall RealmPacketReceiveHANDLER(BYTE* unk, BYTE* aPacket, DWORD aLength)
{
	//Check if the packet is to be returned, if not then pass a dummy
	if(cbRealmPacketReceive(aPacket, true))
	{
		FOG::ReceiveRealmPacket(unk, aPacket, aLength);
		//cbRealmPacketReceive(aPacket, true);
	}
	else
	{
		//TODO: Block packet
		FOG::ReceiveRealmPacket(unk, aPacket, aLength);
	}
}

void __declspec(naked) BN_RealmPacketSendSTUB(DWORD* unk, BYTE* aPacket, DWORD aLength)
{
	__asm
	{
		mov eax, dword ptr ss:[esp+4]
		push eax
		push edx
		push ecx
		call BN_RealmPacketSendHANDLER
		ret 4
	}
}

void __stdcall BN_RealmPacketSendHANDLER(DWORD* unk, BYTE* aPacket, DWORD aLength)
{
	if(aPacket[0] == 0xFF) //BNPacket
	{
		cbBNPacketSend(aPacket, aLength, true);
		FOG::Send(unk, aPacket, aLength);
		//cbBNPacketSend(aPacket, aLength, false);
	}
	else
	{
		cbRealmPacketSend(aPacket, aLength, true);
		FOG::Send(unk, aPacket, aLength);
		//cbRealmPacketSend(aPacket, aLength, false);
	}
}

//TODO: Add send blocking at some point


}//Patches
}//Imports
}//botNET

