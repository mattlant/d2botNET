#ifndef IMAGEHOOK_H
#define IMAGEHOOK_H

#include "screenhook.h"
#include "definitions.h"

namespace botNET
{
	namespace Drawing
	{

		///<summary>
		/// The imageHook class lets you create and display images from the Diablo II Gloabal\UI mpq directory.
		/// Future version should allow for loading external images.
		///</summary>
		__gc public class ImageHook : public ScreenHook
		{
		public:

			///<summary>
			/// Instantiates a new ImageHook.
			///</summary>
			ImageHook(String * ImageName, int xPos, int yPos);

			///<summary>
			/// Instantiates a new ImageHook.
			///</summary>
			ImageHook(String * ImageName, int xPos, int yPos, int Layer);

			///<summary>
			/// Instantiates a new ImageHook.
			///</summary>
			ImageHook(String * ImageName, int xPos, int yPos, int Layer, bool IsAnimated);

			///<summary>
			/// Instantiates a new ImageHook.
			///</summary>
			ImageHook(String * ImageName, int xPos, int yPos, int Layer, bool IsAnimated, bool Exposed);

			~ImageHook(void);

			///<summary>
			/// Draws the ImageHook to the screen. This is an operation that will only display the Hook until the next time the screen is drawn, 
			/// so if you are managing you own ImageHooks, you will need to Draw every Game.OnDrawEvent.
			///</summary>
			///<remarks>
			/// By default, ImageHooks are managed by the core and drawn by the core.
			///</remarks>
			void Draw(void);



		public private:
			CellFile * image;
			char frameskip;
			char framespeed;
			bool animated;
			long frame;
			char layer;
			//bool localimage;
			String * imagename;

		};
	}
}

#endif