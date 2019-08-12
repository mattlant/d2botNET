using System;
using System.Threading;

using botNET;
using botNET.Collections;

namespace BotOS
{
	/// <summary>
	/// Summary description for Core.
	/// </summary>
	public class Core
	{

		private static Heap gTasks;
		private static Heap gGoals;
		private static Heap gQuests;
		private static Heap gEvents;

		private System.Collections.Queue mErrors;

		private PluginManager mPlugins;

		public int CoreLoopDelay = 8;

		private bool done = false;

		private TaskBase mCurrentTask = null;
		private GoalBase mCurrentGoal = null;
		private QuestBase mCurrentQuest = null;

		private PersonalityBase mCurrentPersonality = null;

		/// <summary>
		/// If set to true, will quit if there are no tasks in any queues
		/// </summary>
		private bool notaskquit = false;

		public Core()
		{
			mErrors = new System.Collections.Queue();

			mPlugins = new PluginManager(this);
		}

		static Core()
		{
			gTasks = new Heap(5000, HeapDirection.LowHasPriority);
			gGoals = new Heap(5000, HeapDirection.LowHasPriority);
			gQuests = new Heap(5000, HeapDirection.LowHasPriority);
			gEvents = new Heap(5000, HeapDirection.LowHasPriority);
		}

		public Core(bool EndOnNoTasks)
		{
			notaskquit = EndOnNoTasks;
		}

		public static Heap Tasks
		{
			get { return gTasks; }
		}

		public static Heap Goals
		{
			get { return gGoals; }
		}

		public static Heap Quests
		{
			get { return gQuests; }
		}

		public System.Collections.Queue ErrorQueue
		{
			get { return mErrors; }
		}

		public PluginManager Plugins
		{
			get { return mPlugins; }
		}

		public TaskBase CurrentTask
		{
			get { return mCurrentTask ; }
		}

		public GoalBase CurrentGoal
		{
			get { return mCurrentGoal ; }
		}

		public QuestBase CurrentQuest
		{
			get { return mCurrentQuest ; }
		}

		public PersonalityBase CurrentPersonality
		{
			get { return mCurrentPersonality; }
		}

		public void Start()
		{

			HeapNode node = null;

			//main loop
			while(!done)
			{
				//calc delay
				Thread.Sleep(this.CoreLoopDelay);
				//TODO: Add in dynamic delay calculations


				//Mode checking
				//these are uninterruptable modes and should never be interrupted, or we risk C/I, etc
//				if(Me.Mode == 7 || Me.Mode == 8 || (Me.Mode > 9 && Me.Mode < 19)) continue;  // uncomment later

				//TODO: Add in A BAD TASK LIST, IT BASICALLY LOOKS FOR TASKS  that should not execute according to ID
				//TODO: Possibly add in condition to the tasks, like in BotOS.d2jsp (see coremanager.d2l)

				//Any errors?
				//TODO: Add error processing here
				//REMARKS: If an error is found here, remove all the tasks on the tasks heap that are owned by current
				//         goal, then let the goal regenerate a list of tasks.

				//Any events?
				if((node = gEvents.Remove()) != null)
				{
					// pass event to mCurrentTask
					// pass event to mCurrentGoal
					// pass event to mCurrentQuest

					TaskBase[] newtasks = mCurrentPersonality.React( (EventBase)node.Item );
				}

				//Any tasks?
				if((node = gTasks.Remove()) != null)
				{
					mCurrentTask = (TaskBase)node.Item;
					mCurrentTask.Execute();
				}
				//Any goals?
				else if((node = gGoals.Remove()) != null)
				{
					// get the next goal off the heap
					GoalBase goal = (GoalBase)node.Item;
					goal.Update(); // update the goal - this propagates to children

					// get the leaf goal
					while( goal.SubGoals.Count > 0 && ((GoalBase)goal.SubGoals.Peek()).SubGoals.Count > 0 )
					{
						goal = (GoalBase)goal.SubGoals.Peek();
					}
					if( goal.SubGoals.Count > 0 )
					{
						mCurrentGoal = (GoalBase)goal.SubGoals.Dequeue();

						// this goal isn't finished yet, add to Goal heap
						gGoals.Add( node );
					}
					else
					{
						mCurrentGoal = goal;
					}

					// add this goals tasks to Task heap
					TaskBase[] newtasks = mCurrentGoal.Tasks;
					for( int i = 0; i < newtasks.Length; i++ )
					{
						gTasks.Add( new HeapNode( newtasks[i], newtasks[i].Priority ) );
					}
				}
				//Any quests?
				else if((node = gQuests.Remove()) != null)
				{
					mCurrentQuest = (QuestBase)node.Item;
					GoalBase[] newgoals = mCurrentQuest.Goals;
					for( int i = 0; i < newgoals.Length; i++ )
					{
						gGoals.Add( new HeapNode( newgoals[i], newgoals[i].Priority ) );
					}
				}

				//end loop if no more tasks
				if(this.notaskquit)
					break;

			}
		}
	}
}
