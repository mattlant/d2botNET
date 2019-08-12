#ifndef D2GDI_H
#define D2GDI_H

#include "definitions.h"


namespace botNET
{
	namespace Imports
	{
		__nogc class D2GDI
		{
		public:
			static UInt32 BaseAddress;
			static void Initialize();

			static void DrawImage(CellContext *context, DWORD xpos, DWORD ypos, DWORD bright2, DWORD bright, BYTE *coltab);
			static void* fptrDrawImage; //0x2620


		};

	}

}

#endif