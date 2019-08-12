#ifndef PACKETPARSING_H
#define PACKETPARSING_H


bool __stdcall cbBNPacketReceive(BYTE* aPacket, DWORD aLength, bool before);
bool __stdcall cbBNPacketSend(BYTE* aPacket, DWORD aLength, bool before);
bool __stdcall cbRealmPacketReceive(BYTE* aPacket, bool before);
bool __stdcall cbRealmPacketSend(BYTE* aPacket, DWORD aLength, bool before);
bool __stdcall cbGamePacketReceive(BYTE* aPacket, DWORD aLength, bool before);
bool __stdcall cbGamePacketSend(BYTE* aPacket, DWORD aLength, bool before);


#endif