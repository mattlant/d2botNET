#include "botnet.h"

#include "botNETThread.h"
#include "ThreadType.h"

using namespace System;
using namespace System::Collections;
using namespace System::Reflection;
using namespace System::Threading;

namespace botNET
{
	namespace Threading
	{
		botNETThread::botNETThread(ThreadStart * start, botNET::Threading::ThreadType type, System::Reflection::Assembly * assembly)
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				_thread = new Thread(start);
				_type = type;
				_assembly = assembly;

				switch (type)
				{
					case ThreadType::InGame:
						_gameThreads->Add(this);
						break;
					case ThreadType::OutOfGame:
						_oogThreads->Add(this);
						break;
					case ThreadType::Persistant:
						_persistantThreads->Add(this);
						break;
				}
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		Assembly * botNETThread::get_Assembly()
		{
			return _assembly;
		};

		void botNETThread::SuspendAllThreads()
		{
			try
			{
				SuspendThreads(_gameThreads);
				SuspendThreads(_oogThreads);
				SuspendThreads(_persistantThreads);
			}
			catch (Exception *)
			{
			}
		};

		void botNETThread::SuspendThreads(ArrayList* threads)
		{
			try
			{
				IEnumerator* te = threads->GetEnumerator();
				while(te->MoveNext())
				{
					botNETThread* bnt = static_cast<botNETThread*>(te->Current);
					//Make sure it is not this thread
					//if(bnt->_thread
					//Make sure they are able to be suspended
                    if ((bnt->ThreadState & (ThreadState::Stopped | ThreadState::Unstarted)) != 0) continue;
					bnt->Suspend();
				}
			}
			catch(Exception*)
			{
			}
		}

		void botNETThread::KillGameThreads()
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				IEnumerator * e = _gameThreads->GetEnumerator();
				while (e->MoveNext())
					__try_cast<botNETThread *>(e->Current)->Abort();

				_gameThreads->Clear();
			}
			catch (Exception *)
			{
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		void botNETThread::KillOOGThreads()
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				IEnumerator * e = _oogThreads->GetEnumerator();
				while (e->MoveNext())
					__try_cast<botNETThread *>(e->Current)->Abort();

				_oogThreads->Clear();
			}
			catch (Exception *)
			{
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		void botNETThread::KillPersistantThreads()
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				IEnumerator * e = _persistantThreads->GetEnumerator();
				while (e->MoveNext())
					__try_cast<botNETThread *>(e->Current)->Abort();

				_persistantThreads->Clear();
			}
			catch (Exception *)
			{
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		void botNETThread::KillAssemblyThreads(System::Reflection::Assembly * assembly)
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				ArrayList * a;
				botNETThread * t;
				IEnumerator * e;

				a = new ArrayList();

				e = _gameThreads->GetEnumerator();
				while (e->MoveNext())
				{
					t = __try_cast<botNETThread *>(e->Current);
					if (t->Assembly == assembly)
					{
						t->Abort();
						a->Add(t);
					}
				}
				e = a->GetEnumerator();
				while (e->MoveNext())
					_gameThreads->Remove(e->Current);
				a->Clear();

				e = _oogThreads->GetEnumerator();
				while (e->MoveNext())
				{
					t = __try_cast<botNETThread *>(e->Current);
					if (t->Assembly == assembly)
					{
						t->Abort();
						a->Add(t);
					}
				}
				e = a->GetEnumerator();
				while (e->MoveNext())
					_oogThreads->Remove(e->Current);
				a->Clear();

				e = _persistantThreads->GetEnumerator();
				while (e->MoveNext())
				{
					t = __try_cast<botNETThread *>(e->Current);
					if (t->Assembly == assembly)
					{
						t->Abort();
						a->Add(t);
					}
				}
				e = a->GetEnumerator();
				while (e->MoveNext())
					_persistantThreads->Remove(e->Current);
				a->Clear();
			}
			catch (Exception *)
			{
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		void botNETThread::KillAssemblyGameThreads(System::Reflection::Assembly * assembly)
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				ArrayList * a;
				botNETThread * t;
				IEnumerator * e;

				a = new ArrayList();

				e = _gameThreads->GetEnumerator();
				while (e->MoveNext())
				{
					t = __try_cast<botNETThread *>(e->Current);
					if (t->Assembly == assembly)
					{
						t->Abort();
						a->Add(t);
					}
				}
				e = a->GetEnumerator();
				while (e->MoveNext())
					_gameThreads->Remove(e->Current);
				a->Clear();
			}
			catch (Exception *)
			{
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		///////////////////////////////////////////////////////////////////////

		ArrayList* botNETThread::get_GameThreads()
		{
			return _gameThreads;
		}

		ArrayList* botNETThread::get_OOGThreads()
		{
			return _oogThreads;
		}

		ArrayList* botNETThread::get_PersistantThreads()
		{
			return _persistantThreads;
		}

		botNETThread::botNETThread(ThreadStart * start, botNET::Threading::ThreadType type)
		{
			Monitor::Enter(__typeof(botNETThread));

			try
			{
				_thread = new Thread(start);
				_type = type;
				_assembly = Assembly::GetCallingAssembly();

				switch (type)
				{
					case ThreadType::InGame:
						_gameThreads->Add(this);
						break;
					case ThreadType::OutOfGame:
						_oogThreads->Add(this);
						break;
					case ThreadType::Persistant:
						_persistantThreads->Add(this);
						break;
				}
			}
			__finally
			{
				Monitor::Exit(__typeof(botNETThread));
			}
		};

		bool botNETThread::get_IsAlive()
		{
			return _thread->get_IsAlive();
		};

		String * botNETThread::get_Name()
		{
			return _thread->get_Name();
		};

		void botNETThread::set_Name(String * name)
		{
			_thread->set_Name(name);
		};

		ThreadPriority botNETThread::get_Priority()
		{
			return _thread->get_Priority();
		};

		void botNETThread::set_Priority(ThreadPriority priority)
		{
			_thread->set_Priority(priority);
		};

		ThreadState botNETThread::get_ThreadState()
		{
			return _thread->get_ThreadState();
		};

		ThreadType botNETThread::get_ThreadType()
		{
			return _type;
		};

		///////////////////////////////////////////////////////////////////////

		void botNETThread::Abort()
		{
			_thread->Abort();
		};

		void botNETThread::Abort(Object * stateInfo)
		{
			_thread->Abort(stateInfo);
		};

		bool botNETThread::Equals(Object * obj)
		{
			return _thread->Equals(obj);
		};

		int botNETThread::GetHashCode()
		{
			return _thread->GetHashCode();
		};

		void botNETThread::Interrupt()
		{
			_thread->Interrupt();
		};

		void botNETThread::Join()
		{
			_thread->Join();
		};

		bool botNETThread::Join(int millisecondsTimeout)
		{
			return _thread->Join(millisecondsTimeout);
		};

		bool botNETThread::Join(TimeSpan timeout)
		{
			return _thread->Join(timeout);
		};

		void botNETThread::Resume()
		{
			_thread->Resume();
		};

		void botNETThread::Start()
		{
			_thread->Start();
		};

		void botNETThread::Suspend()
		{
			_thread->Suspend();
		};

		///////////////////////////////////////////////////////////////////////

		bool botNETThread::Equals(Object * objA, Object * objB)
		{
			return Thread::Equals(objA, objB);
		};

		void botNETThread::Sleep(int millisecondsTimeout)
		{
			Thread::Sleep(millisecondsTimeout);
		};

		void botNETThread::Sleep(TimeSpan timeout)
		{
			Thread::Sleep(timeout);
		};

		//void botNETThread::ResetAbort()
		//{
		//	Thread::ResetAbort();
		//};
	}
}