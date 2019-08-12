using System;

using botNET.Mapping;

namespace botNET.Mapping
{
	/// <summary>
	/// An object representing a Map of a room
	/// Inherits from Map
	/// </summary>
	public class RoomMap : Map
	{

		/// <summary>
		/// RoomMap represents a Single Room in Diablo. It inherits from Map so it can be Pathed on
		/// </summary>
		/// <param name="rRoom">The Room object that this RoomMap will be made from</param>
		public RoomMap(Mapping.Room rRoom)
		{
			this.room = rRoom;
			this.Name = "Room" + rRoom.Number;

			//process the Collision Data
			this.collisiondata = rRoom.CollisionData;


			//Set 
			this.sizex = rRoom.SizeX;
			this.sizey = rRoom.SizeY;
			this.x = rRoom.X;
			this.y = rRoom.Y;

			//Get level Offsets
			this.LevelOffSetX = this.x - this.room.LevelX;
			this.LevelOffSetY = this.y - this.room.LevelY;

		}

		private Mapping.Room room;

		/// <summary>
		/// Relative X Offset of the room to teh level
		/// </summary>
		public int LevelOffSetX; //need to implement LevelX, LevelY
		/// <summary>
		/// Relative Y Offset of the room to teh level
		/// </summary>
		public int LevelOffSetY; 

		/// <summary>
		/// Gets the underlying botNET.Room's Room Number
		/// </summary>
		public int Number
		{
			get
			{
				return this.room.Number;
			}
		}

	

	}
}
