#ifndef REMOTEIDENTITY_H
#define REMOTEIDENTITY_H

#include "LoadedAssemblyInfo.h"

namespace botNET
{
	namespace Remoting
	{
		__gc public class RemoteCoreInfo : public System::MarshalByRefObject
		{
		public:
			RemoteCoreInfo() {}

			__property Int32 get_D2Handle();
			__property Int32 get_Port();

		public private:
			static void Initialize();
			static Int32 gPortUsed;

		};
	}
}

#endif

