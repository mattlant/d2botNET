#ifndef REMOTEASSEMBLYLOADER_H
#define REMOTEASSEMBLYLOADER_H

#include "LoadedAssemblyInfo.h"

namespace botNET
{
	namespace Remoting
	{
		__gc public class RemoteAssemblyLoader : public System::MarshalByRefObject
		{
		public:
			RemoteAssemblyLoader() {}

			__property LoadedAssemblyInfo get_LoadedAssemblies()[];

			LoadedAssemblyInfo LoadAssembly(String * filename);
			void UnloadAllAssemblies();
			void UnloadAssembly(String * name);
			void SendUserCommand(String * assembly, String * command, String * args[]);
			void KillAllAssemblies();
			void KillAssembly(String * name);

		};
	}
}

#endif

