#include "botnet.h"

#include "LoadableProxy.h"
#include "Game.h"
#include "botnetthread.h"
#include "settings.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Threading;
using namespace botNET::Threading;

namespace botNET
{
	//
	// Constructors
	///////////////////////////////////////////////////////////////////////////

	LoadableProxy::LoadableProxy(Int64 id, String * path, String * name, System::Reflection::Assembly * assembly, ILoadable * module, bool autoloaded)
	{
		_id = id;
		_path = path;
		_name = name;
		_assembly = assembly;
		_module = module;
		_state = AssemblyState::Unknown;
		_autoloaded = autoloaded;
	};

	//
	// Properties
	///////////////////////////////////////////////////////////////////////////

	Int64 LoadableProxy::get_ID()
	{
		return _id;
	};

	String * LoadableProxy::get_Path()
	{
		return _path;
	};

	String * LoadableProxy::get_Name()
	{
		return _name;
	};

	Assembly * LoadableProxy::get_Assembly()
	{
		return _assembly;
	};

	ILoadable * LoadableProxy::get_Module()
	{
		return _module;
	};

	AssemblyState LoadableProxy::get_State()
	{
		return _state;
	};

	bool LoadableProxy::get_IsAutoLoaded()
	{
		return _autoloaded;
	};

	//
	// Methods
	///////////////////////////////////////////////////////////////////////////

	void LoadableProxy::Load()
	{
		_state = AssemblyState::Loading;

		_loadthread = new botNETThread(new ThreadStart(this, &LoadableProxy::DoLoad), ThreadType::Persistant);
		_loadthread->Name = String::Concat(_name, S":LoadThread");
		_loadthread->Start();

		//UserStart();

		if (Game::gIsInGame)
			NewGame();

		_state = AssemblyState::Loaded;
	};

	void LoadableProxy::DoLoad()
	{
		try
		{
			_module->Load();
		}
		catch (ThreadAbortException *)
		{
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::Unload()
	{
		_state = AssemblyState::Disposing;

		if(Game::gIsInGame)
			this->EndGame();

		//UserStop(false);

		if (_loadthread != 0)
		{
			if ((_loadthread->ThreadState & (ThreadState::Stopped | ThreadState::Unstarted)) == 0)
			{
				_loadthread->Abort();
				_loadthread->Join();
			}
			_loadthread = 0;
		}

		try
		{
			_module->Dispose();
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}

		_state = AssemblyState::Disposed;
	};

	void LoadableProxy::NewGame()
	{
		_gamethread = new botNETThread(new ThreadStart(this, &LoadableProxy::DoNewGame), ThreadType::Persistant);
		_gamethread->Name = String::Concat(_name, S":GameThread");
		_gamethread->Start();
	};

	void LoadableProxy::DoNewGame()
	{
		try
		{
			_module->NewGame();
		}
		catch (ThreadAbortException *)
		{
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::EndGame()
	{
		if (_gamethread != 0)
		{
			if ((_gamethread->ThreadState & (ThreadState::Stopped | ThreadState::Unstarted)) == 0)
			{
				_gamethread->Abort();
				_gamethread->Join();
			}
			_gamethread = 0;
		}

		try
		{
			_module->EndGame(DateTime::Now.Subtract(Game::gGameStartTime));
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::UserStart()
	{
		_userthread = new botNETThread(new ThreadStart(this, &LoadableProxy::DoUserStart), ThreadType::Persistant);
		_userthread->Name = String::Concat(_name, S":UserThread");
		_userthread->Start();
	};

	void LoadableProxy::DoUserStart()
	{
		try
		{
		}
		catch (ThreadAbortException *)
		{
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::UserStop(bool passToModule)
	{
		if (_userthread != 0)
		{
			if ((_userthread->ThreadState & (ThreadState::Stopped | ThreadState::Unstarted)) == 0)
			{
				_userthread->Abort();
				_userthread->Join();
			}
			_userthread = 0;
		}

		if (passToModule)
		{
			try
			{
			}
			catch (Exception * ex)
			{
				if(Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
			}
		}
	};

	void LoadableProxy::UserStop()
	{
		UserStop(true);
	};

	void LoadableProxy::UserCommand(String * command, String * args[])
	{
		try
		{
			_module->UserCommand(command, args);
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::ReceiveMessage(Int64 SenderID, Int32 MessageType, Object * Data)
	{
		try
		{
			_module->ReceiveMessage(SenderID, MessageType, Data);
		}
		catch (Exception * ex)
		{
			if(Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
		}
	};

	void LoadableProxy::Kill()
	{
		try
		{
			if (_gamethread != 0)
			{
				if ((_gamethread->ThreadState & (ThreadState::Stopped | ThreadState::Unstarted)) == 0)
				{
					_gamethread->Abort();
					//_gamethread->Join();
				}
				_gamethread = 0;
			}
		}
		catch (Exception *)
		{
		}
	};

	///////////////////////////////////////////////////////////////////////////
};