using System;

namespace BotOS
{
	/// <summary>
	/// Summary description for Plugin.
	/// </summary>
	public abstract class PluginBase
	{
		protected string name;
		protected string author;
		protected UInt32 instanceid;
		protected string version;
		protected PluginTiming timingmethod;
		protected UInt32 timing;

		//These may never be used
		protected string classname;
		protected string assemblyname;

		internal bool enabled;
		internal DateTime lasttime;
		internal UInt32 loopcount;

		//reference to our Core we run in
		protected Core core;

		public PluginBase()
		{
			this.enabled = true;
			this.lasttime = DateTime.Now;
			this.loopcount = 0;
		}

		public PluginBase(string Name, string Author, UInt32 InstanceID, string Version, PluginTiming TimingMethod, UInt32 Timing, Core BotOSCore) : this()
		{
			this.name = Name;
			this.author = Author;
			this.instanceid = InstanceID;
			this.version = Version;
			this.timingmethod = TimingMethod;
			this.timing = Timing;
			this.core = BotOSCore;
		}

		/// <summary>
		/// Gets the name of the plugin.
		/// </summary>
		string Name { get { return name; } }

		/// <summary>
		/// Gets the name of the author who wrote the plugin
		/// </summary>
		string Author { get { return author; } }

		/// <summary>
		/// Gets the instance ID of the plugin. Usefull for tracking multiple instances of the same plugin
		/// </summary>
		UInt32 InstanceID { get { return instanceid; } }

		/// <summary>
		/// Gets the version of the plugin
		/// </summary>
		string Version { get { return version; } }

		/// <summary>
		/// Gets the Timing Method of the plugin
		/// </summary>
		PluginTiming TimingMethod { get { return timingmethod; } }

		/// <summary>
		/// Gets the Timing value. This value is in milliseconds.
		/// </summary>
		UInt32 Timing { get { return timing; } }

		/// <summary>
		/// Gets or Sets a value indicating if this plugin is enabled, aka, should be executed.
		/// </summary>
		bool Enabled { get { return enabled; } set { enabled = value; } }

		//This functionmust be overrridden if using ByTime or ByLoops method. 
		public virtual void Execute()
		{
			throw new NotImplementedException("Function must be implemented.");
		}

		public virtual void OnLoad()
		{
			throw new NotImplementedException("Function must be implemented.");
		}

		public virtual void OnUnload()
		{
			throw new NotImplementedException("Function must be implemented.");
		}


	}

	public enum PluginTiming
	{
		ByLoop,
		ByTime,
		NoExecute
	}


}
