// HelloDiablo for botNET 0.5

using System; 
using botNET; 

namespace HelloDiablo { 

	[LoadableAttribute] 
	public class HelloBot : ILoadable
	{ 

		// Triggered when the a new game starts
		public void NewGame() { 
			Game.Print("Hello Diablo!"); 
		} 

		#region Other required interface elements

		public void EndGame(TimeSpan GameLength) { 
		} 

		public void UserCommand(string command, string[] args) { 
		} 

		public void Load() { 
		} 

		public void Dispose() { 
		} 

		public void ReceiveMessage(long SenderID, int MessageType, object Data) 
		{ 
		} 

		#endregion
	} 
} 
