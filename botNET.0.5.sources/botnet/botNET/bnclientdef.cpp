#include "botnet.h"
#include "bnclient.h"


namespace botNET
{
	namespace Imports
	{
		UInt32 BNCLIENT::BaseAddress = 0;

		DWORD** BNCLIENT::bnClient = 0; //0x1D158

		void* BNCLIENT::fptrReceiveBNPacket = 0; //0x2010
		void* BNCLIENT::fptrChatSrvSay = 0; //0x77C0

		DWORD BNCLIENT::asmCallReceiveBNPacket = 0; //0x215A
		DWORD BNCLIENT::asmCallFOGSend = 0; //0x1FE6

		DWORD BNCLIENT::oldCallReceiveBNPacket = 0; //0x215A
		DWORD BNCLIENT::oldCallFOGSend = 0; //0x1FE6

	}

}