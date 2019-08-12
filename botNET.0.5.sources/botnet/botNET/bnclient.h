#ifndef BNCLIENT_H
#define BNCLIENT_H



namespace botNET
{
	namespace Imports
	{
		__nogc class BNCLIENT
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			static DWORD** bnClient;

			static void ReceiveBNPacket(BYTE * Packet, DWORD Length);
			static void* fptrReceiveBNPacket; //0x2010

			static void ChatSrvSay(char *pszMessage);
			static void* fptrChatSrvSay; //0x77C0

			static DWORD asmCallReceiveBNPacket;
			static DWORD asmCallFOGSend;

			static DWORD oldCallReceiveBNPacket;
			static DWORD oldCallFOGSend;

		};


	}


}

#endif