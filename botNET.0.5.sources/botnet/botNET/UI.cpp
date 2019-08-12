#include "UI.h"
#include "Game.h"

namespace botNET 
{
	#define MAX_UI 0x26 // Maximum GetUIState + 1, defined in D2client\UI\ui.cpp

	__value	public enum	UIMode
	{
		Enable,
		Disable,
		Toggle
	};

	__gc public class MenuItem
	{
	public:
		MenuItem(String * text, UInt32 id, UInt32 color, UInt32 font, int mIndex, bool selectable)
		{
			this->Text = text;
			this->ID = id;
			this->Color = color;
			this->Font = font;
			this->Index = mIndex;
			this->Selectable = selectable;			
		}

		String * Text;
		UInt32 ID;
		UInt32 Color;
		UInt32 Font;
		int Index;
		bool Selectable;
	};

	bool coreClickUIScreen(int MenuItem)
	{
		if (*D2CLIENT::NpcMenu != 0x00000000 && (D2CLIENT::GetUIState(UIState::NPCMenuPanel) ||  D2CLIENT::GetUIState(UIState::PlayerTradeRequest)))
		{
			HWND d2handle=D2GFX::GetWindowHandle();
			D2MSG MouseXY;
			d2_NpcMenu *NpcMenu;
	
			NpcMenu=&(**D2CLIENT::NpcMenu);
	
			MouseXY.pt.X=(WORD)NpcMenu->X +32;
			MouseXY.pt.Y=(WORD)NpcMenu->Y +15 +15*(WORD)MenuItem;
			NpcMenu->clicked=1;
			NpcMenu->MenuId1=MenuItem;
			NpcMenu->MenuId2=MenuItem;

			D2CLIENT::ClickNpcMenuUI((DWORD)d2handle,(DWORD)0x6FFEA1C4,(DWORD)&MouseXY);
			return true;
		}
		return false;
	}

	/////////////////////////////////////////////////////////////////////
	// Method: GetState
	/////////////////////////////////////////////////////////////////////
	bool UI::GetState(UIState State)
	{
		if((int)State >= 0 && (int)State < MAX_UI)
			return D2CLIENT::GetUIState((int)State) > 0;

		throw new ArgumentException("UI.GetState -> Invalid state value passed.");
	}

	MenuItem * UI::GetMenuItems(void)[]
	{
		//PresetUnit * pres __gc[] = new PresetUnit * [presets->Count];

		UInt32 sdgdsjkfgksdfgM = (DWORD)(*D2CLIENT::NpcMenu);

		if (*D2CLIENT::NpcMenu != 0x00000000 && (D2CLIENT::GetUIState(8) ||  D2CLIENT::GetUIState(23)))
		{
			d2_NpcMenu *NpcMenu;

			NpcMenu=&(**D2CLIENT::NpcMenu);

			MenuItem * retMenus __gc[] = new MenuItem * __gc[NpcMenu->NumMenuLines];

			for(UInt32 i = 0; i < NpcMenu->NumMenuLines; i++)
			{
				retMenus[i] = new MenuItem(
						String::Copy(NpcMenu->menuText[i].text),
						NpcMenu->menuText[i].ID,
						NpcMenu->menuText[i].fontColor,
						NpcMenu->menuText[i].fontType,
						i,
						(i == 0 ? false : true)
					);

				/*
					String * s = String::Format("I see a line: \"{0}\" with proposed ID: {1} Color: {2} Font: ",
					String::Copy(NpcMenu->menuText[i].text),
					__box(NpcMenu->menuText[i]._13)->ToString(),
					__box(NpcMenu->menuText[i].fontColor)->ToString());					

					botNET::Game::Print(String::Concat(s,__box(NpcMenu->menuText[i].fontType)->ToString()));
				*/
			
			}

			return retMenus;
			//return String::Copy(NpcMenu->menuText[tLine].text);
		}

		throw new ApplicationException("NPC menu is not active.");
	}

	/////////////////////////////////////////////////////////////////////
	// Method: GetState
	/////////////////////////////////////////////////////////////////////
	bool UI::GetState(int State)
	{
		if(State >= 0 && State < MAX_UI)
			return D2CLIENT::GetUIState(State) > 0;

		throw new ArgumentException("UI.GetState -> Invalid state value passed.");
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SetState
	/////////////////////////////////////////////////////////////////////
	void UI::SetState(UIState State, UIMode Mode)
	{
		if((int)State < 0 || (int)State >= MAX_UI)
			throw new ApplicationException("UI.SetState -> Invalid state value passed.");

		D2CLIENT::ManipUI(State, Mode, 0);
	}

		/////////////////////////////////////////////////////////////////////
	// Method: SetState
	/////////////////////////////////////////////////////////////////////
	void UI::SetState(int State, UIMode Mode)
	{
		if(State < 0 || State >= MAX_UI)
			throw new ApplicationException("UI.SetState -> Invalid state value passed.");

		D2CLIENT::ManipUI(State, Mode, 0);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SetState
	/////////////////////////////////////////////////////////////////////
	void UI::SetState(UIState State, UIMode Mode, UInt32 _1)
	{
		if((int)State < 0 || (int)State >= MAX_UI)
			throw new ApplicationException("UI.SetState -> Invalid state value passed.");

		D2CLIENT::ManipUI(State, Mode, _1);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: SetState
	/////////////////////////////////////////////////////////////////////
	void UI::SetState(int State, UIMode Mode, UInt32 _1)
	{
		if(State < 0 || State >= MAX_UI)
			throw new ApplicationException("UI.SetState -> Invalid state value passed.");

		D2CLIENT::ManipUI(State, Mode, _1);
	}

	/////////////////////////////////////////////////////////////////////
	// Method: ClickUIScreen
	/////////////////////////////////////////////////////////////////////
	void UI::ClickUIScreen(int MenuItem)
	{
		if(!coreClickUIScreen(MenuItem))
			throw new ApplicationException("Menu was not ready to be clicked");
	}

	bool UI::ClickMenu( MainMenu MenuEntry )
	{
		if( !D2CLIENT::GetUIState( (int)UIState::NPCMenuPanel ) )
			return false;

		if( MenuEntry == MainMenu::Cancel )
		{
			UI::Cancel();
			return true;
		}

		int current = reinterpret_cast<int>( D2CLIENT::NpcMainMenuFunctionTable );
		for( int i = 0; i < *D2CLIENT::NpcMainMenuTableCount; i++ )
		{			
			current += 0x27;
			int npcid = *reinterpret_cast<int*>( current );
			if( npcid == *D2CLIENT::InteractedNPCClassID )
			{
				for(int c = 0; c < *reinterpret_cast<int*>( current+4 ); c++ )
				{
					if( *reinterpret_cast<short*>( current+8+2*c ) == MenuEntry )
					{
						ClickUIScreen( c+1 );
						return true;
					}
				}

				return false;
			}
		}

		return false;
	}

	/////////////////////////////////////////////////////////////////////
	// Method: Cancel
	//
	// Clicks the Cancel option on an active menu / Sends an "esc" key to the D2 Client otherwise
	/////////////////////////////////////////////////////////////////////
	void UI::Cancel()
	{
		//if(Game::IsInGame)
			//coreCancel();
		//else

		// TODO: It's possible to call this "in-between" menus, eg after resurrecting merc the NPC menu
		// disappears briefly. If you call Cancel during this time, the game enters a limbo state where
		// nothing works.

		//do we have a menu?
		if (*D2CLIENT::NpcMenu != 0x00000000 && (D2CLIENT::GetUIState(UIState::NPCMenuPanel) ||  D2CLIENT::GetUIState(UIState::PlayerTradeRequest)))
		{ // click it's cancel button
			coreClickUIScreen(GetMenuItems()->Length-1);
		}
		else
		{ // else hit escape (yuck)
			STORM::GlobalMessageHandler(D2GFX::GetWindowHandle(), 256, (WPARAM)27, (LPARAM)0x10001, 0, 0);
		}
	}

	/////////////////////////////////////////////////////////////////////
	// Method: GetStates
	/////////////////////////////////////////////////////////////////////
	UIState UI::GetStates(bool Active)[]
	{
		System::Collections::ArrayList * States = new ArrayList();

		for(int n = 0; n < MAX_UI; n++)
		{
			if(UI::GetState(n) == Active) States->Add(__box((UIState)n));
		}

		return __try_cast<UIState[]>(States->ToArray(__typeof(UIState)));
	}

}