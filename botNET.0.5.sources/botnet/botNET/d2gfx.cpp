#include "botnet.h"
#include "d2gfx.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2GFX::Initialize()
		{
			BaseAddress = Importer::D2Gfx->BaseAddress.ToInt32();


			D2GFX::asmCallIsIconic = BaseAddress + 0x490E;

		}

	}

}
