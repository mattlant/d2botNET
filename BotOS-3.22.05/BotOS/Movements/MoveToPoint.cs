using System;
using System.Collections;
using System.Drawing;

using botNET;
using botNET.Mapping;
using botNET.Pathing;
using botNET.Units;

namespace BotOS.Movements
{
	/// <summary>
	/// Summary description for MoveToPoint.
	/// </summary>
	public class MoveToPoint : GoalBase
	{
		private Point mDestination;
		private bool mTeleport;

		private LevelMap map;
		private Pather pather;

		/// <summary>
		/// </summary>
		public MoveToPoint( GoalBase Parent, int Priority, Point destination, bool teleport )
			: base( Parent, Priority )
		{
			mDestination = destination;
			mTeleport = teleport;
		}

		/// <summary>
		/// </summary>
		public override TaskBase[] Tasks
		{
			get
			{
				PC pc = new PC();

				if( map == null || map.Level != pc.Area )
				{
					// initialize our LevelMap
					map = new LevelMap( pc.Area );
					map.Initialize();
				}

				if( pather == null )
					pather = new Pather( map );

				// setup pather
				if( mTeleport )
				{
					pather.PatherConfiguration.ReductionType = Reduction.TeleportReduction;
					pather.PatherConfiguration.PathPointDistance = 25;
				}
				else
				{
					pather.PatherConfiguration.ReductionType = Reduction.WalkingReduction;
					pather.PatherConfiguration.PathPointDistance = 15;
				}

				Path path = null;
				bool retry = true;
				for( int i = 0; i < 5 && retry; i++ )
				{
					retry = false;
					try
					{
						path = pather.FindPath( mDestination.X, mDestination.Y );
					}
					catch( Exception exception )
					{
						// print exception here
						retry = true;
					}
				}
				if( path == null )
					return new TaskBase[0];  // should put error on error queue

				// initialize our return value
				TaskBase[] tasks = new TaskBase[path.Count-1];

				ArrayList points = path.CoordinateList;
				for( int i = 1; i < points.Count; i++ )
				{
					Point point = (Point)points[i];

					tasks[i-1] = new MoveStep( this, mPriority+i, point, mTeleport );
				}

				return tasks;
			}
		}
	}
}
