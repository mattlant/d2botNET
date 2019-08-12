#ifndef SETTINGS_H
#define SETTINGS_H

using namespace System;
using namespace botNET;
using namespace botNET::Configuration;
using namespace botNET::Drawing;

namespace botNET
{
	namespace Configuration
	{
		__gc public class Config;
	}
	namespace Units
	{
		__gc public class PC;
	}
	__gc public class Settings
	{

	public:
		__property static System::Version*		get_Version() { return gVersion; }
		__property static String*		get_VersionString() { return gVersionString; }

		__property static bool			get_AutoMinimize() { return gAutoMinimize; }
		__property static void			set_AutoMinimize(bool value) { gAutoMinimize = value; }



	public private:

		static Config*		gGlobalConfig;

		static String*		gAutoLoaded __gc[];

		static System::Version*		gVersion;
		static String*		gVersionString;

		static bool			gAutoMinimize;

		static void DirectoryCreator(DirectoryInfo* path);
		static DirectoryInfo* GetDirectoryInfo(Config* cfg, String* root, String* node);
		static String* GetAutoLoaded()[];

	public:

		__gc class Directories
		{
		public:
			__property static DirectoryInfo*		get_Root() { return gRoot; }
 
			__property static DirectoryInfo*		get_Assemblies() { return gAssemblies; }
			__property static DirectoryInfo*		get_Output() { return gOutput; }
			__property static DirectoryInfo*		get_Settings() { return gSettings; }
			__property static DirectoryInfo*		get_Documents() { return gDocuments; }
			__property static DirectoryInfo*		get_Source() { return gSource; }
			__property static DirectoryInfo*		get_Images() { return gImages; }

			__property static DirectoryInfo*		get_Bots() { return gBots; }
			__property static DirectoryInfo*		get_Libraries() { return gLibraries; }
			__property static DirectoryInfo*		get_IDemos() { return gDemos; }
			__property static DirectoryInfo*		get_Utilities() { return gUtilities; }
			__property static DirectoryInfo*		get_Application() { return gApplications; }
		public private:
			// Paths
			static DirectoryInfo*		gRoot;

			static DirectoryInfo*		gAssemblies;
			static DirectoryInfo*		gOutput;
			static DirectoryInfo*		gSettings;
			static DirectoryInfo*		gDocuments;
			static DirectoryInfo*		gSource;
			static DirectoryInfo*		gImages;

			static DirectoryInfo*		gBots;
			static DirectoryInfo*		gLibraries;
			static DirectoryInfo*		gDemos;
			static DirectoryInfo*		gUtilities;
			static DirectoryInfo*		gApplications;
		};

		__gc class Remoting
		{
		public:

		public private:
			static bool			gEnabled;
			static UInt16		gBaseRemotingPort;
			static UInt16		gUsedRemotingPort;
		};

		__gc class Debugging
		{
		public:
			__property static String*		get_LogFile() { return gLogFile; }
			__property static bool			get_PrintExceptions() { return gPrintExceptions; }
			__property static void			set_PrintExceptions(bool value) { gPrintExceptions = value; }
		public private:
			static bool			gPrintExceptions;
			static String*		gLogFile;
		};


	};

}

#endif