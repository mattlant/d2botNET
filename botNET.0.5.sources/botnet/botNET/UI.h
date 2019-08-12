#ifndef UI_H
#define UI_H

#include "botnet.h"

#include "d2gfx.h"
#include "d2client.h"
#include "storm.h"

namespace botNET 
{

	static bool coreClickUIScreen(int MenuItem);

	__gc public class MenuItem;

	__value	public enum	UIMode;

	__gc public class UI
	{
	public:

		static MenuItem * UI::GetMenuItems(void)[];

		///<summary>
		/// Returns true if the specified UIState is active, false otherwise.
		/// Throws an ArguementException if an invalid UI State is specified
		///</summary>
		///<param name="State"> The UI State to check for. </param>
		static bool UI::GetState(UIState State);
		
		///<summary>
		/// Returns true if the specified (int)UIState is active, false otherwise.
		/// Throws an ArguementException if an invalid UI State is specified
		///</summary>
		///<param name="State"> The UI State to check for. </param>
		static bool UI::GetState(int State);

		///<summary>
		/// Returns an array of all UI States that are either active (Active = true) or innactive (Active = false)
		///</summary>
		///<param name="Active"> True to return all active UI States, false to return all inactive UI States. </param>
		static UIState UI::GetStates(bool Active)[];

		///<summary>
		/// Enables / disables the specified UIState.
		///</summary>
		///<param name="State"> The UI State to enable/disable. </param>
		///<param name="Mode"> The mode to set. </param>
		static void UI::SetState(UIState State, UIMode Mode);

		///<summary>
		/// Enables / disables the specified UIState.
		///</summary>
		///<param name="State"> The UI State to enable/disable. </param>
		///<param name="Mode"> The mode to set. </param>
		static void UI::SetState(int State, UIMode Mode);

		///<summary>
		/// Enables / disables the specified UIState.
		///</summary>
		///<param name="State"> The UI State to enable/disable. </param>
		///<param name="Mode"> The mode to set. </param>
		///<param name="_1"> Unknown third parameter (assumed 0.) </param>
		static void UI::SetState(UIState State, UIMode Mode, UInt32 _1);

		///<summary>
		/// Enables / disables the specified UIState.
		///</summary>
		///<param name="State"> The UI State to enable/disable. </param>
		///<param name="Mode"> The mode to set. </param>
		///<param name="_1"> Unknown third parameter (assumed 0.) </param>
		static void UI::SetState(int State, UIMode Mode, UInt32 _1);

		///<summary>
		/// Clicks an NPC's menu.
		///</summary>
		///<param name="MenuItem"> The index of the menu choice to choose. </param>
		static void UI::ClickUIScreen(int MenuItem);

		///<summary>
		/// Clicks an NPC's menu.
		///</summary>
		///<param name="MenuEntry"> . </param>
		///<returns> True if success, false if failed. </returns>
		static bool UI::ClickMenu( MainMenu MenuEntry );

		///<summary>
		/// Cancels out of UI screens.
		///</summary>
		///<remarks> If an NPC menu is active, it will click the menu's cancel button.  Otherwise, it sends an escape keypress </remarks>
		static void UI::Cancel(void);

	};

}

#endif