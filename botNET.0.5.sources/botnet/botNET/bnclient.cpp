#include "botnet.h"
#include "bnclient.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void BNCLIENT::Initialize()
		{

			BaseAddress = Importer::BNClient->BaseAddress.ToInt32();

			BNCLIENT::bnClient = reinterpret_cast<DWORD**> (BaseAddress + 0x1D83C);			//1.11b

			BNCLIENT::fptrReceiveBNPacket = reinterpret_cast<void*> (BaseAddress + 0xB4D0);	//1.11b
			BNCLIENT::fptrChatSrvSay = reinterpret_cast<void*> (BaseAddress + 0x14070);		//1.11b

			BNCLIENT::asmCallReceiveBNPacket = BaseAddress + 0xB7CE;						//1.11b
			BNCLIENT::asmCallFOGSend = (BaseAddress + 0x143AD);								//1.11b


		}

		void BNCLIENT::ReceiveBNPacket(BYTE * Packet, DWORD aLength)
		{
			__asm
			{
				//mov edx, aLength
				//mov ecx, Packet
				//mov eax, BNCLIENT::fptrReceiveBNPacket		;0x2010
				//call eax
				mov eax, Packet
				push aLength
				call BNCLIENT::fptrReceiveBNPacket
			}
		}

		void BNCLIENT::ChatSrvSay(char *pszMessage)
		{
			__asm
			{
				mov ecx, pszMessage
				mov eax, BNCLIENT::fptrChatSrvSay		;0x77C0
				call eax
			}
		}


	}

}
