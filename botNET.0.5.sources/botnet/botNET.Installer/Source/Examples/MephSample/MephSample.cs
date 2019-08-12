using System;
using System.Collections;
using System.Threading;

using botNET;

using botNET.Mapping;
using botNET.Pathing;
using botNET.Units;

namespace botNET
{

	[LoadableAttribute] 
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class Bot : ILoadable
	{

		public Bot()
		{
		}

		public static void MoveToDurance2()
		{
			PC me = new PC();

			AreaMap map = new AreaMap(me.Area);
			map.Initialize();

			Pather p = new Pather(map, new WalkingReducer(5, 13));

			p.FindPathToWaypoint(me.Position);

			Pathing.Mover m = new Pathing.Mover(p);
			m.Move(Reduction.WalkingReduction);

			GameObject waypoint = new GameObject(p.LastPresetUsed);

			Game.Print("About to click the WP");
			me.Interact(waypoint);
			while(!Game.GetUIState(UIState.WaypointPanel))	{	Thread.Sleep(50);	}

			waypoint.Interact(AreaLevel.DuranceOfHateLevel2);

			while(me.Area != AreaLevel.DuranceOfHateLevel2)
			{
				Thread.Sleep(100);
			}
			//Thread.Sleep(50000); //init delay


		}

		public static void MoveToDurance3()
		{
			PC me = new PC();

			AreaMap map = new AreaMap(me.Area);
			map.Initialize();

			Pather p = me.GetSkillLevel(SkillType.Teleport) > 0 ? new Pather(map, new TeleportReducer(25)) : p = new Pather(map, new WalkingReducer(7, 13));

			p.FindPathToWarp(me.Position, new int[] {67, 68}, me.Area);

			Pathing.Mover m = new Pathing.Mover(p);
			m.OnMoverCallBack +=new botNET.Pathing.Mover.MoverCallBackHandler(m_OnMoverCallBack);
			m.Move(me.GetSkillLevel(SkillType.Teleport) > 0 ? Reduction.TeleportReduction : Reduction.WalkingReduction);

			Warp warp = new Warp(p.LastPresetUsed);

			Thread.Sleep(200);

			me.Interact(warp);

			Thread.Sleep(200);

			while(me.Area != (AreaLevel)102)
			{
				me.ClickMap(ClickType.LeftDown, false, warp);
				Thread.Sleep(100);
				me.ClickMap(ClickType.LeftUp, false, warp);
				Thread.Sleep(500);
			}

			return;
		}

		public static void MoveTomephisto()
		{
			PC me = new PC();

			AreaMap map = new AreaMap(me.Area);
			map.Initialize();

			Pather p = me.GetSkillLevel(SkillType.Teleport) > 0 ? new Pather(map, new TeleportReducer(25)) : p = new Pather(map, new WalkingReducer(7, 13));

			p.FindPath(me.Position, new System.Drawing.Point(17564, 8069));

			Pathing.Mover m = new Pathing.Mover(p);

			m.Move(me.GetSkillLevel(SkillType.Teleport) > 0 ? Reduction.TeleportReduction : Reduction.WalkingReduction);
		}


		public void Dispose()
		{
			// TODO:  Add Bot.Dispose implementation
		}


		public void UserStop()
		{
			// TODO:  Add Bot.UserStop implementation
		}

		public void EndGame(TimeSpan GameLength)
		{
			// TODO:  Add Bot.EndGame implementation
		}

		public void UserStart()
		{
			// TODO:  Add Bot.UserStart implementation
			NewGame();
		}

		public void Load()
		{
			// TODO:  Add Bot.Load implementation
			if(Game.IsInGame)
				Game.Print("mephisto sample loaded");
		}

		public void UserCommand(string command, string[] args)
		{
		}

		public void NewGame()
		{

			PC me = new PC();

			try
			{
				Game.Print("botNET mephisto Assembly");
				Game.Print("Based off code from sh-demon's d2bs mephisto script");
				Thread.Sleep(2000);

				if(me.IsInTown)
					MoveToDurance2();

				if(me.Area == AreaLevel.DuranceOfHateLevel2)
					MoveToDurance3();

				if(me.Area == AreaLevel.DuranceOfHateLevel3)
					MoveTomephisto();

			}

			catch(Exception ex) 
			{
				//messageBox.Show(ex.StackTrace);
				Game.Print(ex);
				//System.Windows.Forms.messageBox.Show(ex.message + "\r\n" + ex.StackTrace);
			
			}
		}

		private static void m_OnMoverCallBack(MoverEventArgs e)
		{

		}

		public void ReceiveMessage(long SenderID, int MessageType, object Data)
		{
			// TODO:  Add Bot.ReceiveMessage implementation
		}

	}

	public class Mover
	{

		public static void Move(int x, int y)
		{
			PC me = new PC();
			while((Math.Abs(me.X - x) > 4 || Math.Abs(me.Y - y) > 4)) 
			{ 
				while(me.RightSkill != SkillType.Teleport && me.GetSkillLevel(SkillType.Teleport) > 0)
				{
					me.RightSkill = SkillType.Teleport;
					Thread.Sleep(500);
				}

				int click = 3;
				if(me.IsInTown || me.GetSkillLevel(SkillType.Teleport) == 0)
					click = 0;
				me.ClickMap((ClickType)click, false, x, y);
				Thread.Sleep(100);
				me.ClickMap((ClickType)(click + 2), false, x, y);
				Thread.Sleep(100); 
			} 
		}

		public static void Interact(UnitBase u)
		{
			
			PC me = new PC();

			me.ClickMap(ClickType.LeftDown, false, u);
			Thread.Sleep(100);
			me.ClickMap(ClickType.LeftUp, false, u);
		}



	}





}
