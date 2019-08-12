#include "botnet.h"
#include "d2multi.h"


namespace botNET
{
	namespace Imports
	{
		UInt32 D2MULTI::BaseAddress = 0;

		ButtonAttrib ** D2MULTI::ChatOutputTextBox = 0; //0x228A0


		void* D2MULTI::fptrChatLineCommitHandler = 0; //0xC068
		void* D2MULTI::fptrChatLineSend = 0; //0x6B20

		DWORD D2MULTI::asmCallChatLineCommit = 0; //0x1C57C
		DWORD D2MULTI::asmCallChatLineSend = 0; //0x62BC

		DWORD D2MULTI::oldCallChatLineCommit = 0; //0x1C57C
		DWORD D2MULTI::oldCallChatLineSend = 0; //0x62BC
	}

}