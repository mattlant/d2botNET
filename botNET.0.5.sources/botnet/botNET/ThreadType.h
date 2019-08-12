#ifndef THREADTYPE_H
#define THREADTYPE_H

using namespace System;

namespace botNET
{
	namespace Threading
	{
		///<summary>
		/// Describes type of botNETThread.
		///</summary>
		public __value enum ThreadType
		{
			///<summary>
			/// This thread will be killed when module quits game.
			///</summary>
			InGame = 1,

			///<summary>
			/// This thread will be killed when module enters game.
			///</summary>
			OutOfGame,

			///<summary>
			/// Threads of this type will exist all the time until module gets unloaded.
			///</summary>
			Persistant,
		};
	}
}

#endif