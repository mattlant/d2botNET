#include "botnet.h"
#include ".\screendrawpatch.h"
#include ".\game.h"
#include ".\screenhookmanager.h"
#include ".\d2client.h"
#include ".\d2win.h"
#include ".\automap.h"
#include "settings.h"

#include "initializing.h"

void __stdcall cbDrawPanel();

bool notinited = true;

namespace botNET
{
namespace Imports
{
namespace Patches
{


void __stdcall DrawPanelSTUB(void)
{
	cbDrawPanel();
	D2CLIENT::DrawPanel();
}

void __stdcall DrawIGScreenSTUB(void)
{
	try
	{
		if(notinited)
		{
			SecondaryInit();
			notinited = false;
		}

		//botNET::Game::RaiseDrawBeginEvent();
		botNET::Drawing::ScreenHookManager::raise_OnDrawSH();
		botNET::Game::RaiseDrawEndEvent();
	}
	catch(Exception * ex)
	{
		if(botNET::Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex);
	}

	D2WIN::DrawScreen();
}

void __stdcall DrawOOGScreenSTUB(void)
{
	try
	{
		if(notinited)
		{
			SecondaryInit();
			notinited = false;
		}

		//botNET::Game::RaiseDrawBeginEvent();
		botNET::Drawing::ScreenHookManager::raise_OnDrawSH();
		botNET::Game::RaiseDrawEndEvent();
	}
	catch(Exception * ex)
	{
		if(botNET::Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex);
	}
	D2WIN::DrawScreen();
}

void __stdcall DrawAutoMapSTUB(void)
{
	try
	{

		botNET::Mapping::AutoMap::DrawItems();
	}
	catch(Exception * ex)
	{
		if(botNET::Settings::Debugging::gPrintExceptions)
			botNET::Game::Print(ex);
	}

	D2CLIENT::DrawAutoMap();
}


}//Patches
}//Imports
}//botNET

