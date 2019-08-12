#include "botnet.h"
#include ".\recthook.h"
#include ".\d2exports.h"
#include ".\d2gfx.h"


namespace botNET
{
	namespace Drawing
	{

		RectHook::RectHook(int xPos, int yPos, int w, int h) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			this->_size = System::Drawing::Size(w, h);
		}

		RectHook::RectHook(int xPos, int yPos, int w, int h, int col, ScreenHookTransparency trans) : ScreenHook(xPos, yPos, col, trans)
		{
			this->_size = System::Drawing::Size(w, h);
		}

		RectHook::RectHook(int xPos, int yPos, int w, int h, bool Exposed) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			this->_size = System::Drawing::Size(w, h);
			this->Exposed = Exposed;
		}

		RectHook::RectHook(int xPos, int yPos, int w, int h, int col, ScreenHookTransparency trans, bool Exposed) : ScreenHook(xPos, yPos, col, trans)
		{
			this->_size = System::Drawing::Size(w, h);
			this->Exposed = Exposed;
		}

		RectHook::~RectHook(void)
		{
		}

		void RectHook::set_Width(int value)
		{
			this->_size.Width = value;
		}

		void RectHook::set_Height(int value)
		{
			this->_size.Height = value;
		}

		void RectHook::set_Size(System::Drawing::Size value)
		{
			this->_size = value;
		}

		void RectHook::Draw()
		{
			__super::Draw();
			D2GFX::DrawRectangle(this->_point.X, this->_point.Y, 
				this->_point.X + this->_size.Width, this->_point.Y + this->_size.Height, color, transparency);
		}

		void RectHook::Draw(int x, int y, int width, int height, int colour, int transparency)
		{
			D2GFX::DrawRectangle(x, y, width, height, colour, transparency);
		}
	}


}
