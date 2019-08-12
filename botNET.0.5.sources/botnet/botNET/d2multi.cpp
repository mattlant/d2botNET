#include "botnet.h"
#include "d2multi.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2MULTI::Initialize()
		{
			BaseAddress = Importer::D2Multi->BaseAddress.ToInt32();

			D2MULTI::ChatOutputTextBox = reinterpret_cast<ButtonAttrib **> (BaseAddress + 0x228A0);

			D2MULTI::fptrChatLineCommitHandler = reinterpret_cast<void*> (BaseAddress + 0xC068);
			D2MULTI::fptrChatLineSend = reinterpret_cast<void*> (BaseAddress + 0x6B20);

			D2MULTI::asmCallChatLineCommit = (BaseAddress + 0x1C57C);
			D2MULTI::asmCallChatLineSend = (BaseAddress + 0x62BC);

		}

		void D2MULTI::ChatLineCommitHandler(wchar_t * line)
		{
			__asm
			{
				push line
				mov eax, D2MULTI::fptrChatLineCommitHandler		;0xC068
				call eax
			}
		}

		void D2MULTI::ChatLineSend(char * line)
		{
			__asm
			{
				mov ecx, line
				mov eax, D2MULTI::fptrChatLineSend		;0x6B20
				call eax
			}
		}

	}

}
