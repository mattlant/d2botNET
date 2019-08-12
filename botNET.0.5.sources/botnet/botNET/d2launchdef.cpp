#include "botnet.h"
#include "d2launch.h"


namespace botNET
{
	namespace Imports
	{
		UInt32 D2LAUNCH::BaseAddress = 0;

		BnetData** D2LAUNCH::BNData = 0; //0x2CD44
		ButtonAttrib ** D2LAUNCH::ButtonList = 0; //0x2CAD8

		void* D2LAUNCH::fptrUIEnterBnet = 0; //0x9910
		void* D2LAUNCH::fptrUIEnterMainMenu = 0; //0x9320
		void* D2LAUNCH::fptrUIExitD2 = 0; //0x12900
		void* D2LAUNCH::fptrEnterBnet = 0; //0x11FD0

		DWORD D2LAUNCH::asmCallEnterBnet1 = 0; //0x238A0
		DWORD D2LAUNCH::asmCallEnterBnet2 = 0; //0x219F0

	}

}