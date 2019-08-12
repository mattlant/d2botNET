#include "botnet.h"
#include ".\texthook.h"
#include "game.h"
#include <vcclr.h>
#include "d2win.h"
#include "settings.h"

namespace botNET
{
	namespace Drawing
	{
		TextHook::TextHook(int xPos, int yPos, String * sText) : ScreenHook(xPos, yPos, 0, (ScreenHookTransparency)0)
		{
			setup(sText, 0, 0);
		}

		TextHook::TextHook(int xPos, int yPos, String * sText, int iColor, int iFont) : ScreenHook(xPos, yPos, iColor, (ScreenHookTransparency)0)
		{
			setup(sText, iFont, 0);
		}

		TextHook::TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, int Align) : ScreenHook(xPos, yPos, iColor, (ScreenHookTransparency)0)
		{
			setup(sText, iFont, Align);
		}

		TextHook::TextHook(int xPos, int yPos, String * sText, bool Exposed) : ScreenHook(xPos, yPos, 0, (ScreenHookTransparency)0)
		{
			setup(sText, 0, 0);
			this->Exposed = Exposed;
		}

		TextHook::TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, bool Exposed) : ScreenHook(xPos, yPos, iColor, (ScreenHookTransparency)0)
		{
			setup(sText, iFont, 0);
			this->Exposed = Exposed;
		}

		TextHook::TextHook(int xPos, int yPos, String * sText, int iColor, int iFont, int Align, bool Exposed) : ScreenHook(xPos, yPos, iColor, (ScreenHookTransparency)0)
		{
			setup(sText, iFont, Align);
			this->Exposed = Exposed;
		}

		TextHook::TextHook(bool noadd, int xPos, int yPos, String * sText, int iColor, int iFont, int Align) : ScreenHook(xPos, yPos, iColor, (ScreenHookTransparency)0, noadd)
		{
			setup(sText, iFont, Align);
		}

		TextHook::~TextHook(void)
		{
		}

		void TextHook::setup(String * sText, int iFont, int iAlign)
		{
			font = iFont;
			align = Align;
			Text = sText;
		}

		int TextHook::get_Font() { return font; }
		void TextHook::set_Font(int value) 
		{ 
			wchar_t __pin* ptr_text = ::PtrToStringChars(this->_text);

			font = value;
			DWORD oldfont = D2WIN::SetTextHookFont(this->font);
			this->_size.Width = D2WIN::GetTextHookWidth(ptr_text);
			this->_size.Height = D2WIN::GetCurrentFontHeight();	
			D2WIN::SetTextHookFont(oldfont);
		}

		int TextHook::get_Align() { return align; }
		void TextHook::set_Align(int value) { align = value; }


		String * TextHook::get_Text() { return _text; }

		void TextHook::set_Text(String * value)
		{
			TextChangedEventArgs * e = new TextChangedEventArgs(value);
			RaiseTextHookTextChangedEvent(e);
			value = e->NewText;

			this->_text = value;

			wchar_t __pin* ptr_text = PtrToStringChars(this->_text);

			DWORD oldfont = D2WIN::SetTextHookFont(this->font);
			if(value->Length == 0)
				this->_size.Width = 0;
			else
				this->_size.Width = D2WIN::GetTextHookWidth(ptr_text);
			this->_size.Height = D2WIN::GetCurrentFontHeight();	
			D2WIN::SetTextHookFont(oldfont);
		}

		void TextHook::Draw()
		{
			//Do draw events by calling ScreenHook::Draw
			__super::Draw();
			//pin our pointer so GC doesnt move
			wchar_t __pin* ptr_text = PtrToStringChars(this->_text);
			//get old font, draw, then put back old font
			DWORD oldfont = D2WIN::SetTextHookFont(this->font);
			D2WIN::DrawTextHook(ptr_text, this->_point.X, this->_point.Y, color, 0);
			D2WIN::SetTextHookFont(oldfont);

		}

		void TextHook::Draw(String* text, int x, int y, int font, int colour)
		{
			wchar_t __pin* ptr_text = PtrToStringChars(text);
			//get old font, draw, then put back old font
			DWORD oldfont = D2WIN::SetTextHookFont(font);
			D2WIN::DrawTextHook(ptr_text, x, y, colour, 0);
			D2WIN::SetTextHookFont(oldfont);

		}

		void TextHook::RaiseTextHookTextChangedEvent(TextChangedEventArgs * e)
		{
			try{
				OnTextChanged(this, e);
			}
			catch (Exception * ex){ 
				if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a TextHookTextChangedEvent: " , ex->Message)); 
			}
		}

		void TextHook::Dispose(bool disposing)
		{
			if(!this->disposed)
			{
				try
				{
					if(disposing)
					{
					}
				}
				__finally
				{
					__super::Dispose(disposing);
					this->disposed = true;
				}
			}
		}
	}


}
