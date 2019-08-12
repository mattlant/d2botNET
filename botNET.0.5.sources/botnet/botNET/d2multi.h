#ifndef D2MULTI_H
#define D2MULTI_H

#include "definitions.h"

namespace botNET
{
	namespace Imports
	{
		__nogc class D2MULTI
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			static ButtonAttrib ** ChatOutputTextBox;


			static void ChatLineCommitHandler(wchar_t * line);
			static void* fptrChatLineCommitHandler; //0xC068

			static void ChatLineSend(char * line);
			static void* fptrChatLineSend; //0x6B20



			static DWORD asmCallChatLineCommit;
			static DWORD asmCallChatLineSend;

			static DWORD oldCallChatLineCommit;
			static DWORD oldCallChatLineSend;

		};

	}

}

#endif