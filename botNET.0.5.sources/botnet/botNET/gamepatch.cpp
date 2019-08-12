#include "botnet.h"
#include ".\gamepatch.h"
#include ".\game.h"
#include ".\assemblyloader.h"
#include ".\d2client.h"
#include ".\d2win.h"
#include ".\d2cmp.h"
#include "settings.h"
#include "pc.h"


namespace botNET
{
namespace Imports
{
namespace Patches
{

/*void NewGameHANDLER (void)
{
	if (!botNET::Game::gIsInGame)
	{
		try
		{
			botNET::Game::gGameStartTime = DateTime::Now;
			botNET::Game::gIsInGame = true;

			botNET::Units::PC::mMe = new botNET::Units::PC();

			AssemblyLoader::NewGame();
			botNET::Game::RaiseBeginGameEvent(new botNET::GameEventArgs(0));
		}
		catch(Exception * ex)
		{
			if(botNET::Settings::Debugging::gPrintExceptions)
				botNET::Game::Print(ex->Message);
		}
	}
}*/

void __stdcall ActChangeSTUB(int act)
{
	//Only works maximized for act changes. Still works fine when entering a game

	//r1ch: moved to better place (NewGameHandler)
	/*try
	{
		if(!botNET::Game::gIsInGame)
		{
			botNET::Game::gGameStartTime = DateTime::Now;
			botNET::Game::gIsInGame = true;

			botNET::Units::PC::mMe = new botNET::Units::PC();

			AssemblyLoader::NewGame();
			botNET::Game::RaiseBeginGameEvent(new botNET::GameEventArgs(0));
		}
		//else
		//{
		//	Game::Print("Switched Acts");
		//}

	}
	catch(Exception * ex)
	{
		if(botNET::Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex->Message);
	}*/

	D2CMP::SetAct(act);

}

//works fine minimized
void __stdcall EndGameHANDLER (UnitPlayer * ptPlayer)
{
	//botNET::Game::Print ("EndGameHANDLER");

	if (!botNET::Game::gIsInGame)
		return;

	try
	{
		AssemblyLoader::EndGame();
		botNET::Game::RaiseEndGameEvent(new botNET::GameEventArgs((DateTime::Now - botNET::Game::gGameStartTime).TotalMilliseconds));

		botNET::Game::gIsInGame = false;

		//TODO: Remove global event handlers
		//System::Game::RemoveClickHandlers(botNET::BeginGameEventHandler, botNET::Game::OnBeginGameEvent);
	}
	catch(Exception * ex)
	{
		if(botNET::Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex->Message);
	}

	D2CLIENT::UpdatePlayerStruct (ptPlayer);
	//D2WIN::SetPalette((BYTE)unk);
}

void __declspec(naked) EndGameSTUB (void)
{
	__asm
	{
		push ecx
		call EndGameHANDLER
		ret
	}
}

void __declspec(naked) NewGameSTUB (void)
{
	__asm
	{
		call NewGameHANDLER
		ret
	}
}

//TODO: Find another intercept, this appears to be called every frame (or more!)
Room1 * __stdcall NewGameHANDLER(void)
{
	//botNET::Game::Print ("NewGameHANDLER");
	Room1 * ptRoom = D2CLIENT::GetPlayerRoom();

	if (ptRoom && !botNET::Game::gIsInGame)
	{
		try
		{
			botNET::Game::gGameStartTime = DateTime::Now;
			botNET::Game::gIsInGame = true;

			botNET::Units::PC::mMe = new botNET::Units::PC();

			AssemblyLoader::NewGame();
			botNET::Game::RaiseBeginGameEvent(new botNET::GameEventArgs(0));
		}
		catch(Exception * ex)
		{
			if(botNET::Settings::Debugging::gPrintExceptions)
				botNET::Game::Print(ex->Message);
		}
	}

	return ptRoom;
}


}//Patches
}//Imports
}//botNET

