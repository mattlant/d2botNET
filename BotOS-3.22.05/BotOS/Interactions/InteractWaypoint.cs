using System;
using System.Collections;
using System.Drawing;
using System.Threading;

using botNET;
using botNET.Mapping;
using botNET.Pathing;
using botNET.Units;

namespace BotOS.Movements
{
	/// <summary>
	/// Summary description for InteractWaypoint.
	/// </summary>
	public class InteractWaypoint : GoalBase
	{
		private AreaLevel mDestination;
		private AreaLevel mSource;
		private bool mTeleport;

		/// <summary>
		/// </summary>
		public InteractWaypoint( GoalBase Parent, int Priority, AreaLevel destination, bool teleport )
			: this( Parent, Priority, AreaLevel.None, destination, teleport )
		{
		}

		/// <summary>
		/// </summary>
		public InteractWaypoint( GoalBase Parent, int Priority, AreaLevel source, AreaLevel destination, bool teleport )
			: base( Parent, Priority )
		{
			mDestination = destination;
			mSource = source;
			mTeleport = teleport;
		}

		/// <summary>
		/// </summary>
		public override TaskBase[] Tasks
		{
			get
			{
				ArrayList tasks = new ArrayList();

				tasks.Add( new OpenWaypointMenu( this, mPriority+1 ) );
				tasks.Add( new SelectDestination( this, mPriority+2, mDestination ) );
				tasks.Add( new CloseWaypointMenu( this, mPriority+3 ) );

				return (TaskBase[])tasks.ToArray( typeof( TaskBase ) );
			}
		}

		/// <summary>
		/// Updates the internal subgoals array.  Will rebuild if out of sync.
		/// </summary>
		public override void Update()
		{
			mSubGoals.Clear();

			PC pc = new PC();

			// should check if we are on a level that doesn't have a waypoint

			// get the waypoint's preset unit on the target level
			AreaLevel area = mSource == AreaLevel.None ? pc.Area : mSource;
			foreach( PresetUnit waypoint in PresetUnit.Get( area, UnitType.Object ) )
			{
				foreach( int classid in new int[] { 119, 145, 156, 157, 237, 238, 288, 323, 324, 398, 402, 429, 494, 496, 511, 539} )
				{
					if( waypoint.ClassID == classid )
					{
						if( Math.Abs( pc.X - waypoint.X ) > 5 || Math.Abs( pc.Y - waypoint.Y ) > 5 )
						{
							mSubGoals.Enqueue( new MoveToWaypoint( this, mPriority+2, area, mTeleport ) );
						}
						goto WAYPOINTFOUND;
					}
				}
			}
			WAYPOINTFOUND:

			// call base classes Update()
			base.Update();
		}

		/// <summary>
		/// </summary>
		private class OpenWaypointMenu : TaskBase
		{
			/// <summary>
			/// </summary>
			/// <param name="parent"></param>
			/// <param name="priority"></param>
			public OpenWaypointMenu( GoalBase parent, int priority )
				: base( parent, priority )
			{
			}

			public override void Execute()
			{
				PC pc = new PC();

				GameObject waypoint = new GameObject();
				foreach( int classid in new int[] { 119, 145, 156, 157, 237, 238, 288, 323, 324, 398, 402, 429, 494, 496, 511, 539} )
				{
					waypoint = new GameObject( classid );
					if( waypoint.IsValid() )
						break;
				}
				if( !waypoint.IsValid() )
					return;  // need an error here

				// open waypoint menu
				for( int i = 0; i < 3 && !Game.GetUIState( UIState.WaypointPanel ); i++ )
				{
					pc.Interact( waypoint );
					Thread.Sleep(500);
				}
			}

		}

		/// <summary>
		/// </summary>
		private class SelectDestination : TaskBase
		{
			private AreaLevel mDestination;

			/// <summary>
			/// </summary>
			/// <param name="parent"></param>
			/// <param name="priority"></param>
			/// <param name="destination"></param>
			public SelectDestination( GoalBase parent, int priority, AreaLevel destination )
				: base( parent, priority )
			{
				mDestination = destination;
			}

			public override void Execute()
			{
				PC pc = new PC();

				if( !Game.GetUIState( UIState.WaypointPanel ) )
					return;

				GameObject waypoint = new GameObject();
				foreach( int classid in new int[] { 119, 145, 156, 157, 237, 238, 288, 323, 324, 398, 402, 429, 494, 496, 511, 539} )
				{
					waypoint = new GameObject( classid );
					if( waypoint.IsValid() )
						break;
				}
				if( !waypoint.IsValid() )
					return;  // need an error here

				for( int i = 0; i < 3 && pc.Area != mDestination; i++ )
				{
					if( waypoint.IsValid() )
						waypoint.Interact( mDestination );  // do I need to check for valid?
					Thread.Sleep( 1000 );
				}
			}
		}

		/// <summary>
		/// </summary>
		private class CloseWaypointMenu : TaskBase
		{
			/// <summary>
			/// </summary>
			/// <param name="parent"></param>
			/// <param name="priority"></param>
			public CloseWaypointMenu( GoalBase parent, int priority )
				: base( parent, priority )
			{
			}

			public override void Execute()
			{
				for( int i = 0; i < 3 && Game.GetUIState( UIState.WaypointPanel ); i++ )
				{
					Game.Cancel();
					Thread.Sleep(500);
				}
				if( Game.GetUIState( UIState.WaypointPanel ) )
					return;  // error here
			}
		}
	}
}
