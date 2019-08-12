#include "botnet.h"
#include ".\globalmessagehandlerpatch.h"
#include ".\game.h"
#include ".\eventargs.h"
#include ".\storm.h"
#include "settings.h"

namespace botNET
{
namespace Imports
{
namespace Patches
{


bool __stdcall MessageHandlerSTUB(HWND hwnd, int Message, WPARAM wParam, LPARAM lParam, bool * NotDef, int * retVal)
{
	//Game::Print(S"MessageHandler");

	bool passback = true;


	//String* temp = String::Concat(Message.ToString("X8"), S", ", wParam.ToString("X8"), S", ", lParam.ToString("X8")
	//	, S", ", (*NotDef).ToString(), S", ", (*retVal).ToString("X8"));
	//Game::Print(temp);
	//Game::logger->WriteLine(temp);
	

	switch(Message)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		try
		{
			WORD y = (WORD)(lParam >> 16);
			WORD x = (WORD)lParam;
			//Now check Game Object click events
			botNET::MouseActionEventArgs* action = new botNET::MouseActionEventArgs((MouseEventType)Message, x, y);
			botNET::Game::RaiseMouseClickEvent(action);
			if(!action->PassClick)
				passback = false;

		}
		catch(Exception * ex)
		{
			if(botNET::Settings::Debugging::gPrintExceptions)
				botNET::Game::Print(ex->Message);
		}
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		try
		{
			botNET::KeyPressEventArgs * clargs = new botNET::KeyPressEventArgs((KeyPressEventType)Message, wParam, lParam);
			botNET::Game::RaiseKeyPressEvent(clargs);
			if(!clargs->PassKey)
				passback = false;
		}
		catch(Exception * ex)
		{
			if(botNET::Settings::Debugging::gPrintExceptions)
				botNET::Game::Print(ex->Message);
		}
		break;

	case WM_ACTIVATEAPP:
		passback = !(Message == WM_ACTIVATEAPP && wParam == 0 && !Settings::gAutoMinimize);
		break;


	}

/*
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109

*/
	if(passback)
		return STORM::GlobalMessageHandler(hwnd, Message, wParam, lParam, NotDef, retVal);
	else
		return false;
		//return passback ? STORM::GlobalMessageHandler(hwnd, Message, wParam, lParam, NotDef, retVal) : false;


}//FUNC_END



}//Patches
}//Imports
}//botNET

