using System;
using System.Collections;

using botNET.Mapping;

namespace botNET.Pathing
{
	/// <summary>
	/// The Path object holds an array of System.Drawing.Point objects.
	/// </summary>
	public class Path
	{
		/// <summary>
		/// General constructor
		/// </summary>
		public Path()
		{
			this.coordinates = new ArrayList();

		}

		/// <summary>
		/// Constructir that supports passing an ArrayList of Coordinates
		/// </summary>
		/// <param name="coords">an ArrayList of Coordinates</param>
		public Path(ArrayList coords)
		{
			this.coordinates = coords;
		}

		private ArrayList coordinates;

		/// <summary>
		/// Returns the number of Coordinates in this Path
		/// </summary>
		/// <returns></returns>
		public int Count
		{
			get
			{
				return this.coordinates.Count;
			}
		}

		/// Gets or Sets a System.Drawing.Point at the given element
		/// </summary>
		public System.Drawing.Point this [int param]
		{
			get
			{
				return (System.Drawing.Point)this.coordinates[param];
			}
			set
			{
				this.coordinates[param] = value;
			}
		}

		/// <summary>
		/// The actual ArrayList of Coordinates
		/// </summary>
		public ArrayList CoordinateList
		{
			get
			{
				return this.coordinates;
			}
		}
	}
}
