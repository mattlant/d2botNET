#include "botnet.h"

#include "AssemblyLoader.h"
#include "LoadableAttribute.h"
#include "Game.h"
#include "botNETThread.h"
#include "EventWaiter.h"
#include "CompilerEnum.h"
#include "LineCompiler.h"
#include "settings.h"

using namespace System;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Threading;
using namespace botNET::Threading;
using namespace botNET::Compiler;

namespace botNET
{
	//
	// Helper functions
	///////////////////////////////////////////////////////////////////////////

	Byte AssemblyLoader::ReadFile(String * filename)[]
	{
		FileStream * fs = File::OpenRead(filename);
		Byte buffer __gc[] = new Byte[(int) fs->Length];

		fs->Read(buffer, 0, (int) fs->Length);
		fs->Close();

		return buffer;
	}

	String * AssemblyLoader::Resolve(String * path, String * filename)
	{
		String * ret = 0;

		if (File::Exists(String::Concat(path, S"\\", filename)))
			return String::Concat(path, S"\\", filename);

		String * dirs[] = Directory::GetDirectories(path);
		IEnumerator * e = dirs->GetEnumerator();

		while (e->MoveNext())
			if ((ret = Resolve(String::Concat(__try_cast<String *>(e->Current)), filename)) != 0)
				break;

		return ret;
	}

	LoadableProxy * AssemblyLoader::GetByAssembly(System::Reflection::Assembly * assembly)
	{
		for (int i = 0; i < _proxies->Count; i++)
			if ((__try_cast<LoadableProxy *>(_proxies->get_Item(i)))->Assembly == assembly)
				return __try_cast<LoadableProxy *>(_proxies->get_Item(i));

		return 0;
	}

	LoadableProxy * AssemblyLoader::GetByName(String * name)
	{
		name = name->ToLower();

		for (int i = 0; i < _proxies->Count; i++)
			if ((__try_cast<LoadableProxy *>(_proxies->get_Item(i)))->Name->ToLower()->Equals(name))
				return __try_cast<LoadableProxy *>(_proxies->get_Item(i));

		return 0;
	}

	LoadableProxy * AssemblyLoader::GetByID(Int64 id)
	{
		for (int i = 0; i < _proxies->Count; i++)
			if ((__try_cast<LoadableProxy *>(_proxies->get_Item(i)))->ID == id)
				return __try_cast<LoadableProxy *>(_proxies->get_Item(i));

		return 0;
	}

	//
	// Main internal functions
	///////////////////////////////////////////////////////////////////////

	String * AssemblyLoader::RandomName()
	{
		__wchar_t alnum[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		__wchar_t partial[8];

		Random * rnd = new Random();

		for (int i = 0; i < 7; i++)
			partial[i] = alnum[rnd->Next(36)];

		return new String(partial);
	}

	void AssemblyLoader::AutoLoad()
	{
		try
		{
			String * line;

			String* nodes __gc[] = Settings::gAutoLoaded;

			for(int i = 0; i < nodes->Length; i++)
			{
				line = nodes[i];

				if (line->IndexOf(S";") > -1)
					line = line->Substring(0, line->IndexOf(S";")); 
				line = line->Trim();

				if (line->Length == 0)
					continue;

				if (line->IndexOf(S"|") > -1)
				{
					if (line->IndexOf(S"|") != line->LastIndexOf(S"|"))
						continue;

					String * name = line->Substring(0, line->IndexOf(S"|"))->Trim();
					String * files[] = line->Substring(line->IndexOf(S"|") + 1, line->Length - line->IndexOf(S"|") - 1)->Trim()->Split(S","->ToCharArray());

					ArrayList * flist = new ArrayList();

					for (int i = 0; i < files->Length; i++)
						if (files[i]->Trim()->Length > 0)
							flist->Add(files[i]->Trim());

					files = __try_cast<String * __gc[]>(flist->ToArray(__typeof(String)));
					flist = 0;

					if (files->Length == 0)
						continue;

					String * suffix = 0;
					CompilerEnum lang = CompilerEnum::CSharp;

					bool ok = true;
					for (int i = 0; i < files->Length; i++)
					{
						String * s = files[i]->ToLower();

						if (s->Length < 4)
						{
							ok = false;
							break;
						}

						if (suffix == 0)
							if (s->EndsWith(S".cs"))
							{
								suffix = S".cs";
								lang = CompilerEnum::CSharp;
							}
							else if (s->EndsWith(S".vb"))
							{
								suffix = S".vb";
								lang = CompilerEnum::VisualBasic;
							}
							else if (s->EndsWith(S".js"))
							{
								suffix = S".js";
								lang = CompilerEnum::JScript;
							}
							else
							{
								ok = false;
								break;
							}
						else
							if (!s->EndsWith(suffix))
							{
								ok = false;
								break;
							}
					}

					if (!ok)
						continue;

					/*
					System::Reflection::Assembly * assembly = LineCompiler::CompileInMemory(files, lang);
					if (assembly != 0)
						Load(name, assembly, true);
					*/

					String * filename = String::Concat(Settings::Directories::gAssemblies->FullName, S"\\", RandomName());
					if (LineCompiler::CompileToDisk(files, lang, filename, true))
					{
						Load(filename, name, true);
						File::Delete(String::Concat(filename, S".dll"));
						File::Delete(String::Concat(filename, S".pdb"));
					}
				}
				else if (line->ToLower()->EndsWith(S".bot"))
				{
					String * srcfile = String::Copy(line);
					String * name = line->Substring(0, line->Length - 4);

					if (name->IndexOf(S"\\") > -1)
						name = name->Substring(name->LastIndexOf(S"\\") + 1, name->Length - name->LastIndexOf(S"\\") - 1);

					if (System::IO::Path::IsPathRooted(srcfile) && File::Exists(srcfile))
					{
					}
					else if (srcfile->IndexOf("\\") < 0)
						srcfile = Resolve(String::Concat(Settings::Directories::gRoot, S"\\Source"), srcfile);
					else if (File::Exists(String::Concat(Settings::Directories::gRoot, S"\\Source\\", srcfile)))
						srcfile = String::Concat(Settings::Directories::gRoot, S"\\Source\\", srcfile);
					else
						srcfile = 0;

					if (!srcfile)
						continue;

					StreamReader * s2;
					String * line2;

					ArrayList * flist = new ArrayList();

					s2 = File::OpenText(srcfile);

					while (line2 = s2->ReadLine())
					{
						if (line2->IndexOf(S";") > -1)
							line2 = line2->Substring(0, line2->IndexOf(S";"));
						line2 = line2->Trim();

						if (line2->Length == 0)
							continue;

						flist->Add(line2);
					}

					s2->Close();

					String * files[] = __try_cast<String * __gc[]>(flist->ToArray(__typeof(String)));
					flist = 0;

					if (files->Length == 0)
						continue;

					String * suffix = 0;
					CompilerEnum lang = CompilerEnum::CSharp;

					bool ok = true;
					for (int i = 0; i < files->Length; i++)
					{
						String * s = files[i]->ToLower();

						if (s->Length < 4)
						{
							ok = false;
							break;
						}

						if (suffix == 0)
							if (s->EndsWith(S".cs"))
							{
								suffix = S".cs";
								lang = CompilerEnum::CSharp;
							}
							else if (s->EndsWith(S".vb"))
							{
								suffix = S".vb";
								lang = CompilerEnum::VisualBasic;
							}
							else if (s->EndsWith(S".js"))
							{
								suffix = S".js";
								lang = CompilerEnum::JScript;
							}
							else
							{
								ok = false;
								break;
							}
						else
							if (!s->EndsWith(suffix))
							{
								ok = false;
								break;
							}
					}

					if (!ok)
						continue;

					/*
					System::Reflection::Assembly * assembly = LineCompiler::CompileInMemory(files, lang);
					if (assembly != 0)
						Load(name, assembly, true);
					*/

					String * filename = String::Concat(Settings::Directories::gAssemblies->FullName, S"\\", RandomName());
					if (LineCompiler::CompileToDisk(files, lang, filename, true))
					{
						Load(filename, name, true);
						File::Delete(String::Concat(filename, S".dll"));
						File::Delete(String::Concat(filename, S".pdb"));
					}
				}
				else
					Load(line, true);
			}

		}
		catch (Exception * ex)
		{
			System::Windows::Forms::MessageBox::Show(ex->ToString()); 
			Game::Print(ex);
		}
	}

	void AssemblyLoader::List()
	{
		if (_proxies->Count <= 0)
			Game::Print("No assemblies loaded");
		else
		{
			Game::Print(String::Concat(_proxies->Count.ToString(), _proxies->Count == 1 ? S" assembly loaded:" : S" assemblies loaded:"));
			for (int i = 0; i < _proxies->Count; i++)
				Game::Print(String::Concat(S"  ", (i + 1).ToString(), S": ", (__try_cast<LoadableProxy *>(_proxies->get_Item(i)))->Name));
		}
	}

	LoadedAssemblyInfo AssemblyLoader::GetList()[]
	{
		if (_proxies->Count <= 0)
			return new LoadedAssemblyInfo  [0];

		LoadedAssemblyInfo temp __gc[] = new LoadedAssemblyInfo [_proxies->Count];

			for (int i = 0; i < _proxies->Count; i++)
				temp[i] = LoadedAssemblyInfo( static_cast<LoadableProxy*>(_proxies->Item[i])->ID, static_cast<LoadableProxy*>(_proxies->Item[i])->Name) ;

		return temp;
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * filename, String * name, bool autoloaded)
	{
		LoadedAssemblyInfo inf = LoadedAssemblyInfo(0, 0);

		try
		{
			String * pdbfilename;
			String * path;
			System::Reflection::Assembly * assembly;
			Type * types __gc[];
			bool found;

			if (!filename->ToLower()->EndsWith(S".dll"))
				filename = String::Concat(filename, S".dll");

			if (System::IO::Path::IsPathRooted(filename) && File::Exists(filename))
			{
			}
			else if (filename->IndexOf("\\") < 0)
				filename = Resolve(String::Copy(Settings::Directories::gAssemblies->FullName), filename);
			else if (File::Exists(String::Concat(Settings::Directories::gAssemblies->FullName, S"\\", filename)))
				filename = String::Concat(Settings::Directories::gAssemblies->FullName, S"\\", filename);
			else
				filename = 0;

			if (!filename)
				throw new FileNotFoundException(S"The assembly could not be found");

			if (GetByName(name) != 0)
				throw new ApplicationException(S"Assembly already loaded");

			path = filename->Substring(0, filename->LastIndexOf(S"\\"));
			pdbfilename = String::Concat(filename->Substring(0, filename->Length - 4), S".pdb");
			if (File::Exists(pdbfilename))
				assembly = AppDomain::CurrentDomain->Load(ReadFile(filename), ReadFile(pdbfilename));
			else
				assembly = AppDomain::CurrentDomain->Load(ReadFile(filename));

			found = false;
			types = assembly->GetTypes();
			for (int i = 0; i < types->Length; i++)
			{
				Type * t = types[i];
				if (t->IsClass && !t->IsAbstract && t->GetInterface(S"botNET.ILoadable") != 0 && t->GetCustomAttributes(__typeof(LoadableAttribute), false)->Length > 0)
				{
					ILoadable * module = __try_cast<ILoadable *>(assembly->CreateInstance(t->FullName));
					LoadableProxy * proxy = new LoadableProxy(_nextid++, path, name, assembly, module, autoloaded);

					_proxies->Add(proxy);
					found = true;

					proxy->Load();
					inf = LoadedAssemblyInfo(proxy->ID, proxy->Name);
					break;
				}
			}

			if (!found)
				throw new ApplicationException(S"Could not find any non abstract ILoadable implementations marked with LoadableAttribute");

		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}

		return inf;
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * filename, String * name)
	{
		return Load(filename, name, false);
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * filename, bool autoloaded)
	{
		String * name = String::Copy(filename);

		if (name->ToLower()->EndsWith(S".dll"))
			name = name->Substring(0, name->Length - 4);
		if (name->IndexOf(S"\\") > -1)
			name = name->Substring(name->LastIndexOf(S"\\") + 1, name->Length - name->LastIndexOf(S"\\") - 1);

		return Load(filename, name, false);
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * filename)
	{
		return Load(filename, false);
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * name, System::Reflection::Assembly * assembly, bool autoloaded)
	{
		LoadedAssemblyInfo inf = LoadedAssemblyInfo(0, 0);

		try
		{
			bool found;
			Type * types __gc[];
			Type * t;

			if (name->ToLower()->EndsWith(S".dll"))
				name = name->Substring(0, name->Length - 4);

			if (name->IndexOf(S"\\") > -1)
				name = name->Substring(name->LastIndexOf(S"\\") + 1, name->Length - name->LastIndexOf(S"\\") - 1);

			if (GetByName(name) != 0)
				Unload(name);

			found = false;
			types = assembly->GetTypes();
			for (int i = 0; i < types->Length; i++)
			{
				t = types[i];

				if (t->IsClass && !t->IsAbstract && t->GetInterface(S"botNET.ILoadable") != 0 && t->GetCustomAttributes(__typeof(LoadableAttribute), false)->Length > 0)
				{
					ILoadable * module = __try_cast<ILoadable *>(assembly->CreateInstance(t->FullName));
					LoadableProxy * proxy = new LoadableProxy(_nextid++, String::Concat(Settings::Directories::gRoot, S"\\Assemblies\\"), name, assembly, module, autoloaded);

					_proxies->Add(proxy);
					found = true;

					proxy->Load();
					inf = LoadedAssemblyInfo(proxy->ID, proxy->Name);
					break;
				}
			}

			if (!found)
				throw new ApplicationException(S"Could not find any non abstract ILoadable implementations marked with LoadableAttribute");


		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}

		return inf;
	}

	LoadedAssemblyInfo AssemblyLoader::Load(String * name, System::Reflection::Assembly * assembly)
	{
		return Load(name, assembly, false);
	}

	void AssemblyLoader::Unload()
	{
		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				LoadableProxy * proxy = __try_cast<LoadableProxy *>(_proxies->get_Item(i));

				botNETThread::KillAssemblyThreads(proxy->Assembly);

				proxy->Unload();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}

		_proxies->Clear();
	}

	void AssemblyLoader::Unload(String * name)
	{
		try
		{
			LoadableProxy * proxy = GetByName(name);

			if (proxy == 0)
				throw new ApplicationException(S"Assembly not loaded");

			botNETThread::KillAssemblyThreads(proxy->Assembly);

			proxy->Unload();
			_proxies->Remove(proxy);
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	void AssemblyLoader::Unload(LoadableProxy * proxy)
	{
		try
		{
			botNETThread::KillAssemblyThreads(proxy->Assembly);

			proxy->Unload();
			_proxies->Remove(proxy);
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	void AssemblyLoader::NewGame()
	{
		botNETThread::KillOOGThreads();
		EventWaiter::SignalNewGame();

		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->NewGame();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::EndGame()
	{
		botNETThread::KillGameThreads();
		EventWaiter::SignalEndGame();

		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->EndGame();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::UserStart()
	{
		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->UserStart();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::UserStart(String * name)
	{
		try
		{
			LoadableProxy * proxy = GetByName(name);

			if (proxy == 0)
				throw new ApplicationException(S"Assembly not loaded");

			proxy->UserStart();
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	void AssemblyLoader::UserStop()
	{
		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->UserStop();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::UserStop(String * name)
	{
		try
		{
			LoadableProxy * proxy = GetByName(name);

			if (proxy == 0)
				throw new ApplicationException(S"Assembly not loaded");

			proxy->UserStop();
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	void AssemblyLoader::UserCommand(String * name, String * command, String * args[])
	{
		try
		{
			LoadableProxy * proxy = GetByName(name);

			if (proxy == 0)
				throw new ApplicationException(S"Assembly not found");

			proxy->UserCommand(command, args);
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	void AssemblyLoader::Kill()
	{
		botNETThread::KillGameThreads();

		for (int i = 0; i < _proxies->Count; i++)
		{
			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->Kill();
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::Kill(String * name)
	{
		try
		{
			LoadableProxy * proxy = GetByName(name);

			if (proxy == 0)
				throw new ApplicationException(S"Assembly not loaded");

			botNETThread::KillAssemblyGameThreads(proxy->Assembly);

			proxy->Kill();
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}

	Int64 AssemblyLoader::GetIDByAssembly(System::Reflection::Assembly * assembly)
	{
		LoadableProxy * proxy = GetByAssembly(assembly);

		if (proxy != 0)
			return proxy->get_ID();

		return 0;
	}

	//
	// Public functions
	///////////////////////////////////////////////////////////////////////////

	Int64 AssemblyLoader::get_CurrentID()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy != 0)
			return proxy->get_ID();

		return 0;
	}

	String * AssemblyLoader::get_CurrentName()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy != 0)
			return proxy->get_Name();

		return 0;
	}

	String * AssemblyLoader::get_CurrentPath()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy != 0)
			return proxy->get_Path();

		return 0;
	}

	AssemblyState AssemblyLoader::get_CurrentState()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy != 0)
			return proxy->get_State();

		return AssemblyState::Unknown;
	}

	bool AssemblyLoader::get_IsAutoLoaded()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy != 0)
			return proxy->get_IsAutoLoaded();

		return false;
	}

	void AssemblyLoader::UnloadCurrent()
	{
		LoadableProxy * proxy = GetByAssembly(Assembly::GetCallingAssembly());

		if (proxy == 0)
			throw new ApplicationException(S"Assembly already unloaded");

		Unload(proxy);
	}

	void AssemblyLoader::SendMessageToAll(Int32 MessageType, Object * Data)
	{
		LoadableProxy * sender = GetByAssembly(Assembly::GetCallingAssembly());
		if (sender == 0)
			return;

		for (int i = 0; i < _proxies->Count; i++)
		{
			if (sender->ID == __try_cast<LoadableProxy *>(_proxies->get_Item(i))->ID)
				continue;

			try
			{
				__try_cast<LoadableProxy *>(_proxies->get_Item(i))->ReceiveMessage(sender->ID, MessageType, Data);
			}
			catch (Exception * ex)
			{
				if (Settings::Debugging::gPrintExceptions)
					Game::Print(ex);
				else
					Game::Print(ex->Message);
			}
		}
	}

	void AssemblyLoader::SendMessageTo(Int64 ReceiverID, Int32 MessageType, Object * Data)
	{
		LoadableProxy * sender = GetByAssembly(Assembly::GetCallingAssembly());
		if (sender == 0)
			return;

		LoadableProxy * receiver = GetByID(ReceiverID);
		if (receiver == 0)
			throw new ApplicationException(S"Assembly not loaded");

		try
		{
			receiver->ReceiveMessage(sender->ID, MessageType, Data);
		}
		catch (Exception * ex)
		{
			if (Settings::Debugging::gPrintExceptions)
				Game::Print(ex);
			else
				Game::Print(ex->Message);
		}
	}
}