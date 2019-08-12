#ifndef GAME_H
#define GAME_H

#include "definitions.h"

namespace botNET 
{

	__gc public class Game
	{
	public:

		__gc class Window
		{
		public:

			///<summary>
			/// Gets an IntPtr representing the Diablo II window handle.
			///</summary>
			__property static IntPtr get_Handle();

			///<summary>
			/// Gets or Sets the name of the Diablo II window.
			///</summary>
			__property static String * get_Title();

			///<summary>
			/// Gets or Sets the name of the Diablo II window.
			///</summary>
			__property static void set_Title(String * NewName);

			///<summary>
			/// Returns a value indicating wether or not the window is minimized.
			///</summary>
			///<returns> Returns a value indicating wether or not the window is minimized. </returns>
			static bool IsMinimized(void);

			///<summary>
			/// Restores the DIablo II window
			///</summary>
			static void Show(void);

			///<summary>
			/// Minimizes
			///</summary>
			static void Minimize(void);

			__property static UInt32 get_XOffset();
			__property static UInt32 get_YOffset();

		};

			static void Crash();
			static void Crash(bool unhandled);

		///<summary>
		/// Gets an IntPtr of the Diablo II window handle
		///</summary>
		static IntPtr GetWindowHandle();



		///<summary>
		/// Gets the cursors mode
		///</summary>
		__property static CursorMode get_CursorMode();


		///<summary>
		/// Prints a message to the screen.
		///</summary>
		///<param name="msg"> The message to print. </param>
		static void Print(String * msg);

		///<summary>
		/// Prints a message to the screen.
		///</summary>
		///<param name="msg"> The message to print. </param>
		///<param name="type"> using type 7 will print to a scroll on the screen. </param>
		static void Print(String * msg, int type);

		///<summary>
		/// Prints a message to the screen.
		///</summary>
		///<param name="msgs"> A string Array of messages to print. </param>
		static void Print([ParamArray] String * msgs[]);

		static void Print(String* format, [ParamArray] Object* args[]);

		///<summary>
		/// Prints a message to the screen.
		///</summary>
		///<param name="ExceptionToPrint"> An exception to print to the screen. </param>
		///<remarks> This method will print the Exception's Message and StackTrace. </remarks>
		static void Print(Exception * ExceptionToPrint);

		///<summary>
		/// Prints an integer to the screen.
		///</summary>
		///<param name="I"> The integer to print. </param>
		static void Print(int I);

		///<summary>
		/// Prints a message to the game which goes as a normal message.
		///</summary>
		///<param name="msg"> The message to print. </param>
		static void PrintToBnet(String * msg);

		///<summary>
		/// Will wait for a user to type a message in the chat box and return the message.
		///</summary>
		///<returns> A string representing the message the user entered</returns>
		///<remarks> Only works in-game at this time. By default the typed message will not pass through to the game. </remarks>
		static String * ReadLine(void);

		///<summary>
		/// Will wait for a user to type a message in the chat box and return the message.
		///</summary>
		///<param name="PassThrough"> Set to true to have the typed message also pass through to the game. </param>
		///<returns> A string representing the message the user entered</returns>
		///<remarks> Only works in-game at this time. By default the typed message will not pass through to the game. </remarks>
		static String * ReadLine(bool PassThrough);

		///<summary>
		/// Will read a value form an ini file.
		///</summary>
		///<param name="File"> The name of the file to read from. </param>
		///<param name="Section"> The name of the section to read from. </param>
		///<param name="Key"> The name of the key value to read. </param>
		///<returns> A string representing requested Key value. </returns>
		static String * IniReadValue(String * File, String * Section, String * Key);

		///<summary>
		/// Will write a value to an ini file.
		///</summary>
		///<param name="File"> The name of the file to write to. </param>
		///<param name="Section"> The name of the section to write. </param>
		///<param name="Key"> The name of the key value to write. </param>
		///<param name="Value"> The value to write. </param>
		static void IniWriteValue(String * File, String * Section, String * Key, String * Value);

		static void ScreenDrawText(String * text, int Xloc, int Yloc, int Color, int Font, int Alignment);
		static void ScreenDrawRectangle(int Xloc, int Yloc, int Width, int Height, int Color, int Transparency);

		///<summary>
		/// Quits the current game.
		///</summary>
		static void Quit(void);

		///<summary>
		/// Completely exits Diablo II.
		///</summary>
		static void Exit(void);

		///<summary>
		/// Completely exits Diablo II.
		///</summary>
		///<param name="flags"> Unknown. </param>
		static void Exit(int flags);

		///<summary>
		/// Sends a Packet to battlenet's chat server.
		///</summary>
		static void SendPacketToChatServer(Byte buf[]);

		///<summary>
		/// Sends a Packet to the game server.
		///</summary>
		static void SendPacketToServer(Byte buf[]);

		///<summary>
		/// Sends a Packet to the game.
		///</summary>
		static void SendPacketToGame(Byte buf[]);

		///<summary>
		/// Sends a Key Press to the game.
		///</summary>
		///<param name="KeyCode1"> The key code to send. </param>
		///<param name="KeyCode2"> The extended info to send, or LPARAMs. </param>
		static void SendKey(UInt32 WParam, UInt32 LParam);

		///<summary>
		/// Sends a mouse click to the game.
		///</summary>
		///<param name="x"> the X coordinate to click. </param>
		///<param name="y"> the X coordinate to click. </param>
		///<param name="clicktype"> The ClickType enumeration value. </param>
		static void SendMouseClick(int x, int y, ClickType clicktype);

		///<summary>
		/// Will repair all your items.
		///</summary>
		//static void PlayInGameSound(void);

		///<summary>
		/// Converts Coords.
		///</summary>
		static System::Drawing::Point ScreenToMap(System::Drawing::Point coord);


		__property static System::Drawing::Point get_MouseLocation();
		__property static System::Drawing::Point get_MouseMapLocation();



		static bool			gIsInGame;
		static DateTime		gGameStartTime;
        
		__property static bool get_IsInGame(void);

		///<summary>
		/// Gets the ping of the current game.
		///</summary>
		__property static UInt32 get_Ping(void);

		///<summary>
		/// Gets the name of the current game.
		///</summary>
		__property static String * get_GameName(void);

		///<summary>
		/// Gets the game server's IP address.
		///</summary>
		__property static String * get_GameIP(void);

		///<summary>
		/// Gets the account name currently logged in.
		///</summary>
		__property static String * get_AccountName(void);

		///<summary>
		/// Gets the current players name.
		///</summary>
		__property static String * get_PlayerName(void);

		///<summary>
		/// Gets the current realm.
		///</summary>
		///<returns> </returns>
		__property static String * get_Realm(void);

		///<summary>
		/// Gets the current sub realm if applicable.
		///</summary>
		__property static String * get_SubRealm(void);

		///<summary>
		/// Gets the current game's password.
		///</summary>
		__property static String * get_GamePassword(void);

		///<summary>
		/// Gets the surrent games description.
		///</summary>
		///<returns> </returns>
		__property static String * get_GameDescription(void);

		///<summary>
		/// Gets the current DifficultyType.
		///</summary>
		__property static DifficultyType get_Difficulty(void);

		///<summary>
		/// Gets the current GameType.
		///</summary>
		__property static int get_GameType(void);

		///<summary>
		/// Gets the maximum difficulty the current character can play.
		///</summary>
		__property static DifficultyType get_MaxDifficulty(void);

		///<summary>
		/// Gets a value indicating if the character is a hard core character
		///</summary>
		__property static bool get_IsHardCore(void);

		///<summary>
		/// Gets a value indicating if the character is a hard core character
		///</summary>
		__property static bool get_IsPaused(void);

		///<summary>
		/// Gets the game's status... ?
		///</summary>
		///<returns> </returns>
		__property static bool get_GameStatus(void);

		///<summary>
		/// Queries the .NET Garbage Collector for current memory usage.
		///</summary>
		///<returns> </returns>
		__property static Int64 get_MemoryUsage();

		static void InGameCheck();

		//Static Event Handler stuff
		__event static OnDrawHandler * OnDrawBegin;
		__event static OnDrawHandler * OnDrawEnd;
		__event static OnBeginGameHandler * OnBeginGame;
		__event static OnEndGameHandler * OnEndGame;
		__event static OnChatLineHandler * OnChatLine;
		__event static OnKeyPressHandler * OnKeyPress;
		__event static OnMouseActionHandler * OnMouseClick;

	public private:

		static System::Windows::Forms::NotifyIcon * TrayIcon;
		static Int64 memusage;
		static UnitPlayer * meunit;
		static UInt32 lastrightclickitem;
		//static Byte waypoints[] = new Byte[5];


		static void RaiseDrawBeginEvent();
		static void RaiseDrawEndEvent();
		static void RaiseBeginGameEvent(GameEventArgs * e);
		static void RaiseEndGameEvent(GameEventArgs * e);
		static void RaiseChatLineEvent(ChatLineMessageEventArgs * e);
		static void RaiseKeyPressEvent(KeyPressEventArgs * e);
		static void RaiseMouseClickEvent(MouseActionEventArgs * e);


	};


}

#endif