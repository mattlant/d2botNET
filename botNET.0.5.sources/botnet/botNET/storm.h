#ifndef STORM_H
#define STORM_H



namespace botNET
{
	namespace Imports
	{
		__nogc class STORM
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			//TODO: chanmge away from dllimport and to asm code for performance
			[DllImport("storm", EntryPoint="#412", CallingConvention=CallingConvention::StdCall)]
			static bool GlobalMessageHandler(HWND hwnd, int Message, WPARAM wParam, LPARAM lParam, bool * NotDef, int * retVal);

			[DllImport("storm", EntryPoint="#403", CallingConvention=CallingConvention::StdCall)]
			static void FreeMemory(DWORD _1, char * ident, DWORD _2, DWORD _3);


		};


	}


}

#endif