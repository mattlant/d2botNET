#ifndef LOADEDASSEMBLYINFO_H
#define LOADEDASSEMBLYINFO_H

namespace botNET
{
	namespace Remoting
	{

		//[Serializable]
		__value public struct LoadedAssemblyInfo
		{
			LoadedAssemblyInfo(Int64 id, String* name) : ID(id), Name(name) {}
			Int64 ID;
			String* Name;
			//Assembly* TheAssembly;
		};

	}
}

#endif


/*



		*/