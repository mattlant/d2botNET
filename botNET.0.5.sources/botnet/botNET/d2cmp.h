#ifndef D2CMP_H
#define D2CMP_H

#include "definitions.h"


namespace botNET
{
	namespace Imports
	{
		__nogc class D2CMP
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;


			[DllImport("d2cmp", EntryPoint="#10024", CallingConvention=CallingConvention::StdCall)]
			static void InitCellFile(void* cellfile, CellFile** outptr, char* srcfile, DWORD lineno, DWORD filever, char* filename);

			[DllImport("d2cmp", EntryPoint="#10032", CallingConvention=CallingConvention::StdCall)]
			static void DeleteCellFile(CellFile* cellfile);

			[DllImport("d2cmp", EntryPoint="#10014", CallingConvention=CallingConvention::StdCall)]
			static void UnloadUIImage(CellFile* cellfile);

			[DllImport("d2cmp", EntryPoint="#10097", CallingConvention=CallingConvention::StdCall)]
			static void SetAct(int Act);

		};


	}


}

#endif