
using namespace System::Diagnostics;
using namespace System::Runtime::Remoting;

#include "botnet.h"
#include "loadedassemblyinfo.h"

namespace botNET
{
	namespace Remoting
	{

	}
}
/*

			__property UInt32 get_D2Handle();
			__property AssemblyIDPair get_LoadedAssemblies()[];

			AssemblyIDPair LoadAssembly(String * filename);
			void UnloadAllAssemblies();
			void UnloadAssembly(String * name);
			void SendUserCommand(String * assembly, String * command, String * args[]);
			void KillAllAssemblies();
			void KillAssembly(String * name);

			void SendMessageToAssembly(Int64 ReceiverID, Int32 MessageType, Object * Data);
			void SendMessageToAllAssemblies(Int32 MessageType, Object * Data);

*/