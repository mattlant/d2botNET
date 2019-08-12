#ifndef ASSEMBLYLOADER_H
#define ASSEMBLYLOADER_H

#include "ILoadable.h"
#include "AssemblyState.h"
#include "LoadableProxy.h"
#include "loadedassemblyinfo.h"

using namespace System;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Reflection;
using namespace botNET::Remoting;

namespace botNET
{
	///<summary>
	/// This class allows to access ILoadable module load and current state info.
	///</summary>
	 __gc public __sealed class AssemblyLoader
	{
	public private: //changed by mattlant to test crash stack tracing
		static Int64 _nextid;
		static ArrayList * _proxies;

		static AssemblyLoader() { _nextid = 1; _proxies = new ArrayList(); };

		static Byte ReadFile(String * filename) [];
		static String * Resolve(String * path, String * filename);
		static LoadableProxy * GetByAssembly(Assembly * assembly);
		static LoadableProxy * GetByName(String * name);
		static LoadableProxy * GetByID(Int64 id);
		static LoadedAssemblyInfo Load(String * filename, String * name, bool autoloaded);
		static LoadedAssemblyInfo Load(String * filename, bool autoloaded);
		static LoadedAssemblyInfo Load(String * name, Assembly * assembly, bool autoloaded);

	private public:
		static String * RandomName();

		static void AutoLoad();
		static void List();
		static LoadedAssemblyInfo GetList()[];
		static LoadedAssemblyInfo Load(String * filename, String * name);
		static LoadedAssemblyInfo Load(String * filename);
		static LoadedAssemblyInfo Load(String * name, Assembly * assembly);
		static void Unload();
		static void Unload(String * name);
		static void Unload(LoadableProxy * proxy);
		static void NewGame();
		static void EndGame();
		static void UserStart();
		static void UserStart(String * name);
		static void UserStop();
		static void UserStop(String * name);
		static void UserCommand(String * name, String * command, String * args[]);
		static void Kill();
		static void Kill(String * name);


	public:
		static Int64 GetIDByAssembly(Assembly * assembly);

		///<summary>
		/// Returns id assigned to calling assembly module during loading process.
		///</summary>
		__property static Int64 get_CurrentID();

		///<summary>
		/// Returns name of calling assembly module.
		///</summary>
		__property static String * get_CurrentName();

		///<summary>
		/// Returns base path of calling assembly module.
		///</summary>
		__property static String * get_CurrentPath();

		///<summary>
		/// Gives information about current state of calling assembly module.
		///</summary>
		__property static AssemblyState get_CurrentState();

		///<summary>
		/// Returns true if module was autoloaded.
		///</summary>
		__property static bool get_IsAutoLoaded();

		///<summary>
		/// Dynamically unloads requesting module.
		///</summary>
		///<remarks> This is same as if user typed <b>.unload &lt;callingassembly&gt;</b> in chat line. </remarks>
		static void UnloadCurrent();

		///<summary>
		/// Sends internal message to specified loaded module inside botNET core.
		///</summary>
		///<param name="ReceiverID"> ID of assembly to receive message. </param>
		///<param name="MessageType"> Type of message sent. </param>
		///<param name="Data"> Additional data. </param>
		static void SendMessageTo(Int64 ReceiverID, Int32 MessageType, Object * Data);

		///<summary>
		/// Sends internal message to all loaded modules inside botNET core.
		///</summary>
		///<param name="MessageType"> Type of message sent. </param>
		///<param name="Data"> Additional data. </param>
		static void SendMessageToAll(Int32 MessageType, Object * Data);
	};
}

#endif