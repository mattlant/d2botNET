#ifndef BOTNETHUD_H
#define BOTNETHUD_H

namespace botNET
{
	namespace Drawing
	{

		public __gc class ImageHook;

		private __gc class botNETHUD
		{
		public:
			botNETHUD(void);
			~botNETHUD(void);

			void Draw();

			static botNETHUD* mHUD;

		private:
			ImageHook* imgHUD;
			ImageHook* imgTime;
			ImageHook* imgPing;

			int mLastPing;
			String* mVersion;



		};
	}
}

#endif

/*
// HUD BG
ImageHook HUD = new ImageHook(Game.WorkingDirectory + "\\hud.bmp", 105, 553, -1);
HUD.ZOrder = 0;

// Time
ImageHook time = new ImageHook(Game.WorkingDirectory + "\\time.bmp", 512, 549, -1);
time.ZOrder = 0;

TextHook txtTime = new TextHook(525, 546, "Time", 4, 6);
txtTime.ZOrder = 1;
TextHook txtCurrentTime = new TextHook(580, 546, DateTime.Now.ToString("h:mm:ss tt"), 4, 6);
txtCurrentTime.ZOrder = 1;
txtCurrentTime.OnDraw += new OnDrawHandler(UpdateTime);

// Ping
ImageHook ping = new ImageHook(Game.WorkingDirectory + "\\ping.bmp", 145, 549, -1);
ping.ZOrder = 0;

TextHook txtPing = new TextHook(149, 546, "0ms", 4, 6);
txtPing.ZOrder = 1;
txtPing.OnDraw += new OnDrawHandler(PingUpdate);

RectHook [] PingBars = new RectHook [6];

int XStart = 198;
for(int i = 0; i < 6; i++)
{
	PingBars[i] = new RectHook(XStart + i*14, 537, 13, 10, ((i < 2)?125:((i < 4)?111:10)), botNET.Drawing.ScreenHookTransparency.Full, true);
	PingBars[i].ZOrder = 1;
	PingBars[i].OnDraw +=new OnDrawHandler(PingBarUpdate);
}

// Version Line
TextHook VersionLine = new TextHook(335, 548, "botNET v0.5.0.28", 4, 8);








private void UpdateTime(object sender, EventArgs e)
{
	((TextHook)sender).Text = DateTime.Now.ToString("h:mm:ss tt");
}

private void PingBarUpdate(object sender, EventArgs e)
{
	RectHook CurrentBlock = (RectHook)sender;
	switch(CurrentBlock.X)
	{
		case 198:
			if(Game.Ping > 0 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 0 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;

		case 212:
			if(Game.Ping > 75 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 75 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;

		case 226:
			if(Game.Ping > 200 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 200 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;

		case 240:
			if(Game.Ping > 400 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 400 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;

		case 254:
			if(Game.Ping > 600 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 600 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;

		case 268:
			if(Game.Ping > 1000 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.Full)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.None;
			else if(Game.Ping <= 1000 && CurrentBlock.Transparency == botNET.Drawing.ScreenHookTransparency.None)
				CurrentBlock.Transparency = botNET.Drawing.ScreenHookTransparency.Full;
			break;
	}
}

private void PingUpdate(object sender, EventArgs e)
{
	((TextHook)sender).Text = Game.Ping + "ms";
}
*/