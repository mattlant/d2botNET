#include "botnet.h"
#include ".\hotspot.h"
#include ".\d2exports.h"
#include ".\d2gfx.h"


namespace botNET
{
	namespace Drawing
	{

		HotSpot::HotSpot(int xPos, int yPos, int w, int h) : ScreenHook(xPos, yPos, 0xFF, (ScreenHookTransparency)1)
		{
			this->_size = System::Drawing::Size(w, h);
			this->outline = false;
		}

		HotSpot::~HotSpot(void)
		{
		}

		//only override Set since we dont want default adding/removing teh draw event and no setting either
		void HotSpot::set_Visible(bool value)	
		{ 
		}

		void HotSpot::set_Outline(bool value)	
		{ 
			this->outline = value;
		}

		bool HotSpot::get_Outline()	
		{ 
			return this->outline;
		}

		void HotSpot::set_Width(int value)
		{
			this->_size.Width = value;
		}

		void HotSpot::set_Height(int value)
		{
			this->_size.Height = value;
		}

		void HotSpot::set_Size(System::Drawing::Size value)
		{
			this->_size = value;
		}

		void HotSpot::Draw()
		{
			if(this->outline)
			{
				D2GFX::DrawLine(this->_point.X, this->_point.Y, this->_point.X+this->_size.Width, this->_point.Y, color, 0);
				D2GFX::DrawLine(this->_point.X, this->_point.Y, this->_point.X, this->_point.Y+this->_size.Height, color, 0);
				D2GFX::DrawLine(this->_point.X+this->_size.Width, this->_point.Y, this->_point.X+this->_size.Width, this->_point.Y+this->_size.Height, color, 0);
				D2GFX::DrawLine(this->_point.X, this->_point.Y+this->_size.Height, this->_point.X+this->_size.Width, this->_point.Y+this->_size.Height, color, 0);
				//TODO: draw outline
			}
			__super::Draw();
		}
	}


}
