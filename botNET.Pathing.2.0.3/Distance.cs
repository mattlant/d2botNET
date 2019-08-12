using System;

using botNET.Mapping;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for Distance.
	/// </summary>
	public class Distance
	{

		/// <summary>
		/// Returns the Distance using the Manhattan Method
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static int Manhattan(int x1, int y1, int x2, int y2) 
		{
			return Math.Abs(x2-x1) + Math.Abs(y2-y1);
		}
		/// <summary>
		/// Returns the Distance using the Manhattan Method
		/// </summary>
		/// <param name="c1"></param>
		/// <param name="c2"></param>
		/// <returns></returns>
		public static int Manhattan(System.Drawing.Point c1, System.Drawing.Point c2) 
		{
			return Manhattan(c1.X, c1.Y, c2.X, c2.Y);
		}


		/// <summary>
		/// Returns the Distance using the Euclidian Method
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static int Euclidian(int x1, int y1, int x2, int y2) 
		{
			return (int)Math.Sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}

		/// <summary>
		/// Returns the Distance using the Euclidian Method
		/// </summary>
		/// <param name="c1"></param>
		/// <param name="c2"></param>
		/// <returns></returns>
		public static int Euclidian(System.Drawing.Point c1, System.Drawing.Point c2) 
		{
			return Manhattan(c1.X, c1.Y, c2.X, c2.Y);
		}


		/// <summary>
		/// Returns the Distance using the Euclidian Method with no Square Root
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static int EuclidianNoSqrt(int x1, int y1, int x2, int y2) 
		{
			return (int)Math.Floor((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}

		/// <summary>
		/// Returns the Distance using the Euclidian Method with no Square Root
		/// </summary>
		/// <param name="c1"></param>
		/// <param name="c2"></param>
		/// <returns></returns>
		public static int EuclidianNoSqrt(System.Drawing.Point c1, System.Drawing.Point c2) 
		{
			return EuclidianNoSqrt(c1.X, c1.Y, c2.X, c2.Y);
		}


		/// <summary>
		/// Returns the Distance using the Diagonal Shortcut Method. This offers best Measurement for Diablo Type games
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static int DiagShortcut(int x1, int y1, int x2, int y2) 
		{
			int dy = Math.Abs(y2-y1);
			int dx = Math.Abs(x2-x1);
			if (dy <= dx) return (int)(dy*0.414 + dx); else return (int)(dx*0.414 + dy);
		}

		/// <summary>
		/// Returns the Distance using the Diagonal Shortcut Method. This offers best Measurement for Diablo Type games
		/// </summary>
		/// <param name="c1"></param>
		/// <param name="c2"></param>
		/// <returns></returns>
		public static int DiagShortcut(System.Drawing.Point c1, System.Drawing.Point c2) 
		{
			return DiagShortcut(c1.X, c1.Y, c2.X, c2.Y);
		}


		/// <summary>
		/// Returns the Distance using the Maximum DxDy Method.
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static int MaxDxDy(int x1, int y1, int x2, int y2) 
		{
			int dy = Math.Abs(y2-y1);
			int dx = Math.Abs(x2-x1);
			return (dx>dy)?dx:dy;
		}

		/// <summary>
		/// Returns the Distance using the Maximum DxDy Method.
		/// </summary>
		/// <param name="c1"></param>
		/// <param name="c2"></param>
		/// <returns></returns>
		public static int MaxDxDy(System.Drawing.Point c1, System.Drawing.Point c2) 
		{
			return MaxDxDy(c1.X, c1.Y, c2.X, c2.Y);
		}

		/// <summary>
		/// Returns an angle
		/// </summary>
		/// <param name="x1"></param>
		/// <param name="y1"></param>
		/// <param name="x2"></param>
		/// <param name="y2"></param>
		/// <returns></returns>
		public static double GetAngle(double x1, double y1, double x2, double y2) 
		{
			return Math.Floor((Math.Atan2(y2-y1 , x2-x1)) * 180 / 3.1415);
		}

	}
}
