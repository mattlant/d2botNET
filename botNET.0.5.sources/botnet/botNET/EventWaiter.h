#ifndef EVENTWAITER_H
#define EVENTWAITER_H

#include "ThreadType.h"

using namespace System;
using namespace System::Threading;

namespace botNET
{
	namespace Threading
	{
		public __sealed __gc class EventWaiter
		{
		private:
			static Object * endMonitor;
			static Object * newMonitor;

			static EventWaiter() { endMonitor = new Object(); newMonitor = new Object(); };

		private public:
			static void SignalEndGame();
			static void SignalNewGame();

		public:
			static void WaitForEndGame();
			static void WaitForNewGame();
		};
	}
}

#endif