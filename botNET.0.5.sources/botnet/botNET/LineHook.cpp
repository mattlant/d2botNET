#include "botnet.h"
#include ".\linehook.h"
#include "d2exports.h"
#include ".\d2gfx.h"


namespace botNET
{
	namespace Drawing
	{


		LineHook::LineHook(int xPos, int yPos, int xPos2, int yPos2, int color) : ScreenHook(xPos, yPos, color, (ScreenHookTransparency)1)
		{
			this->_point2 = System::Drawing::Point(xPos2, yPos2);
		}

		LineHook::LineHook(int xPos, int yPos, int xPos2, int yPos2, int color, bool Exposed) : ScreenHook(xPos, yPos, color, (ScreenHookTransparency)1)
		{
			this->_point2 = System::Drawing::Point(xPos2, yPos2);
			this->Exposed = Exposed;
		}

		LineHook::~LineHook(void)
		{
		}

		int LineHook::get_X2()
		{
			return this->_point2.X;
		}

		void LineHook::set_X2(int xPos2)
		{
			this->_point2.X = xPos2;
		}

		int LineHook::get_Y2()
		{
			return this->_point2.Y;
		}

		void LineHook::set_Y2(int yPos2)
		{
			this->_point2.Y = yPos2;
		}

		System::Drawing::Point LineHook::get_Point2()
		{
			return this->_point2;
		}

		void LineHook::set_Point2(System::Drawing::Point value)
		{
			this->_point2 = value;
		}

		void LineHook::Draw()
		{
			__super::Draw();
			D2GFX::DrawLine(this->_point.X, this->_point.Y, this->_point2.X, this->_point2.Y, color, 0);
		}

		void LineHook::Draw(int xPos, int yPos, int xPos2, int yPos2, int color)
		{
			D2GFX::DrawLine(xPos, yPos, xPos2, yPos2, color, 0);
		}

	}
}

