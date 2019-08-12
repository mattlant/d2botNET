#include "botnet.h"
#include "fog.h"


namespace botNET
{
	namespace Imports
	{
		UInt32 FOG::BaseAddress = 0;


		void* FOG::fptrReceiveRealmPacket = 0; //0x1430
		void* FOG::fptrErrorReasonWriter = 0; //0xEEA0
		void* FOG::fptrMemAlloc = 0; //-0x273D
		void* FOG::fptrMemDeAlloc = 0; //-0x273E
		void* FOG::fptrSend = 0; //-0x2717
		void* FOG::fptrGetComputerInfo = 0; //-0x27F2

		DWORD FOG::asmCallErrorReasonWriter = 0; //0xF162
		DWORD FOG::asmCallExceptionHandlerGetComputerInfo = 0; //0xE712
		DWORD FOG::asmCallErrorHandlerGetComputerInfo = 0; //0xEEE9
		DWORD FOG::asmCallReceiveRealmPacket = 0; //0x16D1
		DWORD FOG::asmCallFOGSend = 0; //0x135A

		DWORD FOG::oldCallErrorReasonWriter = 0; //0xF162
		DWORD FOG::oldCallExceptionHandlerGetComputerInfo = 0; //0xE712
		DWORD FOG::oldCallErrorHandlerGetComputerInfo = 0; //0xEEE9
		DWORD FOG::oldCallReceiveRealmPacket = 0; //0x16D1
		DWORD FOG::oldCallFOGSend = 0; //0x135A
 	}

}