#ifndef BOTNETTHREAD_H
#define BOTNETTHREAD_H

#include "ThreadType.h"

using namespace System;
using namespace System::Collections;
using namespace System::Reflection;
using namespace System::Threading;

namespace botNET
{
	namespace Threading
	{
		public __sealed __gc class botNETThread
		{
		public private: //changed by mattlant to test stack tracing on crashes
			Thread * _thread;
			ThreadType _type;
			System::Reflection::Assembly * _assembly;

			static ArrayList * _gameThreads;
			static ArrayList * _oogThreads;
			static ArrayList * _persistantThreads;

			static botNETThread() { _gameThreads = new ArrayList(); _oogThreads = new ArrayList(); _persistantThreads = new ArrayList(); };

		private public:
			botNETThread(ThreadStart * start, ThreadType type, System::Reflection::Assembly * assembly);

			__property System::Reflection::Assembly * get_Assembly();

			static void SuspendAllThreads();
			static void SuspendThreads(ArrayList* threads);
			static void KillGameThreads();
			static void KillOOGThreads();
			static void KillPersistantThreads();
			static void KillAssemblyThreads(System::Reflection::Assembly * assembly);
			static void KillAssemblyGameThreads(System::Reflection::Assembly * assembly);

		public:
			__property static ArrayList * get_GameThreads();
			__property static ArrayList * get_OOGThreads();
			__property static ArrayList * get_PersistantThreads();

			botNETThread(ThreadStart * start, ThreadType type);

			//__property ApartmentState get_ApartmentState();
			//__property void set_ApartmentState(ApartmentState state);
			//__property CultureInfo get_CurrentCulture();
			//__property void set_CurrentCulture(CultureInfo * info);
			//__property CultureInfo get_CurrentUICulture();
			//__property void set_CurrentUICulture(CultureInfo * info);
			__property bool get_IsAlive();
			//__property bool get_IsBackground();
			//__property void set_IsBackground(bool background);
			//__property bool get_IsThreadPoolThread();
			__property String * get_Name();
			__property void set_Name(String * name);
			__property ThreadPriority get_Priority();
			__property void set_Priority(ThreadPriority priority);
			__property System::Threading::ThreadState get_ThreadState();
			__property ThreadType get_ThreadType();

			void Abort();
			void Abort(Object * stateInfo);
			virtual bool Equals(Object * obj);
			virtual int GetHashCode();
			void Interrupt();
			void Join();
			bool Join(int millisecondsTimeout);
			bool Join(TimeSpan timeout);
			void Resume();
			void Start();
			void Suspend();

			static bool Equals(Object * objA, Object * objB);
			static void Sleep(int millisecondsTimeout);
			static void Sleep(TimeSpan timeout);
			//static void ResetAbort();
		};
	}
}

#endif