#ifndef LINEHOOK_H
#define LINEHOOK_H

#include "delegates.h"
#include "screenhook.h"

namespace botNET
{

	namespace Drawing
	{

		__gc public class LineHook : public ScreenHook
		{
		public:
			LineHook(int xPos, int yPos, int xPos2, int yPos2, int color);
			LineHook(int xPos, int yPos, int xPos2, int yPos2, int color, bool Exposed);
			~LineHook(void);

			void Draw(void);
			static void Draw(int xPos, int yPos, int xPos2, int yPos2, int color);

			__property int get_X2();
			__property void set_X2(int x2);

			__property int get_Y2();
			__property void set_Y2(int x2);

			__property System::Drawing::Point get_Point2();
			__property void set_Point2(System::Drawing::Point value);



		public private:

			System::Drawing::Point _point2;

		};
	}
}

#endif