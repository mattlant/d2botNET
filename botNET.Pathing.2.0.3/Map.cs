using System;
using System.IO;
using System.Collections;

using botNET.Mapping;

namespace botNET.Mapping
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public abstract class Map
	{
		/// <summary>
		/// The Map constructor should be called after initializing an inherited classes members
		/// </summary>
		public Map()
		{
			//this.maxx = this.x + this.sizex;
			//this.maxy = this.y + this.sizey;
		}

		/// <summary>
		/// Pretected x coord
		/// </summary>
		protected int x = 65535;
		/// <summary>
		/// Protected y coord
		/// </summary>
		protected int y = 65535;
		/// <summary>
		/// Protected X size
		/// </summary>
		protected int sizex = 0;
		/// <summary>
		/// Protected Y size
		/// </summary>
		protected int sizey = 0;
		/// <summary>
		/// Protected Max X
		/// </summary>
		protected int maxx = 0;
		/// <summary>
		/// Protected Max Y
		/// </summary>
		protected int maxy = 0;
		/// <summary>
		/// Protected memeber to hold colission data
		/// </summary>
		protected UInt16[,] collisiondata;
		/// <summary>
		/// Protected member to hold if the Map is initialized
		/// </summary>
		protected bool isinitialized;

		/// <summary>
		/// A name you can give this instance of Map
		/// </summary>
		public string Name = "MapWithNoName";

		/// <summary>
		/// Protected member that hold the time it took to initialize initialize the map
		/// </summary>
		protected int InitializationTime = 0;

		/// <summary>
		/// Gets a value indictating if the Map is initialized or not
		/// </summary>
		public bool IsInitialized
		{
			get { return this.isinitialized; }
		}

		/// <summary>
		/// Gets the Map's Collision Data
		/// </summary>
		public UInt16[,] CollisionData
		{
			get { return this.collisiondata; }
		}

		/// <summary>
		/// Gets the Map's X System.Drawing.Point
		/// </summary>
		public int X
		{
			get { return this.x; }
		}

		/// <summary>
		/// Gets the Map's X System.Drawing.Point
		/// </summary>
		public int Y
		{
			get { return this.y; }
		}

		/// <summary>
		/// Gets the Map's Size on the X Axis
		/// </summary>
		public  int SizeX
		{
			get { return this.sizex; }
		}

		/// <summary>
		/// Gets the Map's Size on the Y Axis
		/// </summary>
		public int SizeY
		{
			get	{ return this.sizey; }
		}

		/// <summary>
		/// Gets the Map's Max X System.Drawing.Point
		/// </summary>
		public int MaxX
		{
			get { return this.maxx; }
		}

		/// <summary>
		/// Gets the Map's Max X System.Drawing.Point
		/// </summary>
		public int MaxY
		{
			get { return this.maxy;	}
		}
	
		//Must be overridden in any inherited class
		/// <summary>
		/// Initializes the Map
		/// </summary>
		public virtual void Initialize() 
		{

		}

		/// <summary>
		/// Sets the maps exits
		/// </summary>
		public virtual void SetExits() 
		{

		}

		/// <summary>
		/// Used to Check if a coord is within the COllisionData's Limits
		/// </summary>
		/// <param name="coord">The System.Drawing.Point to check</param>
		/// <returns></returns>
		public virtual bool IsInRange(System.Drawing.Point coord)
		{
			return !(coord.X > this.maxx || coord.X < this.x || coord.Y > this.maxy || coord.Y < this.y);
		}
		/// <summary>
		/// Used to Check if a coord is within the COllisionData's Limits
		/// </summary>
		/// <param name="XCoord">The X System.Drawing.Point to check</param>
		/// <param name="YCoord">The X System.Drawing.Point to check</param>
		/// <returns></returns>
		public virtual bool IsInRange(int XCoord, int YCoord)
		{
			return !(XCoord > this.maxx || XCoord < this.x || YCoord > this.maxy || YCoord < this.y);
		}

		/// <summary>
		/// Checks if the given System.Drawing.Point is walkable
		/// </summary>
		/// <param name="coord">The coordinate to test</param>
		/// <returns>true if walkable else false</returns>
		public virtual bool IsWalkable(System.Drawing.Point coord) 
		{
			if ( !this.IsInRange(coord) ) return false;
			return ((this.collisiondata[coord.X - this.x, coord.Y-this.y] & 0x1) != 0x1);
		}
		/// <summary>
		/// Checks if the given System.Drawing.Point is walkable
		/// </summary>
		/// <param name="_x">The X coordinate to test</param>
		/// <param name="_y">The Y coordinate to test</param>
		/// <returns>true if walkable else false</returns>
		public virtual bool IsWalkable(int _x, int _y) 
		{
			if ( !this.IsInRange( _x, _y) ) return false;
			return ((this.collisiondata[_x - this.x, _y - this.y] & 0x1) != 0x1);
		}

		/// <summary>
		/// Finds the closest walkable coordinate to the given coordinate
		/// </summary>
		/// <param name="coord">Initial System.Drawing.Point</param>
		/// <returns>A coordinate that is closest to the input coordinate</returns>
		public virtual System.Drawing.Point FindClosestWalkable(System.Drawing.Point coord) 
		{
			//Check to see if it is already walkable
			if ( this.IsWalkable(coord) )
				return coord;
			//Check if it is in range
			if (!this.IsInRange(coord))
				throw new ApplicationException("botNET.Pathing.Map.FindClosestWalkable - Map.cs -> Provided coordinates are not in range");

			int dist = 1;
			while (true) 
			{
				for ( int vy = -dist; vy < dist; vy++ ) 
				{
					for ( int vx = -dist; vx < dist; vx++ ) 
					{
						if ( this.IsWalkable(coord.X + vx, coord.Y + vy) ) 
						{
							coord.X += vx;
							coord.Y += vy;
							return coord;
						}
					}
				}
				if(dist++ > 100) 
					throw new ApplicationException("botNET.Pathing.Map.FindClosestWalkable - Map.cs -> Could not find a closest walkable");
			}

		}
		/// <summary>
		/// Finds the closest walkable coordinate to the given coordinate
		/// </summary>
		/// <param name="_x">Initial X System.Drawing.Point</param>
		/// <param name="_y">Initial Y System.Drawing.Point</param>
		/// <returns>A coordinate that is closest to the input coordinate</returns>
		public virtual System.Drawing.Point FindClosestWalkable(int _x, int _y)
		{
			return this.FindClosestWalkable(new System.Drawing.Point(_x, _y));
		}

		/// <summary>
		/// Check to see if you have Line Of Sight between the Start and End Coordinates
		/// </summary>
		/// <param name="StartX">Starting X System.Drawing.Point</param>
		/// <param name="StartY">Starting Y System.Drawing.Point</param>
		/// <param name="EndX">Ending X System.Drawing.Point</param>
		/// <param name="EndY">Ending Y System.Drawing.Point</param>
		/// <returns>Returns true if you have LOS, false otherwise</returns>
		public virtual bool LOS(int StartX, int StartY, int EndX, int EndY) 
		{
			int Ax = StartX;
			int Ay = StartY;
			int Bx = EndX;
			int By = EndY;

			if(!this.IsInRange(Ax, Ay))
				return false;
			if(!this.IsInRange(Bx, By))
				return false;
	        
			int _bit = 4;

			int dX = Math.Abs(Bx-Ax);
			int dY = Math.Abs(By-Ay);

			int Xincr, Yincr;
	        
			if (Ax > Bx) { Xincr=-1; } 
			else { Xincr=1; }
			if (Ay > By) { Yincr=-1; } 
			else { Yincr=1; }

			if (dX >= dY)
			{
				int dPr     = dY<<1;
				int dPru     = dPr - (dX<<1);
				int P         = dPr - dX;
				for (; dX>=0; dX--)    
				{
					if ((this.collisiondata[Ax - this.x, Ay - this.y] & _bit) > 0)
						return false;
	                        
					if (P > 0)
					{
						Ax+=Xincr;
						Ay+=Yincr;
						P+=dPru;
					}
					else
					{
						Ax+=Xincr;
						P+=dPr;
					}
				}
			}
			else
			{
				int dPr     = dX<<1;
				int dPru     = dPr - (dY<<1);
				int P         = dPr - dY;
				for (; dY>=0; dY--)    
				{
					if ((this.collisiondata[Ax - this.x, Ay - this.y] & _bit) > 0)
						return false;

					if (P > 0)
					{
						Ax+=Xincr;
						Ay+=Yincr;
						P+=dPru;
					}
					else
					{
						Ay+=Yincr;
						P+=dPr;
					}
				}
			}
			return true;
		}

		/// <summary>
		/// Dumps the Map to the given file
		/// </summary>
		/// <param name="Bit">The bit to dump, from 0-15</param>
		/// <param name="file">The full filename of the file to dump to</param>
		public virtual void Dump(int Bit, string file) 
		{
			StreamWriter sw = File.CreateText(file);

			int bit = 0x1 << Bit;

			string line = "";

			for(int ly = 0; ly < this.sizey; ly++)
			{
				line += ((this.y+ly).ToString());
				for(int lx = 0; lx < this.sizey; lx++)
				{
					if((this.collisiondata[lx, ly] & bit) != 0)
						line += "X";
					else
						line += ".";
				}

				sw.WriteLine(line);
				line = "";
			}

			sw.Close();
		}

	}
}
