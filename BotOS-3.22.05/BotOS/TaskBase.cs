using System;

using botNET;
using botNET.Collections;

namespace BotOS
{
	/// <summary>
	/// The TaskBase class is the only base class that all Tasks/Goals/Queues inherit from.
	/// </summary>
	public class TaskBase
	{
		protected int mPriority;
		protected int mID;
		protected GoalBase mParent;

		public TaskBase( GoalBase parent, int priority )
		{
			mParent = parent;
			mPriority = priority;
			mID = new Random().Next(int.MinValue, int.MaxValue);
		}

		public int ID
		{
			get { return mID; }
		}

		public GoalBase Parent
		{
			get { return mParent; }
		}

		public int Priority
		{
			get { return mPriority; }
		}

		public virtual bool Completed
		{
			get { return false; }
		}

		public virtual void Execute()
		{
			throw new NotImplementedException("Function must be implemented.");
		}

		protected void Insert(Heap QueueToInsertTo)
		{
			lock(QueueToInsertTo)
			{
				QueueToInsertTo.Add(new HeapNode(this, this.mPriority));
			}
		}

	}
}
