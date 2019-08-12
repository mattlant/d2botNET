#ifndef HOTSPOT_H
#define HOTSPOT_H

#include "screenhook.h"

namespace botNET
{
	namespace Drawing
	{

		///<summary>
		/// The RectHook class lets you create and display rectangles of varying colour and transpoarency on the screen.
		///</summary>
		__gc public class HotSpot : public ScreenHook
		{
		public:
			HotSpot(int x, int y, int w, int h);
			~HotSpot(void);
			void Draw(void);

			__property virtual bool	get_Outline();
			__property virtual void	set_Outline(bool);

			__property virtual void	set_Visible(bool);

			__property void set_Width(int value);
			__property void set_Height(int value);

			__property void set_Size(System::Drawing::Size value);

			bool outline;
			ScreenHook* LinkedHook;

		};
	}

}

#endif