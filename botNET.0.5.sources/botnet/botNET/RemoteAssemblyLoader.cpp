
using namespace System::Diagnostics;
using namespace System::Runtime::Remoting;

#include "botnet.h"
#include "RemoteAssemblyLoader.h"
#include "AssemblyLoader.h"

namespace botNET
{
	namespace Remoting
	{

		LoadedAssemblyInfo RemoteAssemblyLoader::get_LoadedAssemblies()[]
		{
			return AssemblyLoader::GetList();
		}

		LoadedAssemblyInfo RemoteAssemblyLoader::LoadAssembly(String* filename)
		{
			return AssemblyLoader::Load(filename);
		}

		void RemoteAssemblyLoader::UnloadAllAssemblies()
		{
			AssemblyLoader::Unload();
		}

		void RemoteAssemblyLoader::UnloadAssembly(String* name)
		{
			AssemblyLoader::Unload(name);
		}

		void RemoteAssemblyLoader::SendUserCommand(String* assembly, String* command, String* args[])
		{
			AssemblyLoader::UserCommand(assembly, command, args);

		}

		void RemoteAssemblyLoader::KillAllAssemblies()
		{
			AssemblyLoader::Kill();
		}

		void RemoteAssemblyLoader::KillAssembly(String* name)
		{
			AssemblyLoader::Kill(name);
		}


	}
}
