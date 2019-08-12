using System;
using System.Collections;

using botNET;
using botNET.Collections;

namespace BotOS
{
	/// <summary>
	/// The GoalBase class
	/// </summary>
	public class GoalBase
	{
		protected int mPriority;
		protected int mID;
		protected GoalBase mParent;
		protected Queue mSubGoals = new Queue();

		public GoalBase( GoalBase parent, int priority )
		{
			this.mParent = parent;
			this.mPriority = priority;
			this.mID = new Random().Next(int.MinValue, int.MaxValue);
		}

		public int ID
		{
			get { return mID; }
		}

		public GoalBase Parent
		{
			get { return mParent; }
		}

		public Queue SubGoals
		{
			get { return mSubGoals; }
		}

		public int Priority
		{
			get { return mPriority; }
		}

		/// <summary>
		/// </summary>
		public virtual TaskBase[] Tasks
		{
			get { return new TaskBase[0]; }
		}

		/// <summary>
		/// </summary>
		public virtual void Update()
		{
			foreach( GoalBase goal in mSubGoals )
			{
				goal.Update();
			}
		}
	}
}
