#ifndef PACKETPATCH_H
#define PACKETPATCH_H

namespace botNET
{
namespace Imports
{
namespace Patches
{

void GamePacketReceiveSTUB(BYTE* aPacket, DWORD aLength);
void __stdcall GamePacketReceiveHANDLER(BYTE* aPacket, DWORD aLength);
void __stdcall GamePacketSendSTUB(DWORD type, BYTE* packet, DWORD length);

void BNPacketReceiveSTUB(BYTE* aPacket, DWORD aLength);
void __stdcall BNPacketReceiveHANDLER(BYTE* aPacket, DWORD aLength);

void RealmPacketReceiveSTUB(BYTE* unk, BYTE* aPacket, DWORD aLength);
void __stdcall RealmPacketReceiveHANDLER(BYTE* unk, BYTE* aPacket, DWORD aLength);

void BN_RealmPacketSendSTUB(DWORD* unk, BYTE* aPacket, DWORD aLength);
void __stdcall BN_RealmPacketSendHANDLER(DWORD* unk, BYTE* aPacket, DWORD aLength);


}
}
}

#endif