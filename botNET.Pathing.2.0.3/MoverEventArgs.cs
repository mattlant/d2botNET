using System;

using botNET.Pathing;
using botNET.Mapping;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for MoverEventArgs.
	/// </summary>
	public class MoverEventArgs
	{
		public System.Drawing.Point CurrentCoordinate;
		public int CurrentPathPoint;
		public Mover MoverUsed;
		public Pather PatherUsed;
		public Path PathUsed;
		public bool Stop;

		public MoverEventArgs(System.Drawing.Point c, int i, Mover m)
		{
			this.CurrentCoordinate = c;
			this.CurrentPathPoint = i;
			this.MoverUsed = m;
			this.PatherUsed = m.pather;
			this.PathUsed = this.PatherUsed.path;
			this.Stop = false;
		}
	}
}
