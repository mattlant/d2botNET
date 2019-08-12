
typedef unsigned __int32 __uint32;
//DWORD

#include "botnet.h"
 
#include "screenhookmanager.h"
#include "screenhook.h"
#include "botnethud.h"
#include "texthook.h"
#include "imagehook.h"
#include "game.h"
#include "settings.h"
#include "PC.h"
#include "UnitBase.h"
#include "unitcollectionbase.h"
#include "automap.h"

#include "AssemblyLoader.h"
#include "CompilerEnum.h"
#include "LineCompiler.h"
#include "Converter.h"
#include "log.h"
#include "botnetthread.h"
#include "crashhandler.h"
#include "ChatMessage.h"
#include "MessageEventArgs.h"
#include "importutils.h"
#include "d2exports.h"
#include "d2common.h"
#include "d2client.h"
#include "d2win.h" 
#include "d2gfx.h"
#include "d2cmp.h"
#include "d2game.h"
#include "d2launch.h"
#include "d2multi.h" 
#include "d2net.h"
#include "storm.h"
#include "bnclient.h"
#include "fog.h"
#include "patcher.h"
#include "remotecoreinfo.h"
#include "Initializing.h"

#define MAXMODULE 50


HANDLE hThread = INVALID_HANDLE_VALUE;
DWORD dwThreadId = 0;

using namespace botNET;
using namespace botNET::Messaging;
using namespace botNET::Compiler;
using namespace System::Diagnostics;

/**********************************************************
 * Initialization Call Back
 * The core.dll calls this to initialize
 *********************************************************/
void __stdcall cbInitialize()
{

}

/**********************************************************
 * Screen Print Call Back
 * Takes care of printing hooks to the screen
 * Added in debug type screen hooks
 *********************************************************/

int GCPrintCount = 0;
//Move to the callback, move screenhook to the manager or something
void __stdcall cbDrawPanel()
{
	try
	{
		//if(!botNET::Game::gIsInGame) return;

		//Get old font
		//DWORD oldfont = D2WIN::SetTextHookFont(0);

		//AlwaysOnScreenHooks::NewDisplay->Draw();
		botNET::Drawing::botNETHUD::mHUD->Draw();

		//D2WIN::SetTextHookFont(oldfont);

		//Game::Print("Draw End");
		//Game::logger->WriteLine("Draw End");
	}
	catch(Exception * ex)
	{
		if(Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex->Message);
	}
}

/**********************************************************
 * Quit Diablo II Call Back
 * Fires when user kits a key on the keyboard
 *********************************************************/
void __stdcall cbQuitDiabloII()
{
	try
	{
		AssemblyLoader::Unload();
		Patcher::Initialize(false);
	}
	catch(Exception * ex)
	{
		if(Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex->Message);
	}
}

/**********************************************************
 * Chat Line Call Back
 * Fires when you enter a message on the chat window
 *********************************************************/
bool __stdcall cbCommandLine(wchar_t* msg)
{
	//char * msg[0x100];

	//ConvertToUnicode(msgin, msg, 0xFF);

	try
	{
		String * message = Convert::ToString(msg);

		if (message->StartsWith(S"."))
		{
			String * trimmed = message->Trim();
			String * command = trimmed->Substring(0, (trimmed->IndexOf(' ') > 0 ? trimmed->IndexOf(S" ") : trimmed->Length))->ToLower();
			String * options = (trimmed->Length > command->Length + 1 ? trimmed->Substring(command->Length + 1)->Trim() : S"");

			if (command->Equals(S".load") || command->Equals(S".lo"))
			{
				if (options->Length == 0)
					botNET::Game::Print(S"Missing assembly name parameter");
				else
					AssemblyLoader::Load(options);
			}
			else if (command->Equals(S".unload") || command->Equals(S".un"))
			{
				if (options->Length == 0)
					botNET::Game::Print(S"Missing assembly name parameter");
				else
					AssemblyLoader::Unload(options);
			}
			else if (command->Equals(S".unloadall") || command->Equals(S".unall"))
			{
				AssemblyLoader::Unload();
			}
			else if (command->Equals(S".reload") || command->Equals(S".re"))
			{
				if (options->Length == 0)
					botNET::Game::Print(S"Missing assembly name parameter");
				else
				{
					AssemblyLoader::Unload(options);
					AssemblyLoader::Load(options);
				}
			}
			else if (command->Equals(S".kill") || command->Equals(S".ki"))
			{
				if (options->Length == 0)
					AssemblyLoader::Kill();
				else
					AssemblyLoader::Kill(options);
			}
			else if (command->Equals(S".list") || command->Equals(S".li"))
			{
				AssemblyLoader::List();
			}
			else if (command->Equals(S".start") || command->Equals(S".sta"))
			{
				if (options->Length == 0)
					AssemblyLoader::UserStart();
				else
					AssemblyLoader::UserStart(options);
			}
			else if (command->Equals(S".stop") || command->Equals(S".sto"))
			{
				if (options->Length == 0)
					AssemblyLoader::UserStop();
				else
					AssemblyLoader::UserStop(options);
			}
			else if (command->Equals(S".exec") || command->Equals(S".execcs") || command->Equals(S".execvb")
				|| command->Equals(S".execjs"))
			{
				CompilerEnum lang;

				if (command->Equals(S".execcs"))
					lang = CompilerEnum::CSharp;
				else if (command->Equals(S".execvb"))
					lang = CompilerEnum::VisualBasic;
				else
					lang = CompilerEnum::JScript;

				if (options->Length == 0)
					botNET::Game::Print(S"Missing code to execute");
				else
					LineCompiler::ExecuteOnNewThread(options, lang);
			}
			else if (command->Equals(S".run") || command->Equals(S".runcs") || command->Equals(S".runvb")
				|| command->Equals(S".runjs") || command->Equals(S".compile") || command->Equals(S".compilecs")
				|| command->Equals(S".compilevb") || command->Equals(S".compilejs"))
			{
				CompilerEnum lang;
				String * suffix;

				if (command->Equals(S".runcs") || command->Equals(S".compilecs"))
				{
					lang = CompilerEnum::CSharp;
					suffix = S".cs";
				}
				else if (command->Equals(S".runvb") || command->Equals(S".compilevb"))
				{
					lang = CompilerEnum::VisualBasic;
					suffix = S".vb";
				}
				else
				{
					lang = CompilerEnum::JScript;
					suffix = S".js";
				}

				if (options->Length == 0)
					botNET::Game::Print(S"Missing assembly name");
				else
				{
					String * args __gc[] = options->Split(S" "->ToCharArray());

					if (args->Length < 2)
						botNET::Game::Print(S"At least one source file must be given");
					else
					{
						String * name = args[0];
						String * files __gc[] = new String * __gc[args->Length - 1];

						args->Copy(args, 1, files, 0, args->Length - 1);
						for (int i = 0; i < files->Length; i++)
							if (!files[i]->ToLower()->EndsWith(suffix))
							{
								botNET::Game::Print(String::Concat(S"All source files should be ended with ", suffix));
								return false;
							}

						if (command->StartsWith(".run"))
						{
							/*
							System::Reflection::Assembly * assembly = LineCompiler::CompileInMemory(files, lang);
							if (assembly != 0)
								AssemblyLoader::Load(name, assembly);
							*/

							String * filename = String::Concat(Settings::Directories::gAssemblies, S"\\", AssemblyLoader::RandomName());
							if (LineCompiler::CompileToDisk(files, lang, filename, true))
							{
								AssemblyLoader::Load(filename, name);
								System::IO::File::Delete(String::Concat(filename, S".dll"));
								System::IO::File::Delete(String::Concat(filename, S".pdb"));
							}
						}
						else
							LineCompiler::CompileToDisk(files, lang, name, false);
					}
				}
			}
			else if (command->Equals(S".say") || command->Equals(S".sa"))
			{
				if (options->Length != 0 && botNET::Game::gIsInGame)
				{
					unsigned char mb __gc[] = System::Text::Encoding::ASCII->GetBytes(options);
					unsigned char pack __gc[] = new unsigned char __gc[6 + mb->Length];

					pack[0] = 0x15;
					pack[1] = 0x01;
					pack[2] = 0x00;

					Array::Copy(mb, 0, pack, 3, mb->Length);

					pack[pack->Length - 3] = 0x00;
					pack[pack->Length - 2] = 0x00;
					pack[pack->Length - 1] = 0x00;

					botNET::Game::SendPacketToServer(pack);
				}
			}
			else if (command->Equals(S".send") || command->Equals(S".se"))
			{
				if (options->Length != 0 && botNET::Game::gIsInGame)
				{
					unsigned char pack __gc[] = Converter::ToByteArray(options);

					if (pack != 0)
						botNET::Game::SendPacketToServer(pack);
					else
						botNET::Game::Print(S"Invalid packet data");
				}
			}
			else if (command->Equals(S".title") || command->Equals(S".ti"))
			{
				if (options->Length == 0)
					botNET::Game::Print(String::Concat(S"Titlebar: ", botNET::Game::Window::get_Title()));
				else
					botNET::Game::Window::set_Title(options);
			}
			else if (command->Equals(S".quit") || command->Equals(S".qu"))
			{
				botNET::Game::Quit();
			}
			else if (command->Equals(S".exit") || command->Equals(S".ex"))
			{
				botNET::Game::Exit();
			}
			else if (command->Equals(S".help") || command->Equals(S".?"))
			{
				String * help __gc[] =
				{
					S"Command list:",
					S"  .lo[ad] <assemblyname>",
					S"  .un[load] <assemblyname>",
					S"  .un[load]all",
					S"  .re[load] <assemblyname>",
					S"  .ki[ll] [assemblyname]",
					S"  .li[st]",
					S"  .sta[rt] [assemblyname]",
					S"  .sto[p] [assemblyname]",
					S"  .<assemblyname> <command> [arg1 [arg2 [...]]]",
					S"  .exec[cs|vb|js] <code>",
					S"  .run[cs|vb|js] <assemblyname> <file1> [file2 [file3 [...]]]",
					S"  .compile[cs|vb|js] <assemblyname> <file1> [file2 [file3 [...]]]",
					S"  .sa[y] <message>",
					S"  .se[nd] <packet>",
					S"  .ti[tle] [titlebar]",
					S"  .qu[it]",
					S"  .ex[it]",
					S"  .help|.?",
				};

				botNET::Game::Print(help);
			}
			else
			{
				String * args __gc[] = trimmed->Split(S" "->ToCharArray());

				if (args->Length < 2)
					botNET::Game::Print(S"Missing command name");
				else
				{
					String * subargs __gc[] = new String * [args->Length - 2];
					args->Copy(args, 2, subargs, 0, args->Length - 2);

					AssemblyLoader::UserCommand(args[0]->Substring(1), args[1], subargs);
				}
			}

			return false;
		}

		ChatMessage* m = new ChatMessage(message);
		MessageEventArgs* eventargs = new MessageEventArgs(m);
		ChatMessage::raise_OnMessage(NULL, eventargs);

		return eventargs->PassMessage;
	}
	catch (Exception * ex)
	{
		if(Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex);
	}
}

/**********************************************************
 * Main Entry Point
 * 
 *********************************************************/
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved)
{
	
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			MainInit();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			cbQuitDiabloII();
			break;
	}

	return TRUE;
}

bool somefunction()
{
	__asm
	{
		nop
	}
	return true;
}

