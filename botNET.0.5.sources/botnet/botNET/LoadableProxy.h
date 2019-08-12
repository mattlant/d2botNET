#ifndef LOADABLEPROXY_H
#define LOADABLEPROXY_H

#include "ILoadable.h"
#include "AssemblyState.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Threading;

namespace botNET
{
	namespace Threading
 	{
		__gc public __sealed class botNETThread;
	}

	using namespace botNET::Threading;

	__gc private __sealed class LoadableProxy
	{
	private:
		Int64 _id;
		String * _path;
		String * _name;
		Assembly * _assembly;
		ILoadable * _module;
		AssemblyState _state;
		bool _autoloaded;

		botNETThread * _loadthread;
		botNETThread * _gamethread;
		botNETThread * _userthread;

		void DoLoad();
		void DoNewGame();
		void DoUserStart();
		void UserStop(bool passToModule);

	private public:
		LoadableProxy(Int64 id, String * path, String * name, Assembly * assembly, ILoadable * module, bool autoloaded);

		__property Int64 get_ID();
		__property String * get_Path();
		__property String * get_Name();
		__property Assembly * get_Assembly();
		__property ILoadable * get_Module();
		__property AssemblyState get_State();
		__property bool get_IsAutoLoaded();

		void Load();
		void Unload();
		void NewGame();
		void EndGame();
		void UserStart();
		void UserStop();
		void UserCommand(String * command, String * args[]);
		void ReceiveMessage(Int64 SenderID, Int32 MessageType, Object * Data);

		void Kill();
	};
}

#endif