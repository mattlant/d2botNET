#include "botnet.h"
#include "storm.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void STORM::Initialize()
		{
			BaseAddress = Importer::Storm->BaseAddress.ToInt32();


		}

	}

}
