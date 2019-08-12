using System;
using System.Collections;
using System.Threading;

using botNET.Units;
using botNET.Mapping;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for Mover.
	/// </summary>
	public class Mover
	{

		public delegate void MoverCallBackHandler(MoverEventArgs e);

		public int WalkDelay = 100;
		 
		internal Pather pather;
		internal Path path;

		/// <summary>
		/// Creates a new Mover to move your character.
		/// </summary>
		/// <param name="PatherToUse">The Pather object. </param>
		public Mover(Pather PatherToUse)
		{
			this.path = PatherToUse.path;
			this.pather = PatherToUse;
		}

		/// <summary>
		/// Initiates the movement process
		/// </summary>
		/// <returns>True if successful, false otherwise. </returns>
		public bool Move()
		{
			return this.Move(0);
		}

		/// <summary>
		/// Initiates the movement process
		/// </summary>
		/// <param name="StartPoint">You can pass an integer to represent the point on the path to start at in case you already did some manual movement</param>
		/// <returns>True if successful, false otherwise. </returns>
		public bool Move(int StartPoint)
		{
			int failedhops = 0;
			int retval;

			PC Me = new PC();

	
			for (int i=StartPoint; i<path.Count; i++)
			{
				if(Me.HP == 0) return false;

				bool tele = !Me.IsInTown && Me.GetSkillLevel(SkillType.Teleport) > 0 && this.pather.PatherConfiguration.ReductionType == Reduction.TeleportReduction;
				if(tele) 
					retval = TeleportToXY(path[i], i);
				else 
					retval = WalkToXY(path[i], i);

				if(retval == -1) return false;
				if (retval == 0)
				{
					if(!this.pather.map.IsInRange(Me.X, Me.Y)) 
						throw new ApplicationException ("Mover.Move -> We do not seem to be i the right area");

					Path midpath;

					try
					{
						midpath = this.pather.FindPath(path[i].X, path[i].Y, Me.X, Me.Y);
					}
					catch
					{
						throw new ApplicationException("Mover.PathMove -> Couldn't recalculate a path");
					}
				
					for(int k = 0; k<midpath.Count; k++) 
					{
						if(tele) 
							retval = TeleportToXY(midpath[k], i);
						else 
							retval = WalkToXY(midpath[k], i);
					}
				}
				if(retval == -1) return false;

				if (retval == 0)
				{
					Game.Print("We couldnt find a way to the next path point");
					if(failedhops == 5)
						throw new ApplicationException("Mover.PathMove - had five failed destinations along this path");
				
					failedhops++;
				}
				else if(retval == -1) return false;
				//delay(50);

				//Thread.Sleep(50);
			}
			return true;
		}
		
		//////////////////////////////////////////////////////////////////////
		// mlwalkto(x, y, walkcallflag)
		// -------------------------------------------------------------------
		// walks to the given coordinates
		// returns: true on success, false on failure
		// requires mlMapInitializeMap: NO
		//////////////////////////////////////////////////////////////////////
		private int WalkToXY(System.Drawing.Point c, int currpoint) //currentpoint is for internal use only
		{
			PC Me = new PC();
			int TargetX = c.X;
			int TargetY = c.Y;

			int startX = Me.X;
			int startY = Me.Y;
			int currDestX = TargetX;
			int currDestY = TargetY;

			if (Math.Abs(Me.X - TargetX) <= 2 && Math.Abs(Me.Y - TargetY) <= 2) return 1;

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

				MoverEventArgs mve = new MoverEventArgs(c, currpoint, this);

				RaiseMoverCallBackHandler(mve);

				if(mve.Stop) return -1;

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


		//////////////////////////////////////////////////////////////////////
		// mlteleportto(x, y, walkcallflag)
		// -------------------------------------------------------------------
		// teleports to the given coordinates
		// returns: true on success, false on failure
		// requires mlMapInitializeMap: NO
		//////////////////////////////////////////////////////////////////////
		private int TeleportToXY(System.Drawing.Point c, int Currentpoint) //current point is used internally
		{

			PC Me = new PC();
			int TargetX = c.X;
			int TargetY = c.Y;

			for (int rv = 0; rv < 3; rv++)
			{
				MoverEventArgs mve = new MoverEventArgs(c, Currentpoint, this);

				RaiseMoverCallBackHandler(mve);

				if(mve.Stop) return -1;

				Mover.CastAtXY(SkillType.Teleport, SkillHand.Right, TargetX, TargetY);
				// Check to see see if we have arrived at our destination
				if ((Math.Abs(Me.X - TargetX) < 6) && (Math.Abs(Me.Y - TargetY) < 6))
					return 1;
			}


			if ((Math.Abs(Me.X - TargetX) < 6) && (Math.Abs(Me.Y - TargetY) < 6))
				return 1;
			else
				return 0;

		}

		public static void CastAtXY(SkillType Skill, SkillHand Hand, int TargetX, int TargetY)
		{
			PC Me = new PC();
			if(Me.GetSkillOnHand(Hand) != Skill)
			{
				Me.SetSkill(Skill, Hand);
				int count=0;
				while(true) 
				{
					if(Me.GetSkillOnHand(Hand) == Skill) break;
					Thread.Sleep(20);
					count++;
					if(count>50) 
						throw new ApplicationException("Could not set skill on the given hand");
				}
			}

			int click = 3;
			if(Hand == SkillHand.Left)
				click = 0;
			Me.ClickMap((ClickType)click, false, TargetX, TargetY);
			Thread.Sleep(100);
			Me.ClickMap((ClickType)(click + 2), false, TargetX, TargetY);
			//return;

			if(Me.Mode == PlayerMode.Cast)
                if(!ModeWait(PlayerMode.Cast, false))
					throw new ApplicationException("Could not start casting");

			if(!ModeWait(PlayerMode.Neutral, false))
				throw new ApplicationException("Could not detect end of casting");
			
		}

		private static bool ModeWait(PlayerMode mode, bool negate)
		{
			PC Me = new PC();
			int count = 0;
			if(mode == PlayerMode.TownNeutral) mode = PlayerMode.Neutral;
			if(negate)
			{

				while(Me.Mode == mode)
				{
					Thread.Sleep(10);
					if(count++ > 100)
						return false;
				}
				return true;
			}
			else
			{

				while(Me.Mode != mode)
				{
					Thread.Sleep(10);
					if(count++ > 100)
						return false;
				}
				return true;
			}


		}

		public event MoverCallBackHandler OnMoverCallBack;

		public void RaiseMoverCallBackHandler(MoverEventArgs e)
		{
			try
			{
				OnMoverCallBack(e);
			}
			catch 
			{
			}
		}







	}
}

