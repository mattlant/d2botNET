using System;
using System.Drawing;
using System.Xml;

using botNET;
using botNET.Collections;
using botNET.Units;

namespace BotOS.Movements
{

	/// <summary>
	/// </summary>
	public enum VendorType
	{
		/// <summary>
		/// </summary>
		Armor,
		/// <summary>
		/// </summary>
		Arrows,
		/// <summary>
		/// </summary>
		Bolts,
		/// <summary>
		/// </summary>
		Katars,
		/// <summary>
		/// </summary>
		Heal,
		/// <summary>
		/// </summary>
		Hire,
		/// <summary>
		/// </summary>
		Identify,
		/// <summary>
		/// </summary>
		Keys,
		/// <summary>
		/// </summary>
		Potions,
		/// <summary>
		/// </summary>
		Repair,
		/// <summary>
		/// </summary>
		Scepters,
		/// <summary>
		/// </summary>
		Scrolls,
		/// <summary>
		/// </summary>
		Staves,
		/// <summary>
		/// </summary>
		ThrowingWeapons,
		/// <summary>
		/// </summary>
		Tomes,
		/// <summary>
		/// </summary>
		Wands,
		/// <summary>
		/// </summary>
		Weapons
	}

	/// <summary>
	/// </summary>
	public enum Act1Town
	{
		/// <summary>
		/// </summary>
		TownPortal = 1,
		/// <summary>
		/// </summary>
		Stash = 267,
		/// <summary>
		/// </summary>
		Waypoint = 119,
		/// <summary>
		/// </summary>
		Akara = 148,
		/// <summary>
		/// </summary>
		DeckardCain = 265,
		/// <summary>
		/// </summary>
		Charsi = 154,
		/// <summary>
		/// </summary>
		Gheed = 147,
		/// <summary>
		/// </summary>
		Kashya = 150,
		/// <summary>
		/// </summary>
		Warriv = 155
	}

	/// <summary>
	/// </summary>
	public enum Act2Town
	{
		/// <summary>
		/// </summary>
		Stash = 267,
		/// <summary>
		/// </summary>
		TownPortal = 1,
		/// <summary>
		/// </summary>
		Waypoint = 156,
		/// <summary>
		/// </summary>
		Atma = 176,
		/// <summary>
		/// </summary>
		DeckardCain = 244,
		/// <summary>
		/// </summary>
		Drognan = 177,
		/// <summary>
		/// </summary>
		Elzix = 199,
		/// <summary>
		/// </summary>
		Fara = 178,
		/// <summary>
		/// </summary>
		Geglash = 200,
		/// <summary>
		/// </summary>
		Greiz = 198,
		/// <summary>
		/// </summary>
		Jerhyn = 201,
		/// <summary>
		/// </summary>
		Kaelan = 331,
		/// <summary>
		/// </summary>
		Lysander = 202,
		/// <summary>
		/// </summary>
		Meshif = 210,
		/// <summary>
		/// </summary>
		Warriv = 175,
	}

	/// <summary>
	/// </summary>
	public enum Act3Town
	{
		/// <summary>
		/// </summary>
		Stash = 267,
		/// <summary>
		/// </summary>
		TownPortal = 1,
		/// <summary>
		/// </summary>
		Waypoint = 237,
		/// <summary>
		/// </summary>
		Alkor = 254,
		/// <summary>
		/// </summary>
		Asheara = 252,
		/// <summary>
		/// </summary>
		DeckardCain = 245,
		/// <summary>
		/// </summary>
		Hratli = 253,
		/// <summary>
		/// </summary>
		Meshif = 264,
		/// <summary>
		/// </summary>
		Natalya = 297,
		/// <summary>
		/// </summary>
		Ormus = 255,
	}

	/// <summary>
	/// </summary>
	public enum Act4Town : int
	{
		/// <summary>
		/// </summary>
		Stash = 267,
		/// <summary>
		/// </summary>
		TownPortal = 1,
		/// <summary>
		/// </summary>
		Waypoint = 398,
		/// <summary>
		/// </summary>
		RedPortal = 4,
		/// <summary>
		/// </summary>
		DeckardCain = 246,
		/// <summary>
		/// </summary>
		Halbu = 257,
		/// <summary>
		/// </summary>
		Jamella = 405,
		/// <summary>
		/// </summary>
		Tyrael = 367,
	}

	/// <summary>
	/// </summary>
	public enum Act5Town : int
	{
		/// <summary>
		/// </summary>
		Stash = 267,
		/// <summary>
		/// </summary>
		TownPortal = 1,
		/// <summary>
		/// </summary>
		Waypoint = 429,
		/// <summary>
		/// </summary>
		RedPortal = 4,
		/// <summary>
		/// </summary>
		Anya = 512,
		/// <summary>
		/// </summary>
		DeckardCain = 520,
		/// <summary>
		/// </summary>
		Larzuk = 511,
		/// <summary>
		/// </summary>
		Malah = 513,
		/// <summary>
		/// </summary>
		Nihlathak = 514,
		/// <summary>
		/// </summary>
		QualKehk = 515
	}

	/// <summary>
	/// </summary>
	public class TownMove : GoalBase
	{
		private AreaLevel mArea;
		private UnitType mUnitType;
		private int mLocation;

		/// <summary>
		/// </summary>
		public TownMove( GoalBase parent, int priority, Act1Town location )
			: base( parent, priority )
		{
			mArea = AreaLevel.RogueEncampment;
			mLocation = (int)location;

			switch( location )
			{
				case Act1Town.Akara:
				case Act1Town.Charsi:
				case Act1Town.DeckardCain:
				case Act1Town.Gheed:
				case Act1Town.Kashya:
				case Act1Town.Warriv:
					mUnitType = UnitType.NPC;
					break;

				case Act1Town.Stash:
				case Act1Town.Waypoint:
					mUnitType = UnitType.GameObject;
					break;

				default:
					mUnitType = UnitType.Invalid;
					break;
			}

			Update();
		}

		/// <summary>
		/// </summary>
		public TownMove( GoalBase parent, int priority, Act2Town location )
			: base( parent, priority )
		{
			mArea = AreaLevel.LutGholein;
			mLocation = (int)location;

			switch( location )
			{
				case Act2Town.Atma:
				case Act2Town.DeckardCain:
				case Act2Town.Drognan:
				case Act2Town.Elzix:
				case Act2Town.Fara:
				case Act2Town.Geglash:
				case Act2Town.Greiz:
				case Act2Town.Jerhyn:
				case Act2Town.Kaelan:
				case Act2Town.Lysander:
				case Act2Town.Meshif:
				case Act2Town.Warriv:
					mUnitType = UnitType.NPC;
					break;

				case Act2Town.Stash:
				case Act2Town.Waypoint:
					mUnitType = UnitType.GameObject;
					break;

				default:
					mUnitType = UnitType.Invalid;
					break;
			}

			Update();
		}

		/// <summary>
		/// </summary>
		public TownMove( GoalBase parent, int priority, Act3Town location )
			: base( parent, priority )
		{
			mArea = AreaLevel.KurastDocks;
			mLocation = (int)location;

			switch( location )
			{
				case Act3Town.Alkor:
				case Act3Town.Asheara:
				case Act3Town.DeckardCain:
				case Act3Town.Hratli:
				case Act3Town.Meshif:
				case Act3Town.Natalya:
				case Act3Town.Ormus:
					mUnitType = UnitType.NPC;
					break;

				case Act3Town.Stash:
				case Act3Town.Waypoint:
					mUnitType = UnitType.GameObject;
					break;

				default:
					mUnitType = UnitType.Invalid;
					break;
			}

			Update();
		}

		/// <summary>
		/// </summary>
		public TownMove( GoalBase parent, int priority, Act4Town location )
			: base( parent, priority )
		{
			mArea = AreaLevel.ThePandemoniumFortress;
			mLocation = (int)location;

			switch( location )
			{
				case Act4Town.DeckardCain:
				case Act4Town.Halbu:
				case Act4Town.Jamella:
				case Act4Town.Tyrael:
					mUnitType = UnitType.NPC;
					break;

				case Act4Town.Stash:
				case Act4Town.Waypoint:
					mUnitType = UnitType.GameObject;
					break;

				default:
					mUnitType = UnitType.Invalid;
					break;
			}

			Update();
		}

		/// <summary>
		/// </summary>
		public TownMove( GoalBase parent, int priority, Act5Town location )
			: base( parent, priority )
		{
			mArea = AreaLevel.Harrogath;
			mLocation = (int)location;

			switch( location )
			{
				case Act5Town.Anya:
				case Act5Town.DeckardCain:
				case Act5Town.Larzuk:
				case Act5Town.Malah:
				case Act5Town.Nihlathak:
				case Act5Town.QualKehk:
					mUnitType = UnitType.NPC;
					break;

				case Act5Town.Stash:
				case Act5Town.Waypoint:
					mUnitType = UnitType.GameObject;
					break;

				default:
					mUnitType = UnitType.Invalid;
					break;
			}

			Update();
		}

		/// <summary>
		/// Updates the internal subgoals array.  Will rebuild if out of sync.
		/// </summary>
		public override void Update()  // change name to Update()
		{
			mSubGoals.Clear();

			PC pc = new PC();

			if( pc.Area != mArea )
			{
//				mSubGoals.Enqueue( new MoveToArea( ) );
			}

			if( mLocation == 1 ) // this is TownPortal in all ActXTown enums
			{
				// do stuff here
			}
			else
			{
				UnitBase location = new Missile(); // need to add UnitBase default constructor
				switch( mUnitType )
				{
					case UnitType.NPC:
						location = new NPC( mLocation );
						break;

					case UnitType.GameObject:
						location = new GameObject( mLocation );
						break;
				}

				if( location.IsValid() )
				{
					if( Math.Abs( pc.X - location.X ) > 5 || Math.Abs( pc.Y - location.Y ) > 5 )
					{
						mSubGoals.Enqueue( new MoveToPoint( this, mPriority, location.Point, false ) );
					}
				}
				else
				{
					foreach( PresetUnit unit in PresetUnit.Get( mArea, mUnitType ) )
					{
						if( unit.ClassID == mLocation )
						{
							if( Math.Abs( pc.X - unit.X ) > 5 || Math.Abs( pc.Y - unit.Y ) > 5 )
							{
								mSubGoals.Enqueue( new MoveToPoint( this, mPriority, unit.Point, false ) );
							}
							break;
						}
					}
				}
			}

			// call base classes Update()
			base.Update();
		}
	}
}
