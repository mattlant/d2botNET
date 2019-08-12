using System;
using System.Collections;

using botNET.Mapping;
using botNET.Units;

namespace botNET.Mapping
{
	/// <summary>
	/// Summary description for Area.
	/// </summary>
	public class LevelMap : Map
	{
		private AreaLevel level;
		private Room[] rooms;

		/// <summary>
		/// LevelMap constructor used to Define the Map you character is standing in
		/// </summary>
		public LevelMap()
		{
			this.level = new PC().Area;
			this.rooms = Mapping.Room.Get();
			this.setdata();
		}

		/// <summary>
		/// LevelMap constructor used to Define the Map of teh Level you specify
		/// </summary>
		/// <param name="LevelNumber">The level number this Map will be created for</param>
		public LevelMap(AreaLevel LevelNumber)
		{
			this.level = LevelNumber;
			this.rooms =  Mapping.Room.Get(this.level);
			this.setdata();
		}

		/// <summary>
		/// Gets the Level number this LevelMap defines
		/// </summary>
		public AreaLevel Level
		{
			get{ return this.level; }
		}

		/// <summary>
		/// Gets an ArrayList of Room Objects held in this LevelMap
		/// </summary>
		public Room[] Rooms
		{
			get{ return this.rooms; }
		}

		/// <summary>
		/// Initializes the LevelMap
		/// </summary>
		public override void Initialize()
		{
			if(this.isinitialized) return;

			//Game.Print("About to initialize");
			if(this.rooms.Length ==0)
				throw new ApplicationException("Rooms array is zero length, Internal Error");
			foreach(Mapping.Room r in this.rooms)
			{
				UInt16[,] colldata = r.CollisionData;
				for(int x = 0; x < r.SizeX; x++)
				{
					for(int y = 0; y < r.SizeY; y++)
					{
						this.collisiondata[r.X - this.x + x, r.Y - this.y + y] = colldata[x, y];
						//this.collisiondata.SetValue(colldata.GetValue(x, y), r.X - this.x + x, r.Y - this.y + y);
					}
				}
			}

			this.isinitialized = true;
		}

		private void setdata()
		{
			if(this.rooms.Length ==0)
				throw new ApplicationException("Rooms array is zero length, Internal Error");
			foreach(Mapping.Room r in this.rooms)
			{
				if(r.X < this.x)
					this.x = r.X;
				if(r.Y < this.y)
					this.y = r.Y;
				if((r.MaxX) > this.maxx)
					this.maxx = r.MaxX;
				if(r.MaxY > this.maxy)
					this.maxy = r.MaxY;
			}

			this.sizex = this.maxx - this.x;
			this.sizey = this.maxy - this.y;

			//Game.Print("About to create coll array");
			//Game.Print("sizex: " + this.sizex.ToString());
			//Game.Print("sizey: " + this.sizey.ToString());
			//Game.Print("maxx: " + this.maxx.ToString());
			//Game.Print("maxy: " + this.maxy.ToString());
			//Game.Print("x: " + this.x.ToString());
			//Game.Print("y: " + this.y.ToString());


			this.collisiondata = new UInt16[this.sizex, this.sizey];
		}


		

	}
}
