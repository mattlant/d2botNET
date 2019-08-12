using System;
using System.Collections;

using botNET;
using botNET.Collections;

namespace BotOS
{
	/// <summary>
	/// The QuestBase class
	/// </summary>
	public class QuestBase
	{
		protected int priority;
		protected int id;
		protected object data;
		protected int function;
		protected Queue goals;

		public QuestBase(int Priority, int Function, object Data)
		{
			this.priority = Priority;
			this.data = Data;
			this.id = new Random().Next(int.MinValue, int.MaxValue);
			this.function = Function;

			Refresh();
		}

		public int ID
		{
			get { return id; }
		}
/*
		public Queue Goals
		{
			get { return goals; }
		}
*/
		public int Priority
		{
			get { return priority; }
		}

		public virtual bool Completed
		{
			get { return true; } // maybe return true when all subgoals are completed
		}

		/// <summary>
		/// </summary>
		public virtual GoalBase[] Goals
		{
			get { return new GoalBase[0]; }
		}

		/// <summary>
		/// Refreshes the internal goals.  Will rebuild if out of sync.
		/// </summary>
		public virtual void Refresh()
		{
		}
	}
}
