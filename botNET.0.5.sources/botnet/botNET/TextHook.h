#ifndef TEXTHOOK_H
#define TEXTHOOK_H

#include "delegates.h"

#include "screenhook.h"

namespace botNET
{
	namespace Drawing
	{

		///<summary>
		/// The TextHook class lets you create and display text on the Diablo II screen.
		///</summary>
		__gc public class TextHook : public ScreenHook
		{
		public:
			TextHook(int xPos, int yPos, String * sText);
			TextHook(int xPos, int yPos, String * sText, int iColor, int iFont);
			TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, int Align);
			TextHook(int xPos, int yPos, String * sText, bool Exposed);
			TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, bool Exposed);
			TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, int Align, bool Exposed);
			TextHook(bool noadd, int xPos, int yPos, String * sText, int iColor, int iFont, int Align);
			~TextHook(void);

			///<summary>
			/// Gets or Sets the Text that the TextHook displays.
			///</summary>
			__property String * get_Text();
			__property void set_Text(String * value);

			///<summary>
			/// Gets or Sets the Font used by the TextHook.
			///</summary>
			__property int get_Font();
			__property void set_Font(int value);

			///<summary>
			/// Gets or Sets the Alignment of the TextHook
			///</summary>
			///<remarks> Through some experimenting, I am unsure that this has much effect. 
			/// If someone discovers exactly how this affects the output, please make a post on http://forums.d2botnet.com/ </remarks>
			__property int get_Align();
			__property void set_Align(int value);

			///<summary>
			/// Renders the TextHook to screen. You usually will not have to Draw manually, unless you are managing ScreenHook on your own
			///</summary>
			void Draw();
			static void Draw(String* text, int x, int y, int font, int colour);

			//Static Event Handler stuff
			__event OnTextChangedHandler * OnTextChanged;
			void RaiseTextHookTextChangedEvent(TextChangedEventArgs * e);



		protected:
			void setup(String * sText, int iFont, int Align);

			virtual void Dispose(bool diposing);

			int align;
			int font;
			String* _text;
		};
	}

}
#endif