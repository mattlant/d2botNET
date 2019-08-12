#include "botnet.h"
#include "initializing.h"
#include "screenhookmanager.h"
#include "screenhook.h"
#include "botnethud.h"
#include "texthook.h"
#include "imagehook.h"
#include "game.h"
#include "settings.h"
#include "configuration.h"
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

bool donecoreentry = false;

namespace botNET
{
	void MainInit()
	{
		if(donecoreentry) return;

		try
		{
			// Temp
			AppDomain * tDomain = AppDomain::CurrentDomain;

			// Init our crits
			InitializeCriticalSection(&PrintBufferCritSect);
			InitializeCriticalSection(&RoomCritSect);

			// Set our version info
			Settings::gVersion = (Assembly::GetExecutingAssembly()->GetName())->Version;
			Settings::gVersionString = Settings::gVersion->ToString();

			// Setup all our Paths
			Settings::Directories::gRoot = new DirectoryInfo(Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location));
			String* root = Settings::Directories::gRoot->FullName;

			// Get our config data and set our settings
			if(!File::Exists(String::Concat(root, "\\botnet.config")))
			{
				System::Windows::Forms::MessageBox::Show("the botNET.config file does not exist. Please recreate file or reinstall botNET.");
				return;
			}

			Settings::gGlobalConfig = new Config();
			Settings::gGlobalConfig->AbsoluteLoad(String::Concat(root, "\\botnet.config"));
			Config* cfg = Settings::gGlobalConfig;

			Settings::Directories::gAssemblies = Settings::GetDirectoryInfo(cfg, root, "Assemblies");
			Settings::Directories::gOutput = Settings::GetDirectoryInfo(cfg, root, "Output");
			Settings::Directories::gSettings = Settings::GetDirectoryInfo(cfg, root, "Settings");
			Settings::Directories::gDocuments = Settings::GetDirectoryInfo(cfg, root, "Documents");
			Settings::Directories::gSource = Settings::GetDirectoryInfo(cfg, root, "Source");
			Settings::Directories::gImages = Settings::GetDirectoryInfo(cfg, root, "Images"); 

			String* assroot = Settings::Directories::gAssemblies->FullName;

			Settings::Directories::gBots = Settings::GetDirectoryInfo(cfg, assroot, "Bots");
			Settings::Directories::gLibraries = Settings::GetDirectoryInfo(cfg, assroot, "Libraries");
			Settings::Directories::gDemos = Settings::GetDirectoryInfo(cfg, assroot, "Demos");
			Settings::Directories::gUtilities = Settings::GetDirectoryInfo(cfg, assroot, "Utilities");
			Settings::Directories::gApplications = Settings::GetDirectoryInfo(cfg, assroot, "Applications");


			Settings::Remoting::gBaseRemotingPort = Settings::gGlobalConfig->GetValue("Remoting/BaseRemotingPort", 43250);
			Settings::Remoting::gEnabled = Settings::gGlobalConfig->GetValue("Remoting/Enabled", true);
			Settings::Debugging::gLogFile = String::Concat(Settings::Directories::gOutput->FullName, S"/", Settings::gGlobalConfig->GetValue("Debugging/LogFile", "botNETLog"));


			int lognumber = 0;
			while(lognumber++ < 16)
			{
				try
				{
					//Setup a logger
					botNET::Diagnostics::Log::file = String::Concat(Settings::Debugging::gLogFile, S"-", lognumber.ToString("D2"), S".log");
					botNET::Diagnostics::Log::logger = new StreamWriter(botNET::Diagnostics::Log::file);
					break;
				}
				catch(Exception*)
				{
					continue;
				}
			}

			// Initialize all of botNET's offsets 
			Importer::Initialize();
			botNET::Imports::D2CLIENT::Initialize();
			botNET::Imports::D2COMMON::Initialize(); 
			botNET::Imports::D2GFX::Initialize();
			botNET::Imports::D2WIN::Initialize();
			botNET::Imports::D2CMP::Initialize();
			botNET::Imports::D2GAME::Initialize();
			botNET::Imports::D2LAUNCH::Initialize();
			botNET::Imports::D2MULTI::Initialize();
			botNET::Imports::D2NET::Initialize();
			botNET::Imports::STORM::Initialize();
			botNET::Imports::BNCLIENT::Initialize();
			botNET::Imports::FOG::Initialize();

			// Patch d2
			Patcher::Initialize(true);


			//Set misc settings
			if(Game::gIsInGame = (*D2CLIENT::PlayerUnit) > 0)
				PC::mMe = new PC();

			ScreenHookManager::IDBaseCount = 0;
			Settings::gAutoMinimize = false;


			// Set AppDomain settings
			tDomain->SetData("APPBASE", root);
			tDomain->SetData("BINPATH_PROBE_ONLY", root);
			//a->SetData("CACHE_BASE", botNET::Settings::Directories::gRoot);
			//a->SetData("DYNAMIC_BASE", botNET::Settings::Directories::gRoot);
			//a->SetCachePath(String::Concat(botNET::Settings::Directories::gRoot, S"\\Assemblies\\ShadowCache"));
			//a->SetShadowCopyPath(botNET::Game::LibrariesDirectory);
			//a->SetShadowCopyFiles(); 
			tDomain->SetData("APP_NAME", S"botNET");
			String* rootname = Settings::Directories::gRoot->Name; 
			String* assrootname = String::Concat(rootname, S"\\", Settings::Directories::gAssemblies->Name);
			tDomain->AppendPrivatePath(rootname);
			tDomain->AppendPrivatePath(String::Concat(assrootname));
			tDomain->AppendPrivatePath(String::Concat(assrootname, S"\\", Settings::Directories::Bots->Name));
			tDomain->AppendPrivatePath(String::Concat(assrootname, S"\\", Settings::Directories::Libraries->Name));
			tDomain->AppendPrivatePath(String::Concat(assrootname, S"\\", Settings::Directories::Application->Name));
			tDomain->AppendPrivatePath(String::Concat(assrootname, S"\\", Settings::Directories::Utilities->Name));
			tDomain->UnhandledException += new UnhandledExceptionEventHandler(NULL, &botNET::Diagnostics::CrashHandler::CLRCrashHandler);

			botNETHUD::mHUD = new botNET::Drawing::botNETHUD();

		}
		catch(Exception * ex)
		{
			System::Windows::Forms::MessageBox::Show(ex->ToString()); 
		} 

		donecoreentry = true;
	}
	void SecondaryInit()
	{			
		Settings::gAutoLoaded = Settings::GetAutoLoaded();
		if(Settings::Remoting::gEnabled)
			botNET::Remoting::RemoteCoreInfo::Initialize();
		AssemblyLoader::AutoLoad();
	}
}