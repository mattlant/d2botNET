#include "botnet.h"
using namespace System::Diagnostics;
#include ".\log.h"
#include ".\game.h"



namespace botNET
{
	namespace Diagnostics
	{

		void Log::WriteLine(String* line)
		{
			Log::logger->WriteLine(line);
		}



	}



}