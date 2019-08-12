using System;
using System.Collections;
using System.IO;

namespace BotOS
{
	/// <summary>
	/// Summary description for PluginManager.
	/// </summary>
	public class PluginManager
	{
		private Core core;
		private ArrayList plugins;

		public PluginManager(Core BotOSCore)
		{
			this.core = BotOSCore;
			this.plugins = new ArrayList();
		}

		public void LoadAll()
		{
		}

		public void Load(string assembly, string Name)
		{
			//pass this.core to the plugins

		}

		internal void ExecuteAll()
		{
		}

		public void Execute(string Name)
		{
		}

		public void Execute(string Name, UInt32 InstanceID)
		{
		}

		private byte[] ReadFile(String filename)
		{
			FileStream fs = File.OpenRead(filename);
			byte[] buffer = new byte[fs.Length];

//			fs.Read(buffer, 0, fs.Length);
//			fs.Close();

			return buffer;
		}


	}
}
