#include "botnet.h"

#include "LineCompiler.h"
#include "Game.h"
#include "settings.h"

using namespace System;
using namespace System::CodeDom;
using namespace System::CodeDom::Compiler;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Threading;
using namespace Microsoft::CSharp;
using namespace Microsoft::VisualBasic;
using namespace Microsoft::JScript;

namespace botNET
{
	namespace Compiler
	{
		void LineCompiler::CheckAndRootPaths(String * files[])
		{
			for (int i = 0; i < files->Length; i++)
			if (System::IO::Path::IsPathRooted(files[i]))
			{
				if (!File::Exists(files[i]))
					throw new ApplicationException(String::Concat(S"File ", files[i], S" cannot be found"));
			}
			else
			{
				if (!File::Exists(String::Concat(Settings::Directories::gRoot, S"\\Source\\", files[i])))
					throw new ApplicationException(String::Concat(S"File ", Settings::Directories::gRoot, S"\\Source\\", files[i], S" cannot be found"));
				else
					files[i] = String::Concat(Settings::Directories::gRoot, S"\\Source\\", files[i]);
			}
		};

		void LineCompiler::AddReferences(CompilerParameters * params)
		{
			params->ReferencedAssemblies->Add(S"System.dll");
			params->ReferencedAssemblies->Add(S"System.Data.dll");
			params->ReferencedAssemblies->Add(S"System.XML.dll");
			params->ReferencedAssemblies->Add(S"System.Drawing.dll");
			params->ReferencedAssemblies->Add(S"System.Windows.Forms.dll");

			params->ReferencedAssemblies->Add(String::Concat(Settings::Directories::gRoot, S"\\botNET.dll"));

			Queue * q = new Queue();
			q->Enqueue(Settings::Directories::gLibraries->FullName);
			while (q->Count > 0)
			{
				String * curr = __try_cast<String *>(q->Dequeue());

				String * subs __gc[] = Directory::GetDirectories(curr);
				for (int i = 0; i < subs->Length; i++) 
					q->Enqueue(subs[i]); 

				String * libs __gc[] = Directory::GetFiles(curr, S"*.dll");
				for (int i = 0; i < libs->Length; i++)
					params->ReferencedAssemblies->Add(libs[i]); 
			} 
		};

		void LineCompiler::Execute(String * code, CompilerEnum lang)
		{
			try
			{
				ICodeCompiler * compiler;
				String * source;

				switch (lang)
				{
					case CompilerEnum::CSharp:
						compiler = (new CSharpCodeProvider())->CreateCompiler();
						source = String::Concat(S"using System;\n using botNET;\n using botNET.Units;\n namespace botNET {\n public class InLineCode {\n public void Exec() {\n", code, S"\n }\n }\n }\n");
						break;
					case CompilerEnum::VisualBasic:
						compiler = (new VBCodeProvider())->CreateCompiler();
						source = String::Concat(S"Imports System\n Imports botNET\n Imports botNET.Units\n Namespace botNET\n Public Class InLineCode\n Public Sub Exec()\n", code, S"\n End Sub\n End Class\n End Namespace\n");
						break;
					case CompilerEnum::JScript:
						compiler = (new JScriptCodeProvider())->CreateCompiler();
						source = String::Concat(S"import System;\n import botNET;\n import botNET.Units;\n package botNET {\n public class InLineCode {\n function Exec() {\n", code, S"}\n }\n }\n");
						break;
					default:
						throw new ApplicationException("Language not supported");
				}

				CompilerParameters * params = new CompilerParameters();

				params->GenerateInMemory = true;
				params->IncludeDebugInformation = true;
				params->WarningLevel = 3;
				params->TreatWarningsAsErrors = false;
				params->TempFiles->KeepFiles = false;

				AddReferences(params);

				CompilerResults * results = compiler->CompileAssemblyFromSource(params, source);

				if (results->Errors->Count > 0)
				{
					int i = 1;
					Game::Print(String::Concat(S"Execution failed, ", results->Errors->Count.ToString(), S" errors and warnings in total"));
					for (IEnumerator * err = results->Errors->GetEnumerator(); err->MoveNext(); i++)
					{
						CompilerError * ce = __try_cast<CompilerError *>(err->Current);
						Game::Print(String::Concat(S"  ", i.ToString(), S": ", ce->ErrorText));
					}

					return;
				}

				Assembly * assembly = results->CompiledAssembly;
				Type * inlinecode = assembly->GetType("botNET.InLineCode");
				MethodInfo * method = inlinecode->GetMethod("Exec");
				Object * instance = Activator::CreateInstance(inlinecode);

				try
				{
					method->Invoke(instance, 0);
				}
				catch (Exception * ex)
				{
					Game::Print(String::Concat("Error during execution, ", ex->ToString()));
					System::Windows::Forms::MessageBox::Show(ex->ToString());
				}
			}
			catch (Exception * ex)
			{
				Game::Print(ex);
			}
		};

		void LineCompiler::ExecuteOnNewThread(String * code, CompilerEnum lang)
		{
			ExecuteThreadStarter * starter = new ExecuteThreadStarter(code, lang);

			Thread * thread = new Thread(new ThreadStart(starter, ExecuteThreadStarter::Start));
			thread->Name = S"Executor";
			thread->Start();
		}

		Assembly * LineCompiler::CompileInMemory(String * files[], CompilerEnum lang)
		{
			try
			{
				ICodeCompiler * compiler;

				switch (lang)
				{
					case CompilerEnum::CSharp:
						compiler = (new CSharpCodeProvider())->CreateCompiler();
						break;
					case CompilerEnum::VisualBasic:
						compiler = (new VBCodeProvider())->CreateCompiler();
						break;
					case CompilerEnum::JScript:
						compiler = (new JScriptCodeProvider())->CreateCompiler();
						break;
					default:
						throw new ApplicationException("Language not supported");
				}

				CheckAndRootPaths(files);

				CompilerParameters * params = new CompilerParameters();

				params->GenerateInMemory = true;
				params->IncludeDebugInformation = true;
				params->WarningLevel = 3;
				params->TreatWarningsAsErrors = false;
				params->TempFiles->KeepFiles = false;

				AddReferences(params);

				CompilerResults * results = compiler->CompileAssemblyFromFileBatch(params, files);

				if (results->Errors->Count > 0)
				{
					Game::Print(String::Concat(S"Compilation failed, ", results->Errors->Count.ToString(), S" errors and warnings in total"));
					for (IEnumerator * err = results->Errors->GetEnumerator(); err->MoveNext(); )
					{
						CompilerError * ce = __try_cast<CompilerError *>(err->Current);
						Game::Print(String::Concat(S"  ", ce->FileName, S"(", ce->Line.ToString(), S",", ce->Column.ToString(), S")", (ce->IsWarning ? S": warning " : S": error "), ce->ErrorNumber, S": ", ce->ErrorText));
					}

					return 0;
				}

				return results->CompiledAssembly;
			}
			catch (Exception * ex)
			{
				Game::Print(ex);
				return 0;
			}
		};

		bool LineCompiler::CompileToDisk(String * files[], CompilerEnum lang, String * outfile, bool silent)
		{
			try
			{
				ICodeCompiler * compiler;

				switch (lang)
				{
					case CompilerEnum::CSharp:
						compiler = (new CSharpCodeProvider())->CreateCompiler();
						break;
					case CompilerEnum::VisualBasic:
						compiler = (new VBCodeProvider())->CreateCompiler();
						break;
					case CompilerEnum::JScript:
						compiler = (new JScriptCodeProvider())->CreateCompiler();
						break;
					default:
						throw new ApplicationException("Language not supported");
				}

				CheckAndRootPaths(files);

				if (!outfile->ToLower()->EndsWith(S".dll"))
					outfile = String::Concat(outfile, S".dll");
				if (!System::IO::Path::IsPathRooted(outfile))
					outfile = String::Concat(Settings::Directories::gAssemblies, S"\\", outfile);
				if (File::Exists(outfile))
					File::Delete(outfile);

				CompilerParameters * params = new CompilerParameters();

				params->OutputAssembly = outfile;
				params->IncludeDebugInformation = true;
				params->WarningLevel = 3;
				params->TreatWarningsAsErrors = false;
				params->TempFiles->KeepFiles = false;

				AddReferences(params);

				CompilerResults * results = compiler->CompileAssemblyFromFileBatch(params, files);

				if (results->Errors->Count > 0)
				{
					Game::Print(String::Concat(S"Compilation failed, ", results->Errors->Count.ToString(), S" errors and warnings in total"));
					for (IEnumerator * err = results->Errors->GetEnumerator(); err->MoveNext(); )
					{
						CompilerError * ce = __try_cast<CompilerError *>(err->Current);
						Game::Print(String::Concat(S"  ", ce->FileName, S"(", ce->Line.ToString(), S",", ce->Column.ToString(), S")", (ce->IsWarning ? S": warning " : S": error "), ce->ErrorNumber, S": ", ce->ErrorText));
					}

					return false;
				}

				if (!silent)
					Game::Print(S"Compilation successfull");

				return true;
			}
			catch (Exception * ex)
			{
				Game::Print(ex);
				return false;
			}
		};

		///////////////////////////////////////////////////////////////////////////

		LineCompiler::ExecuteThreadStarter::ExecuteThreadStarter(String * code, CompilerEnum lang)
			: _code(code), _lang(lang)
		{
		};

		void LineCompiler::ExecuteThreadStarter::Start()
		{
			LineCompiler::Execute(_code, _lang);
		};
	}
}

