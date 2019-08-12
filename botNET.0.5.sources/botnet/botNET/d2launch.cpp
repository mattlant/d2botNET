#include "botnet.h"
#include "d2launch.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2LAUNCH::Initialize()
		{
			BaseAddress = Importer::D2Launch->BaseAddress.ToInt32();

			D2LAUNCH::BNData = reinterpret_cast<BnetData**> (BaseAddress + 0x2CD44);
			D2LAUNCH::ButtonList = reinterpret_cast<ButtonAttrib **> (BaseAddress + 0x2CAD8);


			D2LAUNCH::fptrUIEnterBnet = reinterpret_cast<void*> (BaseAddress + 0x9910);
			D2LAUNCH::fptrUIEnterMainMenu = reinterpret_cast<void*> (BaseAddress + 0x9320);
			D2LAUNCH::fptrUIExitD2 = reinterpret_cast<void*> (BaseAddress + 0x12900);
			D2LAUNCH::fptrEnterBnet = reinterpret_cast<void*> (BaseAddress + 0x11FD0);

			D2LAUNCH::asmCallEnterBnet1 = (BaseAddress + 0x238A0);
			D2LAUNCH::asmCallEnterBnet2 = (BaseAddress + 0x219F0);
		}

		void D2LAUNCH::UIEnterBnet(void)
		{
			__asm
			{
				mov eax, D2LAUNCH::fptrUIEnterBnet		;0x9910
				call eax
			}
		}

		void D2LAUNCH::UIEnterMainMenu(void)
		{
			__asm
			{
				mov eax, D2LAUNCH::fptrUIEnterMainMenu		;0x9320
				call eax
			}
		}

		void D2LAUNCH::UIExitD2(void)
		{
			__asm
			{
				mov eax, D2LAUNCH::fptrUIExitD2		;0x12900
				call eax
			}
		}

		int D2LAUNCH::EnterBnet(void * arg)
		{
			int retval;
			__asm
			{
				push arg
				mov eax, D2LAUNCH::fptrEnterBnet		;0x11FD0
				call eax
				mov eax, retval
			}
			return retval;
		}

	}

}
