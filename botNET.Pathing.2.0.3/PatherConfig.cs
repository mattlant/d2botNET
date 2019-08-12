using System;

using botNET.Mapping;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for PatherConfig.
	/// </summary>
	public class PatherConfig
	{
		/// <summary>
		/// Creates a PatherConfig object required for the Pather
		/// </summary>
		/// <param name="HeuristicType"></param>
		/// <param name="Factor"></param>
		/// <param name="PathPointDistance"></param>
		/// <param name="ReductionType"></param>
		public PatherConfig(Heuristic HeuristicType, double Factor, int PathPointDistance, Reduction ReductionType)
		{
			this.HeuristicType = HeuristicType;
			this.Factor = Factor;
			this.PathPointDistance = PathPointDistance;
			this.ReductionType = ReductionType;
		}

		/// <summary>
		/// Sets or Gets the Heuristic used. This is deprecated
		/// </summary>
		public Heuristic HeuristicType;
		/// <summary>
		/// Gets or Sets the Factor. Factor is a multiplier for the Hueristic
		/// </summary>
		public double Factor;
		/// <summary>
		/// Gets or Sets the Distance between each path point
		/// </summary>
		public int PathPointDistance;
		/// <summary>
		/// Gets or Sets the Reduction Type
		/// </summary>
		public Reduction ReductionType;

	}
}
