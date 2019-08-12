#pragma once


namespace botNET
{
	namespace Diagnostics
	{

		public __gc class CrashHandler
		{
		private public:
			static void DumpCrash(int type);
			static void WriteHeaderInfo(StringWriter* sw, int type);
			static void WriteILoadableInfo(StringWriter* sw);
			static void WriteThreadInfo(StringWriter* sw);
			static void WriteThreadInfo(StringWriter* sw, ArrayList* threads, String* type);
			static void WriteModuleInfo(StringWriter* sw);
			static void WriteCrashThreadInfo(StringWriter* sw);
			static void WriteAppDomainAssemblyInfo(StringWriter* sw);

			static String* GetStackTrace(System::Threading::Thread* t);

			static void DumpException(Exception* ex);

			static void CLRCrashHandler(Object* sender, UnhandledExceptionEventArgs* e);
		};

	}

}
