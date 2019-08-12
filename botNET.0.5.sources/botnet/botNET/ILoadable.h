#ifndef ILOADABLE_H
#define ILOADABLE_H

using namespace System;

namespace botNET
{
	///<summary>
	/// Every bot, application or utility running under botNET has to implement this interface in order to be able to load. botNET uses member methods of this interface to communicate with module and "inform" it about ongoing events inside Diablo 2.
	///</summary>
	///<remarks> <b>CAUTION:</b> Be warned that some of these methods run on internal botNET threads, that means if you run some long running code inside of them, it will cause D2 to freeze. </remarks>
	__gc public __interface ILoadable : public IDisposable
	{
	public:
		///<summary>
		/// Called upon loading of module into botNET when module is autoloaded or user types <b>.load &lt;assembly&gt;</b>.
		///</summary>
		///<param name="ID"> The identification number of current module assigned by core during loading. </param>
		///<remarks> First function called upon loading of our assembly. This is good place to put up some configuration loading routines.<br><br>
		/// This method is run on separate thread which is tracked by core itself. This thread exists all the time inside botNET until module gets unloaded. </remarks>
		void Load();

		///<summary>
		/// Called upon unloading of module from botNET when game is closed or user types <b>.unload &lt;assembly&gt;</b>.
		///</summary>
		///<remarks> Any cleanup should be performed in this method.<br><br>
		/// <b>CAUTION:</b> This method is runs on internal core thread. </remarks>
		void Dispose();

		///<summary>
		/// Called at the beginning of every game.
		///</summary>
		///<remarks> Called at the beginning of every game. If you want to add some event handlers like Game.OnPacketReceiveEvent this is the place to do so. <br><br>
		/// This method is run on separate thread which is tracked by core itself. This thread exists all time until game exits. </remarks>
		void NewGame();

		///<summary>
		/// Called at the end of every game.
		///</summary>
		///<remarks> If you registered any event handlers like Game.OnPacketReceiveEvent this is the place to unregister them. <br><br>
		/// <b>CAUTION:</b> Runs on internal botNET thread, so if you want to do some long running actions in here like handle OOG stuff run them on a new thread. </remarks>
		void EndGame(TimeSpan GameLength);

		///<summary>
		/// Called when user types <b>.&lt;thisassemblyname&gt; &lt;command&gt; [arg1 [arg2 [...]]].</b>
		///</summary>
		///<param name="Command"> The command sent. </param>
		///<param name="Args"> Command arguments array. </param>
		///<remarks> <b>CAUTION:</b> This method is runs on internal core thread. </remarks>
		void UserCommand(String * Command, String * Args[]);

		///<summary>
		/// Handler for internal botNET messages sent from another assemblies.
		///</summary>
		///<param name="SenderID"> ID of assembly that sent message. </param>
		///<param name="MessageType"> Type of message sent. </param>
		///<param name="Data"> Additional data. </param>
		///<remarks> Remember that message sent could contain any data within Data parameter, so you should double check if they are correct before using them.<br><br>
		/// <b>CAUTION:</b> This method is runs on internal core thread. </remarks>
		void ReceiveMessage(Int64 SenderID, Int32 MessageType, Object * Data);
	};
}

#endif