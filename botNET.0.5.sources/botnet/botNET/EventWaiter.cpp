#include "botnet.h"

#include "EventWaiter.h"

using namespace System;
using namespace System::Threading;

namespace botNET
{
	namespace Threading
	{
		void EventWaiter::SignalEndGame()
		{
			Monitor::Enter(endMonitor);
			Monitor::PulseAll(endMonitor);
			Monitor::Exit(endMonitor);
		};

		void EventWaiter::SignalNewGame()
		{
			Monitor::Enter(newMonitor);
			Monitor::PulseAll(newMonitor);
			Monitor::Exit(newMonitor);
		};

		void EventWaiter::WaitForEndGame()
		{
			Monitor::Enter(endMonitor);
			try
			{
				Monitor::Wait(endMonitor);
			}
			__finally
			{
				Monitor::Exit(endMonitor);
			}
		};

		void EventWaiter::WaitForNewGame()
		{
			Monitor::Enter(newMonitor);
			try
			{
				Monitor::Wait(newMonitor);
			}
			__finally
			{
				Monitor::Exit(newMonitor);
			}
		};
	}
}