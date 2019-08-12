#include "botnet.h"
#include "game.h"

#include "Heap.h"
#include "rosterplayer.h"
#include "party.h"
#include "EventArgs.h"
#include "readlineobject.h"
#include "pc.h"
#include "gameobject.h"
#include "item.h"
#include "items.h"
#include "d2exports.h"
#include "d2gfx.h"
#include "d2win.h"
#include "d2client.h"
#include "d2common.h"
#include "d2launch.h"
#include "d2multi.h"
#include "d2net.h"
#include "settings.h"
#include "storm.h"
#include <vcclr.h>


CRITICAL_SECTION PrintBufferCritSect;

namespace botNET
{
		
	void Game::Crash()
	{
		D2CLIENT::ManipUI(99999, 99999, 99999);
	}
		
	void Game::Crash(bool unhandled)
	{
		D2CLIENT::ClickNpcMenuUI(45, 566, 6743);
	}

	bool Game::get_IsInGame()
	{
		return gIsInGame;
	}

		

	/////////////////////////////////////////////////////////////////////
	// Method: Quit
	/////////////////////////////////////////////////////////////////////
	void Game::Quit()
	{ D2CLIENT::QuitGame(); } // quits game

	/////////////////////////////////////////////////////////////////////
	// Method: Exit
	/////////////////////////////////////////////////////////////////////
	void Game::Exit()
	{ D2CLIENT::ExitGame(0); } // No argument given: defulat of zero

	/////////////////////////////////////////////////////////////////////
	// Method: Exit
	/////////////////////////////////////////////////////////////////////
	void Game::Exit(int flags)
	{ D2CLIENT::ExitGame((DWORD)flags); } // if an argument is supplied take it=P

	botNET::CursorMode Game::get_CursorMode()
	{
		switch(*D2CLIENT::CursorMode)
		{
			case 1:
				return (botNET::CursorMode)0;
			case 3:
			case 4:
				return (botNET::CursorMode)1;
			case 6:
				return (botNET::CursorMode)2;

			case 7:
				switch(*D2CLIENT::ShopCursorMode)
				{
					case 1:
						return (botNET::CursorMode)3;
					case 3:
					case 4:
						return (botNET::CursorMode)((*D2CLIENT::ShopCursorMode) + 1);
					case 0x100:
						return (botNET::CursorMode)0;
					default:
						return (botNET::CursorMode)6;
				}

			default:
				return (botNET::CursorMode)6;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Print
	/////////////////////////////////////////////////////////////////////
	void Game::Print(String * message)
	{
		if (!message || message->Length == 0)
			return;

		if(Game::gIsInGame)
		{

			if(D2MULTI::ChatOutputTextBox)
				if(*D2MULTI::ChatOutputTextBox)
					return;

			//Cast it into an unmanaged C++ type

			message = String::Concat("ÿc0", message);
			//wchar_t __nogc* pStr = static_cast<wchar_t*>(Marshal::StringToHGlobalUni(message).ToPointer());
			wchar_t __pin* pStr = PtrToStringChars(message);

			D2CLIENT::PrintScreenMessage(pStr, 0);
			
			//Marshal::FreeHGlobal(pStr);
		}
		else
		{
			ButtonAttrib * out;

			if(D2MULTI::ChatOutputTextBox)
				if(*D2MULTI::ChatOutputTextBox)
					out = *D2MULTI::ChatOutputTextBox;
			if(out)
			{
				if(!out) return;
				//wchar_t __nogc* pStr = static_cast<wchar_t*>(Marshal::StringToHGlobalUni(message).ToPointer());
				wchar_t __pin* pStr = PtrToStringChars(message);
				D2WIN::TextBoxPrint(out, pStr, 0, 0, 1);
				//Marshal::FreeHGlobal(pStr);
			}
		}

	}

	/////////////////////////////////////////////////////////////////////
	// Method: Print
	/////////////////////////////////////////////////////////////////////
	//TODO: Fix void Game::Print(String * msg, int type)
	
	void Game::Print(String * msg, int type) //TODO: Fix void Game::Print(String * msg, int type)
	{
		Game::Print("I do nothing currently");
		return;

		if (!msg)
			return;

		//Get the player Unit
		//Cast it into an unmanaged C++ type
		char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(msg).ToPointer());
		//OnScreenPrint(pStr, "", 0, type, 0x02);
		Marshal::FreeHGlobal(pStr);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Print
	/////////////////////////////////////////////////////////////////////
	void Game::Print([ParamArray] String * msgs[])
	{
		if(!msgs)
			return;

		for(int i = 0; i < msgs->Length; i++)
			Game::Print(msgs[i]);
	}

	void Game::Print(String* format, [ParamArray] Object* args[])
	{
		Game::Print(String::Format(format, args));
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Print
	/////////////////////////////////////////////////////////////////////
	void Game::Print(Exception * ex)
	{
		if (!ex)
			return;

		__wchar_t d __gc[] = { 10, 13};

		String * stacktrace __gc[] = ex->StackTrace->Split(d);
		String * message __gc[] = ex->Message->Split(d);

		Game::Print(message);
		Game::Print(stacktrace);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Print
	/////////////////////////////////////////////////////////////////////
	void Game::Print(int I)
	{
		Game::Print(I.ToString());
	}

	/////////////////////////////////////////////////////////////////////
	// Method: PrintToBnet
	/////////////////////////////////////////////////////////////////////
	void Game::PrintToBnet(String * msg)
	{
		Game::Print("PrintToBnet not working at this time");
		return;

		if (!msg) 
			return;

		//Cast it into an unmanaged C++ type
//		wchar_t __nogc* pStr = static_cast<wchar_t*>(Marshal::StringToHGlobalUni(msg).ToPointer());
		wchar_t __pin* pStr = PtrToStringChars(msg);

		wchar_t * lastmessage = D2CLIENT::LastChatMessage;
		HWND d2handle = D2GFX::GetWindowHandle();
		if(*D2CLIENT::MessageTimer <= 0)
		{
			D2CLIENT::ManipUI(5, UI_ON, 0);
			*D2CLIENT::MessageTimer = 1;
		}
		//StrCpyW(pStr, lastmessage);
		SendMessage(d2handle, WM_CHAR, 0x0D, 0x1C0001);
		D2CLIENT::ManipUI(5, UI_OFF, 0);
		*D2CLIENT::MessageTimer = 0;

//		Marshal::FreeHGlobal(pStr);

	}

	/////////////////////////////////////////////////////////////////////
	// Method: Readline
	/////////////////////////////////////////////////////////////////////
	String * Game::ReadLine()
	{
		return Game::ReadLine(false);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: IniReadValue
	/////////////////////////////////////////////////////////////////////
	String * Game::IniReadValue(String * File, String * Section, String * Key)
	{
		String * Temp = S"";
		char __nogc* file = static_cast<char*>(Marshal::StringToHGlobalAnsi(File).ToPointer());
		char __nogc* section = static_cast<char*>(Marshal::StringToHGlobalAnsi(Section).ToPointer());
		char __nogc* key = static_cast<char*>(Marshal::StringToHGlobalAnsi(Key).ToPointer());
		char __nogc* temp = static_cast<char*>(Marshal::StringToHGlobalAnsi(Temp).ToPointer());
		GetPrivateProfileString(section, key, "", temp, 255, file);
		Temp = Convert::ToString(temp);
		Marshal::FreeHGlobal(file);
		Marshal::FreeHGlobal(section);
		Marshal::FreeHGlobal(key);
		Marshal::FreeHGlobal(temp);
		return Temp;
	}

	/////////////////////////////////////////////////////////////////////
	// Method: IniWriteValue
	/////////////////////////////////////////////////////////////////////
	void Game::IniWriteValue(String * File, String * Section, String * Key, String * Value)
	{
		char __nogc* file = static_cast<char*>(Marshal::StringToHGlobalAnsi(File).ToPointer());
		char __nogc* section = static_cast<char*>(Marshal::StringToHGlobalAnsi(Section).ToPointer());
		char __nogc* key = static_cast<char*>(Marshal::StringToHGlobalAnsi(Key).ToPointer());
		char __nogc* value = static_cast<char*>(Marshal::StringToHGlobalAnsi(Value).ToPointer());
		WritePrivateProfileString(section, key, value, file);
		Marshal::FreeHGlobal(file);
		Marshal::FreeHGlobal(section);
		Marshal::FreeHGlobal(key);
		Marshal::FreeHGlobal(value);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Readline
	/////////////////////////////////////////////////////////////////////
	String * Game::ReadLine(bool PassThrough)
	{
		ReadLineObject * ro = new ReadLineObject(PassThrough);

		botNET::Game::OnChatLine += new botNET::OnChatLineHandler(ro, &ReadLineObject::EventHandle);

		while(ro->Message == S"")
		{
			Thread::Sleep(33);
		}

		botNET::Game::OnChatLine -= new botNET::OnChatLineHandler(ro, &ReadLineObject::EventHandle);
		return ro->Message;
	}

	/////////////////////////////////////////////////////////////////////
	// Method: ScreenDrawText
	/////////////////////////////////////////////////////////////////////
	void Game::ScreenDrawText(String * Text, int Xloc, int Yloc, int Color, int Font, int Alignment)
	{
		//Cast it into an unmanaged C++ type
		//wchar_t __nogc* pStr = static_cast<wchar_t*>(Marshal::StringToHGlobalUni(Text).ToPointer());
		//D2WIN::DrawTextHook(pStr, Xloc, Yloc, Color, 0);
		//Marshal::FreeHGlobal(pStr);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: ScreenDrawRectangle
	/////////////////////////////////////////////////////////////////////
	void Game::ScreenDrawRectangle(int Xloc, int Yloc, int Width, int Height, int Color, int Transparency)
	{
		D2GFX::DrawRectangle(Xloc, Yloc, (Xloc + Width), (Yloc + Height), Color, Transparency);
	}

	//TODO: Fix/Remove void Game::SoundPlay(String * msg, unsigned int Flags) {
	/*
	void Game::SoundPlay(String * msg, unsigned int Flags) {
	//Cast it into an unmanaged C++ type
	wchar_t __nogc* pStr = static_cast<char*>(Marshal::StringToCoTaskMemUni(msg).ToPointer());
	PlaySound(pStr, NULL, Flags);
	Marshal::FreeHGlobal(pStr);
	}
	*/

	/////////////////////////////////////////////////////////////////////
	// Method: SendPacketToChatServer
	/////////////////////////////////////////////////////////////////////
	void Game::SendPacketToChatServer(Byte buf[])
	{
		IntPtr packetbuffer = Marshal::AllocHGlobal(buf->Length);
		Marshal::Copy(buf, 0, packetbuffer, buf->Length);
		//GameSendPacketToChatServer((LPBYTE)packetbuffer.ToPointer(), buf->Length);
		Marshal::FreeHGlobal(packetbuffer);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SendPacketToServer
	/////////////////////////////////////////////////////////////////////
	void Game::SendPacketToServer(Byte buf[]) //TODO: Fix void Game::SendPacketToServer(Byte buf[])
	{
		IntPtr packetbuffer = Marshal::AllocHGlobal(buf->Length);
		Marshal::Copy(buf, 0, packetbuffer, buf->Length);
		D2NET::GameSend (0, (LPBYTE)packetbuffer.ToPointer(), buf->Length);
		Marshal::FreeHGlobal(packetbuffer);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SendPacketToGame
	/////////////////////////////////////////////////////////////////////
	void Game::SendPacketToGame(Byte buf[]) //TODO: Fix void Game::SendPacketToGame(Byte buf[])
	{
		Game::Print("I do nothing currently");
		return;

		IntPtr packetbuffer = Marshal::AllocHGlobal(buf->Length);
		Marshal::Copy(buf, 0, packetbuffer, buf->Length);
		//GameSendPacketToGame((LPBYTE)packetbuffer.ToPointer(), buf->Length);
		Marshal::FreeHGlobal(packetbuffer);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SendKey
	/////////////////////////////////////////////////////////////////////
	void Game::SendKey(UInt32 WParam, UInt32 LParam)
	{
		STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), 256, (WPARAM)WParam, (LPARAM)LParam, 0, 0);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SendMouseClick
	/////////////////////////////////////////////////////////////////////
	void Game::SendMouseClick(int x, int y, ClickType clicktype)
	{
		DWORD xpos = x;
		DWORD ypos = y;
		LPARAM lp = x + (y << 16);
		switch(clicktype)
		{
		case ClickType::LeftDown:
			STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), WM_LBUTTONDOWN, 0, lp, 0, 0);
			break;
		case ClickType::LeftUp:
			STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), WM_LBUTTONUP, 0, lp, 0, 0);
			break;
		case ClickType::RightDown:
			STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), WM_RBUTTONDOWN, 0, lp, 0, 0);
			break;
		case ClickType::RightUp:
			STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), WM_RBUTTONUP, 0, lp, 0, 0);
			break;
		}
	}

	/////////////////////////////////////////////////////////////////////
	// property: GameStatus
	//
	// read-only returns game status
	/////////////////////////////////////////////////////////////////////
	bool Game::get_GameStatus(){ return D2CLIENT::GetGameStatus(); } //Gets game status :O

	/////////////////////////////////////////////////////////////////////
	// property: Ping
	/////////////////////////////////////////////////////////////////////
	UInt32 Game::get_Ping(){ return *D2CLIENT::Ping; } 

	/////////////////////////////////////////////////////////////////////
	// property: GameName
	//
	// read-only returns the game's name
	/////////////////////////////////////////////////////////////////////
	String * Game::get_GameName()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.GameName;
	}

	/////////////////////////////////////////////////////////////////////
	// property: GameIP
	//
	// read-only returns the game's server IP address
	/////////////////////////////////////////////////////////////////////
	String * Game::get_GameIP()
	{
		int count = 0;
		int count2 = 0;
		char *gameip = new char[17];

		BnetData b = **D2LAUNCH::BNData;
		while(*(b.GameIp+count) == '\0')
			count++;
		while(b.GameIp[count] != '\0')
			gameip[count2++] = b.GameIp[count++];
		gameip[count2] = '\0';
		return Convert::ToString(gameip);
	}

	/////////////////////////////////////////////////////////////////////
	// property: AccountName
	//
	// read-only returns the current account name
	/////////////////////////////////////////////////////////////////////
	String * Game::get_AccountName()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.AccountName;
	}

	/////////////////////////////////////////////////////////////////////
	// property: PlayerName
	//
	// read-only returns the current player name
	/////////////////////////////////////////////////////////////////////
	String * Game::get_PlayerName()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.PlayerName;
	}

	/////////////////////////////////////////////////////////////////////
	// property: Realm
	//
	// read-only returns the current realm
	/////////////////////////////////////////////////////////////////////
	String * Game::get_Realm()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.RealmName;
	}

	/////////////////////////////////////////////////////////////////////
	// property: SubRealm
	//
	// read-only returns the current sub realm
	/////////////////////////////////////////////////////////////////////
	String * Game::get_SubRealm()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.RealmName2;
	}

	/////////////////////////////////////////////////////////////////////
	// property: GamePassword
	//
	// read-only returns the current game password
	/////////////////////////////////////////////////////////////////////
	String * Game::get_GamePassword()
	{
		BnetData b = **D2LAUNCH::BNData;
		return b.GamePass;
	}

	/////////////////////////////////////////////////////////////////////
	// property: GameDescription
	//
	// read-only returns the current game description
	/////////////////////////////////////////////////////////////////////
	String * Game::get_GameDescription()
	{
		//BnetData b = **D2LAUNCH::BNData;
		//return b.GameDesc;
		return (**D2LAUNCH::BNData).GameDesc;
	}


	/////////////////////////////////////////////////////////////////////
	// property: MemoryUsage
	/////////////////////////////////////////////////////////////////////
	Int64 Game::get_MemoryUsage()
	{
		return System::GC::GetTotalMemory(false);
	}

	/////////////////////////////////////////////////////////////////////
	// Property: Difficulty
	/////////////////////////////////////////////////////////////////////
	DifficultyType Game::get_Difficulty()
	{
		//TODO: DifficultyType is returned 0-1-2 from D2Client... The enum needs to be changed (its 1-2-3!)
		return (DifficultyType)(*D2CLIENT::Difficulty+1);
	}

	/////////////////////////////////////////////////////////////////////
	// Property: MaxDifficulty
	/////////////////////////////////////////////////////////////////////
	DifficultyType Game::get_MaxDifficulty()
	{
		BnetData BnData = **(D2LAUNCH::BNData);
		if((BnData.MaxDifficulty & 0x0E)==0x0E){ return (DifficultyType)3; }
		else if((BnData.MaxDifficulty & 0x0C)==0x0C){ return (DifficultyType)2; }
		else if((BnData.MaxDifficulty & 0x08)==0x08){ return (DifficultyType)1; }
		else { return (DifficultyType)0; }
	}

	/////////////////////////////////////////////////////////////////////
	// Property: GameType
	/////////////////////////////////////////////////////////////////////
	int Game::get_GameType()
	{
		return D2CLIENT::GetGameType();
	}

	/////////////////////////////////////////////////////////////////////
	// Property: IsHardCore
	/////////////////////////////////////////////////////////////////////
	bool Game::get_IsHardCore()
	{
		BnetData BnData = **(D2LAUNCH::BNData);
		if((BnData.CharFlags & 0x04)==0x04){ return true; }
		else { return false; }

	}

	/////////////////////////////////////////////////////////////////////
	// Property: IsPaused
	/////////////////////////////////////////////////////////////////////
	bool Game::get_IsPaused()
	{
		return *D2CLIENT::IsPaused;
	}

	System::Drawing::Point Game::get_MouseLocation()
	{
		return System::Drawing::Point(*D2CLIENT::MouseX, *D2CLIENT::MouseY);
	}

	System::Drawing::Point Game::get_MouseMapLocation()
	{
		return Game::ScreenToMap(Game::MouseLocation);
	}

	System::Drawing::Point Game::ScreenToMap(System::Drawing::Point coord)
	{
		long Xpos = coord.X + D2CLIENT::GetMouseXOffset();
		long Ypos = coord.Y + D2CLIENT::GetMouseYOffset();

		D2COMMON::AbsScreenToMapCoords(&Xpos, &Ypos);

		return System::Drawing::Point(Xpos, Ypos);
	}


	//OnDraw Event Handlers
	void Game::RaiseDrawBeginEvent()
	{
		try{
			OnDrawBegin(NULL, new EventArgs());
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a DrawBeginEvent: " , ex->Message));
		}
	}
	void Game::RaiseDrawEndEvent()
	{
		try{
			OnDrawEnd(NULL, new EventArgs());
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a DrawEndEvent: " , ex->Message));
		}
	}

	//Event Handler stuff
	void Game::RaiseBeginGameEvent(GameEventArgs * e)
	{
		try{
			OnBeginGame(NULL, e);
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a BeginGameEvent: " , ex->Message));
		}
	}

	//Event Handler stuff
	void Game::RaiseEndGameEvent(GameEventArgs * e)
	{
		try{
			OnEndGame(NULL, e);
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in an EndGameEvent: " , ex->Message));
		}
	}

	//Event Handler stuff
	void Game::RaiseChatLineEvent(ChatLineMessageEventArgs * e)
	{
		try{
			OnChatLine(NULL, e);
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a ChatLineEvent: " , ex->Message));
		}
	}

	//Event Handler stuff
	void Game::RaiseKeyPressEvent(botNET::KeyPressEventArgs * e)
	{
		try{
			//Game::Print(String::Concat(__box(e->Type)->ToString(), S": ", __box(e->LParam)->ToString()));
			OnKeyPress(NULL, e);
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a KeyPressEvent: " , ex->Message));
		}
	}

	//Event Handler stuff
	void Game::RaiseMouseClickEvent(MouseActionEventArgs * e)
	{
		try{
			//Game::Print(String::Concat(__box(e->Type)->ToString(), S" ", e->clickx.ToString(), 
			//	S", ", e->clicky.ToString()));
			OnMouseClick(NULL, e);
		}
		catch (Exception * ex){
			if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a MouseDownEvent: " , ex->Message));
		}
	}



	void Game::InGameCheck()
	{
		if(!Game::gIsInGame)
			throw new ApplicationException("Can be used in game only");
	}




	/////////////////////////////////////////////////////////////////////
	// Method: GetWindowHandle
	/////////////////////////////////////////////////////////////////////
	IntPtr Game::GetWindowHandle()
	{
		return IntPtr(D2GFX::GetWindowHandle());
	}

	/////////////////////////////////////////////////////////////////////
	// Method: get_Handle
	/////////////////////////////////////////////////////////////////////
	IntPtr Game::Window::get_Handle()
	{
		return IntPtr(D2GFX::GetWindowHandle());
	}

	/////////////////////////////////////////////////////////////////////
	// Method: get_Title
	/////////////////////////////////////////////////////////////////////
	String * Game::Window::get_Title()
	{
		return System::Diagnostics::Process::GetCurrentProcess()->MainWindowTitle;
	}

	/////////////////////////////////////////////////////////////////////
	// Method: set_Title
	/////////////////////////////////////////////////////////////////////
	void Game::Window::set_Title(String * NewName)
	{
		char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(NewName).ToPointer());
		SetWindowText(D2GFX::GetWindowHandle(), pStr);
		Marshal::FreeHGlobal(pStr);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: IsMinimized
	/////////////////////////////////////////////////////////////////////
	bool Game::Window::IsMinimized(void)
	{
		WINDOWPLACEMENT placement;
		GetWindowPlacement(D2GFX::GetWindowHandle(), &placement);
		return (placement.showCmd == 2);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Show
	/////////////////////////////////////////////////////////////////////
	void Game::Window::Show(void)
	{
		ShowWindow(D2GFX::GetWindowHandle(), 9);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Show
	/////////////////////////////////////////////////////////////////////
	void Game::Window::Minimize(void)
	{
		ShowWindow(D2GFX::GetWindowHandle(), SW_MINIMIZE);
	}

	/////////////////////////////////////////////////////////////////////
	// Property: XOffset
	/////////////////////////////////////////////////////////////////////
	UInt32 Game::Window::get_XOffset(void)
	{
		return *D2CLIENT::ScreenXOffset;
	}


	/////////////////////////////////////////////////////////////////////
	// Property: YOffset
	/////////////////////////////////////////////////////////////////////
	UInt32 Game::Window::get_YOffset(void)
	{
		return *D2CLIENT::ScreenYOffset;
	}




}