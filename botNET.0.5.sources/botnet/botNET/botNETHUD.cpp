#include "botnet.h"
#include "botnethud.h"
#include "screenhook.h"
#include "TextHook.h"
#include "RectHook.h"
#include "ImageHook.h"
#include "Game.h"
#include "d2client.h"
#include "d2win.h"
#include "d2gfx.h"
#include "d2gdi.h"
#include "settings.h"


namespace botNET
{
	namespace Drawing
	{

		botNETHUD::botNETHUD(void)
		{
			// HUD BG
			//imgHUD = new ImageHook(String::Concat(Game::WorkingDirectory, S"\\hud.bmp"), 105, 528, -1);
			//imgHUD->visible = false; 
			//imgHUD->Enabled = true;
			//imgHUD->ZOrder = 0;

			//// Time
			//imgTime = new ImageHook(String::Concat(Game::WorkingDirectory, S"\\time.bmp"), 512, 533, -1);
			//imgTime->visible = false;
			//imgTime->Enabled = true;
			//imgTime->ZOrder = 0;

			//// Ping
			//imgPing = new ImageHook(String::Concat(Game::WorkingDirectory, S"\\ping.bmp"), 145, 533, -1);
			//imgPing->visible = false;
			//imgPing->Enabled = true;
			//imgPing->ZOrder = 0;

			mLastPing = *D2CLIENT::Ping;
			mVersion = String::Concat(S"botNET v", Settings::gVersionString);

		}

		botNETHUD::~botNETHUD(void)
		{
		}

		void botNETHUD::Draw()
		{
			//CellContext img;
			//img.ptCellFileUnk = 0;
			//img.ptCellFile = imgHUD->image;
			//img.frame = 0;
			//img._3 = 0;
			//RECT rect;
			//rect.left = 0;
			//rect.top = 0;
			//rect.right = 0;
			//rect.bottom = 0; 
			//D2GFX::PrintImage(&img, this->_point.X, this->_point.Y + this->_size.Height, layer, 5, 0); 
			//D2GDI::DrawImage(&img, imgHUD->Point.X, imgHUD->Point.Y + imgHUD->Size.Height, -1, 5, 0);



			//Draw ping time text. 	((TextHook)sender).Text = Game.Ping + "ms";

			//Draw TIme text 	((TextHook)sender).Text = DateTime.Now.ToString("h:mm:ss tt");

			//TextHook::Draw(DateTime::Now.ToString(S"h:mm:ss tt"), 525, 546, 6, 4);
			//TextHook::Draw(String::Concat((*D2CLIENT::Ping).ToString(), "ms"), 149, 546, 6, 4);
			TextHook::Draw(mVersion, 355, 546, 6, 4);

			//if(*D2CLIENT::Ping != this->mLastPing)
			//{
			//	this->mLastPing = *D2CLIENT::Ping;
			//	//check each block;
			//	if(Game::Ping >= 0)
			//		RectHook::Draw(198, 537, 13, 10, 125, ScreenHookTransparency::None);
			//	if(Game::Ping > 75)
			//		RectHook::Draw(212, 537, 13, 10, 125, ScreenHookTransparency::None);
			//	if(Game::Ping > 200)
			//		RectHook::Draw(226, 537, 13, 10, 111, ScreenHookTransparency::None);
			//	if(Game::Ping > 400)
			//		RectHook::Draw(240, 537, 13, 10, 111, ScreenHookTransparency::None);
			//	if(Game::Ping > 600)
			//		RectHook::Draw(254, 537, 13, 10, 10, ScreenHookTransparency::None);
			//	if(Game::Ping > 1000)
			//		RectHook::Draw(268, 537, 13, 10, 10, ScreenHookTransparency::None);
			//}
		}


	}
}
