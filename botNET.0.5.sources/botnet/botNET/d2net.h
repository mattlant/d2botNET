#ifndef D2NET_H
#define D2NET_H

#include "definitions.h"


namespace botNET
{
	namespace Imports
	{
		__nogc class D2NET
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			[DllImport("d2net", EntryPoint="#10005", CallingConvention=CallingConvention::StdCall)]
			static void GameSend(DWORD dwFlags, LPBYTE lpBuf, DWORD len);

			static void Recv(void);
			static void* fptrRecv; //0x15D5


		};


	}


}

#endif