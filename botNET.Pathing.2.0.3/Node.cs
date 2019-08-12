using System;

using botNET.Mapping;


namespace botNET.Pathing
{
	/// <summary>
	/// A Node object is used by the pather to hold a coordinates info
	/// </summary>
	public class Node
	{
		/// <summary>
		/// Holds the X of the node
		/// </summary>
		public int X;
		/// <summary>
		/// Holds the Y of the node
		/// </summary>
		public int Y;

		/// <summary>
		/// A value indicating if the node is Open
		/// </summary>
		public bool IsOpen;
		/// <summary>
		/// A value indicating if the node is Closed
		/// </summary>
		public bool IsClosed;

		/// <summary>
		/// Holds a refernce to a Node which is this Node's Parent
		/// </summary>
		public Node Parent;

		private double g;
		private double h;
		private double f;

		/// <summary>
		/// Creates an instance of Node
		/// </summary>
		/// <param name="X">Sets the X of the node</param>
		/// <param name="Y">Sets the X of the node</param>
		/// <param name="IsOpen">Sets a value indicating if the node is Open</param>
		/// <param name="IsClosed">Sets s value indicating if the node is Closed</param>
		/// <param name="Parent">Sets this nodes Parent</param>
		/// <param name="g">Sets the G of the node</param>
		/// <param name="h">Sets the H of the node</param>
		public Node(int X, int Y, bool IsOpen, bool IsClosed, Node Parent, double g, double h)
		{
			this.X = X;
			this.Y = Y;
			this.IsOpen = IsOpen;
			this.IsClosed = IsClosed;
			this.Parent = Parent;
			this.g = g;
			this.h = h;
			this.f = g + h;
		}

		/// <summary>
		/// Gets or Sets the G value of the Node
		/// </summary>
		public double G
		{
			get
			{
				return this.g;
			}
			set 
			{
				this.g = value;
				this.f = this.g + this.h;
			}
		}

		/// <summary>
		/// Gets or Sets the H value of the Node
		/// </summary>
		public double H
		{
			get
			{
				return this.h;
			}
			set 
			{
				this.h = value;
				this.f = this.g + this.h;
			}
		}

		/// <summary>
		/// Gets the F value of the Node
		/// </summary>
		public double F
		{
			get
			{
				return this.f;
			}
		}
	}
}
