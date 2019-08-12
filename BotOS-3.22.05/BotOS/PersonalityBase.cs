using System;

using botNET;
using botNET.Collections;

namespace BotOS
{
	/// <summary>
	/// Controls the personality of the bot.  Can make personality ChickenShit, Hero, SingleMinded or more.
	/// </summary>
	/// <remarks>
	/// This is also where potioning, chickening and other services like this should be performed.
	/// Maybe event item pickup?  Just look for the event in React() and depending on what it is
	/// push new tasks on the Heap.
	/// </remarks>
	public class PersonalityBase
	{
		public PersonalityBase()
		{
		}

		public virtual TaskBase[] React( EventBase Event )
		{
			throw new NotImplementedException("Function must be implemented.");
		}

	}
}
