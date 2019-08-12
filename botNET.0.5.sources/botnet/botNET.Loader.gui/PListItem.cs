using System;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace botNET.Loader
{
	/// <summary>
	/// Summary description for PListItem.
	/// </summary>
	public class PListItem
	{
		private Process _p;
		public PListItem(Process p)
		{
			_p = p;
		}

		public override string ToString()
		{
			return _p.MainWindowTitle;
		}

		public Process Proc
		{
			get
			{
				return _p;
			}
		}



	}
}
