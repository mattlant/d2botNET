#include "botnet.h"
#include "d2cmp.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2CMP::Initialize()
		{
			BaseAddress = Importer::D2Cmp->BaseAddress.ToInt32();


		}

	}

}
