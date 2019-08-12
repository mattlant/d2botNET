#include "botnet.h"

using namespace System::IO;
using namespace System::Collections;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::Threading;

#include ".\crashhandler.h"
#include ".\botnetthread.h"
#include ".\loadableproxy.h"
#include ".\assemblyloader.h"
#include ".\log.h"
#include ".\Game.h"
#include ".\botnet.h"
#include ".\d2client.h"

using namespace botNET::Threading;

namespace botNET
{
	namespace Diagnostics
	{

		void CrashHandler::DumpException(Exception* ex)
		{

		}

		void CrashHandler::DumpCrash(int type)
		{

			try{
				botNETThread::SuspendAllThreads();

				StringWriter* sw = new StringWriter();
				WriteHeaderInfo(sw, type);
				sw->WriteLine();
				WriteCrashThreadInfo(sw);
				sw->WriteLine();
				WriteILoadableInfo(sw);
				sw->WriteLine();
				WriteThreadInfo(sw);
				sw->WriteLine();
				WriteAppDomainAssemblyInfo(sw);
				sw->WriteLine();
				WriteModuleInfo(sw);
				botNET::Diagnostics::Log::WriteLine(sw->ToString());
				botNET::Diagnostics::Log::logger->Flush();

				// Worth a try to avoid players dying while the exception window is up
				try
				{
					if (Game::gIsInGame)
					{
						D2CLIENT::QuitGame();
					}
				}
				catch (...)
				{
				}

				System::Windows::Forms::MessageBox::Show(String::Concat(
					S"botNET has detected a Diablo II exception. Please see this botNET log for more information: \r\n",
					botNET::Diagnostics::Log::file), "botNET Exception Handler");
			}
			catch(Exception* ex)
			{
				System::Windows::Forms::MessageBox::Show(ex->ToString(), S"try-catch");
			}



		}

		void CrashHandler::WriteHeaderInfo(StringWriter* sw, int type)
		{

			sw->WriteLine(String::Concat(S"botNET has detected ", type?S"an assertion failure":S"an unhandled exception", " in Diablo II."));
			sw->WriteLine(S"Please see the Diablo II crash dump files for Diablo II specific details");
			sw->WriteLine(S"The following is a detailed list of Assemblies and running threads.");

		}

		void CrashHandler::WriteILoadableInfo(StringWriter* sw)
		{
			sw->WriteLine(S"******************** LOADED ILOADABLES **********************");
			//Enumerate thru all assemblies via its proxy
			IEnumerator* ie = AssemblyLoader::_proxies->GetEnumerator();
			while(ie->MoveNext())
			{
				LoadableProxy* lp = static_cast<LoadableProxy*>(ie->Current);
				sw->WriteLine(lp->Assembly->ToString());

				sw->WriteLine(S"Dependant assemblies:");
				AssemblyName* names __gc[] = lp->Assembly->GetReferencedAssemblies();
				if(names->Length == 0)
				{
					sw->WriteLine(S"\tNone");
					sw->WriteLine();
					continue;
				}
				IEnumerator* enames = names->GetEnumerator();
				while(enames->MoveNext())
				{
  					AssemblyName* name = static_cast<AssemblyName*>(enames->Current);
					sw->WriteLine(String::Concat(S"\t", name->ToString()));
				}


				sw->WriteLine();
			}

		}

		void CrashHandler::WriteThreadInfo(StringWriter* sw)
		{
			sw->WriteLine(S"****************** ALL THREADS' STACK TRACES *******************");
			WriteThreadInfo(sw, botNETThread::_persistantThreads, S"---PERSISTANT THREADS---");
			WriteThreadInfo(sw, botNETThread::_gameThreads, S"---IG THREADS---");
			WriteThreadInfo(sw, botNETThread::_oogThreads, S"---OOG THREADS---");

		}

		void CrashHandler::WriteThreadInfo(StringWriter* sw, ArrayList* threads, String* type)
		{
			sw->WriteLine(type);

			IEnumerator* ie = threads->GetEnumerator();
			while(ie->MoveNext())
			{
				botNETThread* bnt = static_cast<botNETThread*>(ie->Current);
				if(!bnt->IsAlive) continue;
				sw->WriteLine(String::Concat(S"ORIGIN ASSEMBLY: ", bnt->Assembly->FullName));
				sw->WriteLine(String::Concat(S"THREAD NAME: ", (bnt->Name && bnt->Name->Length)?bnt->Name:S"Unnamed thread"));

				sw->Write(GetStackTrace(bnt->_thread));
				sw->WriteLine();
				sw->WriteLine();
			}
		}

		void CrashHandler::WriteModuleInfo(StringWriter* sw)
		{
			
			sw->WriteLine(S"**************** ALL LOADED D2 PROCESS MODULES ******************");
			System::Diagnostics::Process* p = System::Diagnostics::Process::GetCurrentProcess();
			ProcessModuleCollection* c = p->Modules;
			IEnumerator* ie = c->GetEnumerator();
			while(ie->MoveNext())
			{
				ProcessModule* m = static_cast<ProcessModule*>(ie->Current);
				sw->WriteLine(m->ToString());
			}
			

		}

		void CrashHandler::WriteAppDomainAssemblyInfo(StringWriter* sw)
		{
			
			sw->WriteLine(S"****************** ALL LOADED .NET ASSMBLIES  ********************");
			AppDomain* curr = AppDomain::CurrentDomain;
			Assembly* as __gc[] = curr->GetAssemblies();
			
			IEnumerator* ie = as->GetEnumerator();
			while(ie->MoveNext())
			{
				Assembly* a = static_cast<Assembly*>(ie->Current);
				sw->WriteLine(a->FullName);
				IEnumerator* ems = a->GetModules()->GetEnumerator();
				while(ems->MoveNext())
				{
					Module* m = static_cast<Module*>(ems->Current);
					sw->WriteLine(String::Concat(S"\t", m->FullyQualifiedName));
				}
				sw->WriteLine();
			}
			
			

		}

		void CrashHandler::WriteCrashThreadInfo(StringWriter* sw)
		{
			sw->WriteLine(S"**************** CRASHED THREAD STACK TRACE *****************");

			Char delimiter[] = (S"\r")->ToCharArray();

			String* st = Environment::StackTrace;
			String* splst __gc[] = st->Split(delimiter);

			String* output = S"";


			for(int i = 6; i < splst->Length; i++)
			{
				output = String::Concat(output, S"\r", splst[i]);
			}

			sw->WriteLine(output);
			sw->WriteLine();

		}

		String* CrashHandler::GetStackTrace(Thread* t)
		{

			System::Diagnostics::StackTrace __gc * trace1 = __gc new System::Diagnostics::StackTrace(t, true);

			System::String __gc * text1 = System::Environment::NewLine;
			System::Text::StringBuilder __gc * builder1 = __gc new System::Text::StringBuilder(255);
			for (System::Int32 num1 = 0; (num1 < trace1->FrameCount); num1++)
			{
					System::Diagnostics::StackFrame __gc * frame1 = trace1->GetFrame(num1);
					builder1->Append(S"   at ");
					System::Reflection::MethodBase __gc * base1 = frame1->GetMethod();
					System::Type __gc * type1 = base1->DeclaringType;
					if (type1 != 0)
					{
						System::String __gc * text2 = type1->Namespace;
						if (text2 != 0)
						{
								builder1->Append(text2);
								if (builder1 != 0)
								{
									builder1->Append(S".");
								}
						}
						builder1->Append(type1->Name);
						builder1->Append(S".");
					}
					builder1->Append(base1->Name);
					builder1->Append(S"(");
					System::Reflection::ParameterInfo __gc * infoArray1 __gc [] = base1->GetParameters();
					for (System::Int32 num2 = 0; (num2 < infoArray1->Length); num2++)
					{
						System::String __gc * text3 = S"<UnknownType>";
						if (infoArray1[num2]->ParameterType != 0)
						{
								text3 = infoArray1[num2]->ParameterType->Name;
						}
						builder1->Append(System::String::Concat(((num2 != 0) ? S", " : S""), text3, S" ", infoArray1[num2]->Name));
					}
					builder1->Append(S")");
					if (frame1->GetILOffset() != -1)
					{
						System::String __gc * text4 = 0;
						try
						{
								text4 = frame1->GetFileName();
						}
						catch (System::Security::SecurityException*)
						{
						}
						if (text4 != 0)
						{
								builder1->Append(System::String::Concat(S" in ", text4, S":line ", frame1->GetFileLineNumber().ToString()));
						}
					}
					if (num1 != (trace1->FrameCount - 1))
					{
						builder1->Append(text1);
					}
			}
			return builder1->ToString();



		}
		void CrashHandler::CLRCrashHandler(Object* sender, UnhandledExceptionEventArgs* e)
		{
			botNET::Game::Print(static_cast<Exception*>(e->ExceptionObject));
			if(e->IsTerminating)
				System::Windows::Forms::MessageBox::Show(String::Concat(
				S"botNET Encountered an internally unhandled exception and will now quit\r\n",
				static_cast<Exception*>(e->ExceptionObject)->ToString()),
				S"botNET Unhandled Exception");
		}

	}

}

