#ifndef RECTHOOK_H
#define RECTHOOK_H

#include "screenhook.h"

namespace botNET
{
	namespace Drawing
	{

		///<summary>
		/// The RectHook class lets you create and display rectangles of varying colour and transpoarency on the screen.
		///</summary>
		__gc public class RectHook : public ScreenHook
		{
		public:
			RectHook(int x, int y, int w, int h);
			RectHook(int x, int y, int w, int h, int col, ScreenHookTransparency trans);
			RectHook(int x, int y, int w, int h, bool Exposed);
			RectHook(int x, int y, int w, int h, int col, ScreenHookTransparency trans, bool Exposed);
			~RectHook(void);


			void Draw(void);
			static void Draw(int x, int y, int width, int height, int colour, int transparency);

			__property void set_Width(int value);

			__property void set_Height(int value);

			__property void set_Size(System::Drawing::Size value);

		};
	}

}

#endif