using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace botNET.Loader
{
	/// <summary>
	/// Summary description for Loader.
	/// </summary>
	internal class Loader
	{
		///////////////////////////////////////////////////////////////////////

		[DllImport("botnet.loader.dll", CharSet=CharSet.Auto)]
		public static extern bool Go(IntPtr hProc, UInt32 BaseAddress, IntPtr HWnd);

		///////////////////////////////////////////////////////////////////////
	}
}
