#include "botnet.h"
#include "d2gdi.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2GDI::Initialize()
		{
			BaseAddress = Importer::D2Gdi->BaseAddress.ToInt32();

			D2GDI::fptrDrawImage = reinterpret_cast<void*> (BaseAddress + 0x2620);
		}

		void D2GDI::DrawImage(CellContext* context, DWORD xpos, DWORD ypos, DWORD bright2, DWORD bright, BYTE* coltab)
		{
			__asm
			{
				push coltab
				push bright
				push bright2
				push ypos
				mov edx, xpos
				mov ecx, context
				mov eax, D2GDI::fptrDrawImage		;0x2620
				call eax
			}
		}


	}

}
