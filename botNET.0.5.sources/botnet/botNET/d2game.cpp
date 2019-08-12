#include "botnet.h"
#include "d2game.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2GAME::Initialize()
		{
			BaseAddress = Importer::D2Game->BaseAddress.ToInt32();

			D2GAME::fptrIsSwitched = reinterpret_cast<void*> (BaseAddress + 0x45B0);

		}

		BYTE D2GAME::IsSwitched(PlrMsg* ptPlrMsg)
		{
			BYTE retval;
			__asm
			{
				mov ecx, ptPlrMsg
				mov eax, D2GAME::fptrIsSwitched		;0x45B0
				call eax
				mov retval, al
			}
			return retval;
		}


	}

}
