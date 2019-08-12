#ifndef D2GAME_H
#define D2GAME_H

#include "definitions.h"


namespace botNET
{
	namespace Imports
	{
		__nogc class D2GAME
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			static BYTE IsSwitched(PlrMsg *ptPlrMsg);
			static void* fptrIsSwitched; //0x45B0

		};


	}


}

#endif