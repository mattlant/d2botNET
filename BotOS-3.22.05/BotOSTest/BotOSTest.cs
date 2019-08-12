// HelloDiablo for botNET 0.3.1

using System; 

using botNET;
using botNET.Collections;

using System.Threading;

using BotOS;
using BotOS.Movements;

namespace BotOSTest 
{ 

	[LoadableAttribute] 
	public class BotOSTest : ILoadable
	{
		private Core core = new Core();

		// Triggered when the a new game starts
		public void NewGame() 
		{ 
			Game.Print("BotOS Test!");

			Thread.Sleep( 1000 );

			// change acts
			Core.Goals.Add( new HeapNode( new InteractWaypoint( null, 1, AreaLevel.RogueEncampment, false ), 0 ) );

			///////////////////////////////////////////////////////////////////
			// Start Act 1
			///////////////////////////////////////////////////////////////////
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.Akara ), 1 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.Charsi ), 2 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.DeckardCain ), 3 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.Gheed ), 4 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.Kashya ), 5 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act1Town.Warriv ), 6 ) );
			///////////////////////////////////////////////////////////////////
			// End Act 1
			///////////////////////////////////////////////////////////////////

			// change acts
			Core.Goals.Add( new HeapNode( new InteractWaypoint( null, 0, AreaLevel.LutGholein, false ), 7 ) );

			///////////////////////////////////////////////////////////////////
			// Start Act 2
			///////////////////////////////////////////////////////////////////
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Atma ), 8 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.DeckardCain ), 9 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Drognan ), 10 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Elzix ), 11 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Fara ), 12 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Geglash ), 13 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Greiz ), 14 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Jerhyn ), 15 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Kaelan ), 16 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Lysander ), 17 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Meshif ), 18 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act2Town.Warriv ), 19 ) );
			///////////////////////////////////////////////////////////////////
			// End Act 2
			///////////////////////////////////////////////////////////////////

			// change acts
			Core.Goals.Add( new HeapNode( new InteractWaypoint( null, 0, AreaLevel.KurastDocks, false ), 20 ) );

			///////////////////////////////////////////////////////////////////
			// Start Act 3
			///////////////////////////////////////////////////////////////////
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Alkor ), 21 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Asheara ), 22 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.DeckardCain ), 23 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Hratli ), 24 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Meshif ), 25 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Natalya ), 26 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act3Town.Ormus ), 27 ) );
			///////////////////////////////////////////////////////////////////
			// End Act 3
			///////////////////////////////////////////////////////////////////

			// change acts
			Core.Goals.Add( new HeapNode( new InteractWaypoint( null, 0, AreaLevel.ThePandemoniumFortress, false ), 28 ) );

			///////////////////////////////////////////////////////////////////
			// Start Act 4
			///////////////////////////////////////////////////////////////////
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act4Town.DeckardCain ), 29 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act4Town.Halbu ), 30 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act4Town.Jamella ), 31 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act4Town.Tyrael ), 32 ) );
			///////////////////////////////////////////////////////////////////
			// End Act 4
			///////////////////////////////////////////////////////////////////

			// change acts
			Core.Goals.Add( new HeapNode( new InteractWaypoint( null, 0, AreaLevel.Harrogath, false ), 33 ) );

			///////////////////////////////////////////////////////////////////
			// Start Act 5
			///////////////////////////////////////////////////////////////////
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.Anya ), 34 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.DeckardCain ), 35 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.Larzuk ), 36 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.Malah ), 37 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.Nihlathak ), 38 ) );
			Core.Goals.Add( new HeapNode( new TownMove( null, 0, Act5Town.QualKehk ), 39 ) );
			///////////////////////////////////////////////////////////////////
			// End Act 5
			///////////////////////////////////////////////////////////////////
		} 

		// Triggers when the user types .start in the in game chat
		public void UserStart() 
		{ 
			NewGame();
		} 
		
		#region Other required interface elements

		public void UserStop() 
		{ 
		} 

		public void EndGame(TimeSpan GameLength) 
		{ 
		} 

		public void UserCommand(string command, string[] args) 
		{ 
		} 

		public void Load() 
		{ 
			core.Start();
		} 

		public void Dispose() 
		{ 
		} 

		public void ReceiveMessage(long SenderID, int MessageType, object Data) 
		{ 
		} 

		#endregion
	} 
} 
