#ifndef D2LAUNCH_H
#define D2LAUNCH_H

#include "definitions.h"

namespace botNET
{
	namespace Imports
	{
		__nogc class D2LAUNCH
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			static BnetData** BNData;
			static ButtonAttrib ** ButtonList;



			static void UIEnterBnet(void);
			static void* fptrUIEnterBnet; //0x9910

			static void UIEnterMainMenu(void);
			static void* fptrUIEnterMainMenu; //0x9320

			static void UIExitD2(void);
			static void* fptrUIExitD2; //0x12900

			static int EnterBnet(void * arg);
			static void* fptrEnterBnet; //0x11FD0

			static DWORD asmCallEnterBnet1;
			static DWORD asmCallEnterBnet2;

		};

	}

}

#endif