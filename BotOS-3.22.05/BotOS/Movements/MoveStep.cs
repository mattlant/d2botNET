using System;
using System.Drawing;
using System.Threading;

using botNET;
using botNET.Collections;
using botNET.Units;

namespace BotOS.Movements
{
	/// <summary>
	/// </summary>
	public class MoveStep : TaskBase
	{
		private Point mDestination;
		private bool mTeleport;

		/// <summary>
		/// </summary>
		public MoveStep( GoalBase Parent, int Priority, Point destination, bool teleport )
			: base( Parent, Priority )
		{
			mDestination = destination;
			mTeleport = teleport;
		}

		/// <summary>
		/// </summary>
		public override bool Completed
		{
			get
			{
				PC pc = new PC();

				if( Math.Abs( pc.X - mDestination.X ) < 10 && Math.Abs( pc.Y - mDestination.Y ) < 10 )
					return true;

				return false;
			}
		}

		/// <summary>
		/// </summary>
		public override void Execute()
		{
			PC pc = new PC();

			if( mTeleport )
				TeleportTo( mDestination );
			else
				WalkTo( mDestination );
		}

		/// <summary>
		/// </summary>
		private int TeleportTo( Point c )
		{
			return 0;
		}

		/// <summary>
		/// </summary>
		private int WalkTo( Point c )
		{
			PC Me = new PC();

			int TargetX = c.X;
			int TargetY = c.Y;

			int startX = Me.X;
			int startY = Me.Y;
			int currDestX = TargetX;
			int currDestY = TargetY;

			if (Math.Abs(Me.X - TargetX) <= 2 &&
			    Math.Abs(Me.Y - TargetY) <= 2) return 1;

			int trys = 0;
			int ntrys=12;
			int thrash = 0;
			int nthrash=3;
			int door;
			int directionalmove=0;
			double direction = 0;

			while ((Math.Abs(Me.X - TargetX) > 3 || Math.Abs(Me.Y - TargetY) > 3) && trys <= ntrys)
			{
				Me.ClickMap(ClickType.LeftDown, false, currDestX, currDestY);
				Thread.Sleep(100);
				Me.ClickMap(ClickType.LeftUp, false, currDestX, currDestY);

				while (Me.Mode != PlayerMode.Neutral && Me.Mode != PlayerMode.TownNeutral)
					Thread.Sleep(20);
				trys++;
				if ((Math.Abs(Me.X - TargetX) > 1 && Math.Abs(Me.Y - TargetX) > 1))
				{
					if (thrash >= nthrash)
					{
						direction = Math.Abs(Math.Floor((Math.Atan2(TargetX-Me.X , TargetY-Me.Y)) * 180 / 3.1415) - 180);
						if (direction > 0 && direction < 45)
						{
							currDestX = Me.X+5;
							currDestY = Me.Y+1;
						}
						else if(direction > 45 && direction < 90) 
						{
							currDestX = Me.X-1;
							currDestY = Me.Y-5;
						}
						else if (direction > 90 && direction < 135)
						{
							currDestX = Me.X-1;
							currDestY = Me.Y+5;
						}
						else if(direction > 135 && direction < 180) 
						{
							currDestX = Me.X+5;
							currDestY = Me.Y-1;
						}
						else if (direction > 180 && direction < 225)
						{
							currDestX = Me.X-5;
							currDestY = Me.Y-1;
						}
						else if(direction > 225 && direction < 270) 
						{
							currDestX = Me.X+1;
							currDestY = Me.Y+5;
						}
						else if (direction > 270 && direction < 315)
						{
							currDestX = Me.X+1;
							currDestY = Me.Y-5;
						}
						else if(direction > 315 && direction < 360) 
						{
							currDestX = Me.X-5;
							currDestY = Me.Y+1;
						}
						else
						{
							//make a randome move
							int dx = currDestX - startX;
							int dy = currDestY - startY;
							double a = Math.Atan2(dx, dy);
							a = Math.Floor(a * 100) + 157;  // + pi/2;
							direction = (new Random()).Next((int)a, (int)a+314)/100;  // + pi
							currDestX = Convert.ToInt32(Math.Floor(Math.Sin(direction)*20) + Me.X);
							currDestY = Convert.ToInt32(Math.Floor(Math.Cos(direction)*20) + Me.Y);
						}
						directionalmove = 0;

						//########################################
						thrash=0;
						directionalmove++;
					} 
					else thrash++;
				}
				else
				{
					startX = Me.X;
					startY = Me.Y;
					currDestX = TargetX;
					currDestY = TargetY;
				}

			}
			if (Math.Abs(Me.X - TargetX) > 4 || Math.Abs(Me.Y - TargetY) > 4)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
}
