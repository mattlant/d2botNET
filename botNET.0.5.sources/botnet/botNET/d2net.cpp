#include "botnet.h"
#include "d2net.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2NET::Initialize()
		{
			BaseAddress = Importer::D2Net->BaseAddress.ToInt32();

			D2NET::fptrRecv = reinterpret_cast<void*> (BaseAddress + 0x15D5);


		}

		void D2NET::Recv(void)
		{
			__asm
			{
				mov eax, D2NET::fptrRecv		;0x15D5
				call eax
			}
		}


	}

}
