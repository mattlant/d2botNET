using System;
using System.Collections;

using botNET.Pathing;
using botNET.Mapping;
using botNET.Units;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for Pather.
	/// </summary>
	public class Pather
	{
		/// <summary>
		/// Creates a Pather object used for Pathing
		/// </summary>
		/// <param name="mMap">An object that inherits from the Map object</param>
		public Pather(Map mMap)
		{
			this.map = mMap;
			this.patherconfig = new PatherConfig(Heuristic.DiagonalShortcut, 1, 5, Reduction.WalkingReduction);
		}

		/// <summary>
		/// Creates a Pather object used for Pathing
		/// </summary>
		/// <param name="mMap">An object that inherits from the Map object</param>
		/// <param name="PatherConfiguration">Defines the Pather configuration</param>
		public Pather(Map mMap, PatherConfig PatherConfiguration)
		{
			this.map = mMap;
			this.patherconfig = PatherConfiguration;
		}

		internal Map map;
		private bool plotpathtomap;
		internal Path path;
		private PatherConfig patherconfig;
		private readonly double[] SCORE = {1, 1.414};
		private PresetUnit presetunit;
		
		/// <summary>
		/// Gets a PresetUnit if one was used
		/// </summary>
		public PresetUnit PresetUnitUsed
		{
			get { return this.presetunit; }
		}

		/// <summary>
		/// Holds the Score of the last path generated
		/// </summary>
		public double LastScore = 0;

		/// <summary>
		/// Gets the PatherConfig used for this instance
		/// </summary>
		public PatherConfig PatherConfiguration
		{
			get { return this.patherconfig; }
		}

		/// <summary>
		/// Finds a Path to the given Warp
		/// </summary>
		/// <param name="WarpID">The ID of the warp to path to</param>
		/// <returns></returns>
		public Path FindPathToWarp(int WarpID)
		{
			return FindPathToWarp(new int []{ WarpID });
		}

		/// <summary>
		/// Finds a Path to the given Warps
		/// </summary>
		/// <param name="WarpID">The ID of the warp to path to</param>
		/// <returns></returns>
		public Path FindPathToWarp(int[] WarpID)
		{
			PC Me = new PC();

			PresetUnit[] presets = PresetUnit.Get(Me.Area, UnitType.Warp);

			foreach(PresetUnit p in presets)
			{
				foreach(int i in WarpID)
				{
					if(p.ClassID == i)
						return FindPath(p);

				}
			}

			throw new ApplicationException("Could not find the given warp ID");

		}

		/// <summary>
		/// Finds a Path to the given Warp
		/// </summary>
		/// <returns></returns>
		public Path FindPathToWaypoint()
		{
			PC Me = new PC();

			int[] waypoints = new int[] { 119, 145, 156, 157, 237, 238, 288, 323, 324, 398, 402, 429, 494, 496, 511, 539};

			PresetUnit[] presets = PresetUnit.Get(Me.Area, UnitType.Object);

			foreach(PresetUnit p in presets)
			{

				foreach(int i in waypoints)
				{
					if(p.ClassID == i) 
						return FindPath(p);
				}
			}

			throw new ApplicationException("Could not find a waypoint");

		}

		/// <summary>
		/// Finds a Path to the given PresetUnit
		/// </summary>
		/// <param name="Preset">The Preset Unit to path to</param>
		/// <returns>A Path object containg the Path's Coordinates</returns>
		public Path FindPath(PresetUnit Preset)
		{
			PC Me = new PC();
			this.presetunit = Preset;
			return FindPath(Preset.X, Preset.Y, Me.X, Me.Y);
		}

		/// <summary>
		/// Finds a Path to teh given Destination
		/// </summary>
		/// <param name="DestinationX">The destinations X System.Drawing.Point</param>
		/// <param name="DestinationY">The destinations Y System.Drawing.Point</param>
		/// <returns>A Path object containg the Path's Coordinates</returns>
		public Path FindPath(int DestinationX, int DestinationY)
		{
			PC Me = new PC();
			return FindPath(DestinationX, DestinationY, Me.X, Me.Y);
		}

		/// <summary>
		/// Finds a Path to teh given Destination
		/// </summary>
		/// <param name="DestinationX">The destinations X System.Drawing.Point</param>
		/// <param name="DestinationY">The destinations Y System.Drawing.Point</param>
		/// <param name="StartX">The starting X System.Drawing.Point</param>
		/// <param name="StartY">The starting Y System.Drawing.Point</param>
		/// <returns>A Path object containg the Path's Coordinates</returns>
		public Path FindPath(int DestinationX, int DestinationY, int StartX, int StartY)
		{
			System.Drawing.Point dest = new System.Drawing.Point(DestinationX - this.map.X, DestinationY - this.map.Y);
			System.Drawing.Point start = new System.Drawing.Point(StartX - this.map.X, StartY - this.map.Y);

			double newg = 0;
			int cx = 0;
			int cy = 0;
			Node node;
			int vxvy;
			Node cnode;

			bool done = false;

			Heap openqueue = new Heap(500000, HeapDirection.LowPriority);

			//Node Array
			Node[,] ng = new Node[this.map.SizeX, this.map.SizeY];

			Node enode = new Node(dest.X, dest.Y, false, false, null, 0, 0);
			Node snode = new Node(start.X, start.Y, false, true, null, 0, Distance.DiagShortcut(dest, start)*this.patherconfig.Factor);

			ng[snode.X, snode.Y] = snode;

			openqueue.Add(new HeapNode(snode, snode.F));

			while(!done)
			{
				//Game.Print("In loop");
				HeapNode tn = openqueue.Remove();
				if(tn == null)
					break;
				node = (Node)tn.Item;

				if(node.X == enode.X && node.Y == enode.Y) 
				{   
					done = true;
					this.LastScore = node.F;
					//if(_reduc == 99)
					//	return node.f;

					//BUILD PATH USING REFRENCED PARENTS
					//var donebuild = false;

					ArrayList ptd = new ArrayList();
					ArrayList fp = new ArrayList();
					ptd.Add(node);
					if (((Node)ptd[ptd.Count-1]).Parent != null) 
					{
						do 
						{
							ptd.Add(((Node)ptd[ptd.Count-1]).Parent);
							if (((Node)ptd[ptd.Count-1]).Parent == null)
								break;
						} while (true);
					}

					//Adding padding
					for (int p = 0; p<ptd.Count; p++)
					{
						for (int px = -1; px < 2; px++) 
						{
							for (int py = -1; py < 2; py++) 
							{
								if((px*py) != 0 && (px != 0 && py != 0)) continue; //continue if diagonal or same coordinate
								if(!this.map.IsWalkable(((Node)ptd[p]).X + px + this.map.X, ((Node)ptd[p]).Y + py + this.map.Y)) 
								{
									((Node)ptd[p]).X += (px*(-1));  // changed ((Node)ptd[p]).Y to ((Node)ptd[p]).X
									((Node)ptd[p]).Y += (py*(-1));
								}
							}
						}
					}
					
					//reverse the path now so we can work with it from start and reduce the points
					double vecanglelast = 0;
					double vecanglenew = 0;
					double vecdistance = 0;
					for (int d=ptd.Count-1; d>=0; d--) 
					{
						if (d == ptd.Count-1 && d > 0) 
						{		//add first point always
							fp.Add(ptd[d]);
							if(this.patherconfig.ReductionType == Reduction.WalkingReduction) 
								vecanglelast = Distance.GetAngle(((Node)fp[fp.Count-1]).X, ((Node)fp[fp.Count-1]).Y, 
											((Node)ptd[d-1]).X, ((Node)ptd[d-1]).Y);
							else vecanglelast = 0;
							continue;
						}

						if (d == 0) 
						{				//add last point always
							fp.Add(ptd[d]);
							break;
						}

						if(this.patherconfig.ReductionType == Reduction.WalkingReduction)	vecanglenew = Distance.GetAngle(((Node)fp[fp.Count-1]).X, ((Node)fp[fp.Count-1]).Y, ((Node)ptd[d]).X, ((Node)ptd[d]).Y);
						else vecanglenew = 0;
						vecdistance = Distance.Euclidian(((Node)fp[fp.Count-1]).X, ((Node)fp[fp.Count-1]).Y, ((Node)ptd[d]).X, ((Node)ptd[d]).Y);

						if(vecanglenew != vecanglelast || vecdistance > this.patherconfig.PathPointDistance) 
						{
							fp.Add(ptd[d]);
							if(this.patherconfig.ReductionType == Reduction.WalkingReduction)	
								vecanglelast = Distance.GetAngle(((Node)fp[fp.Count-1]).X, ((Node)fp[fp.Count-1]).Y, ((Node)ptd[d-1]).X, ((Node)ptd[d-1]).Y);
							else vecanglelast = 0;
							continue;
						}
					}
					this.path = new Path();
					//Put the offset back in and move to path
					for (int d = 0; d<fp.Count; d++)
						this.path.CoordinateList.Add(new System.Drawing.Point(((Node)fp[d]).X + this.map.X, ((Node)fp[d]).Y + this.map.Y));
					//				print("OUT mlmap FindPath");
					return this.path;
				}

				else 
				{  		// look for adjacent blocks that we attach to and add them to open
					for(int vy = -1; vy < 2; vy++) 
					{
						for(int vx=-1; vx < 2; vx++)	
						{
							if(vx == 0 && vy == 0) continue; //continue if we are on the current node
							cx = node.X+vx; cy = node.Y+vy;
							//Game.Print("cx, cy: " + cx.ToString() + ", " + cy.ToString());
							vxvy = vx*vy;
							//check for map edge
							if(cy < 0 || cy > this.map.SizeY-1 || cx < 0 || cx > this.map.SizeX-1) continue;

							//check for walkability and small diagonal gaps that cant be passed
							if ((this.map.CollisionData[cx, cy] & 1) > 0) continue;
							//CHANGED 02-10-2004 as a test (commented out extra checks)

							if (vxvy != 0 && ((this.map.CollisionData[node.X, cy] & 1) > 0) 
								&& ((this.map.CollisionData[cx, node.Y] & 1) > 0)) continue;
							//if ((AreaData[cy][cx+1] & 1) || (AreaData[cy][cx-1] & 1) ||
							//	(AreaData[cy+1][cx] & 1) || (AreaData[cy-1][cx] & 1)) continue;
							//if (((AreaData[cy][cx+1] & 1) && (AreaData[cy][cx-1] & 1)) ||
							//	((AreaData[cy+1][cx] & 1) && (AreaData[cy-1][cx] & 1))) continue;

							newg = node.G + SCORE[Math.Abs(vxvy)];

							cnode = ng[cx, cy];

							if(cnode == null) 
							{
								cnode = new Node(cx,cy,false,false,node,newg,Distance.DiagShortcut(dest.X, dest.Y, cx, cy)*this.patherconfig.Factor);
								ng[cx, cy] = cnode;
							}
							else 
							{
								if (cnode.G > newg)
								{
									cnode.IsClosed = false;
									cnode.G = newg;
									cnode.Parent = node;
								}
								else continue;
							}

							if(!cnode.IsOpen) 
							{
								cnode.IsOpen = true;
								openqueue.Add(new HeapNode(cnode, cnode.F));
								//AreaData[cnode.y][cnode.x] |= 0x200000;
							}
						}
					}
					node.IsOpen = false;	node.IsClosed = true;
					//AreaData[node.y][node.x] |= 0x100000;
				}


			}

			throw new ApplicationException("Could not find a path to destination");
		}

		/// <summary>
		/// Will find a path to the given Level
		/// </summary>
		/// <returns>A Path</returns>
		public Path FindPathToLevel()
		{
			throw new NotImplementedException("Method not implemented");
		}
	}

	/// <summary>
	/// Defines the Reduction Type
	/// </summary>
	public enum Reduction
	{
		/// <summary>
		/// Used to define Teleportation Reduction
		/// </summary>
		TeleportReduction,
		/// <summary>
		/// Used to define Walking Reduction
		/// </summary>
		WalkingReduction
	}

	/// <summary>
	/// Defines the Various Forward Heuristics
	/// Only one is currently used in pathing and cant be changed at this time.
	/// Diagonal Shortcut is the one.
	/// </summary>
	public enum Heuristic
	{
		/// <summary>
		/// Returns the distance of either the Y differnce or just the X differnce, whichever is greater.
		/// </summary>
		MaxDXDY,
		/// <summary>
		/// Standard Euclidian Distance
		/// </summary>
		Euclidian,
		/// <summary>
		/// The only one implemented in the Pathing Engine
		/// </summary>
		DiagonalShortcut,
		/// <summary>
		/// Standard Manhattan which is dIfference in X plus difference in Y
		/// </summary>
		ManHattan,
		/// <summary>
		/// No Heuristic
		/// </summary>
		None
	}

}


