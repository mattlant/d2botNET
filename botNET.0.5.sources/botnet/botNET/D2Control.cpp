#include "botnet.h"
#include ".\d2control.h"
#include "limits.h"
#include "Game.h"
#include "d2gfx.h"
#include "d2win.h"

#include "definitions.h"


namespace botNET
{
	namespace OutOfGame
	{


		D2Control::D2Control(ButtonAttrib * Control)
		{
			this->control = Control;
		}

		D2Control::~D2Control(void)
		{
		}

		D2Control * D2Control::Get()[]{
		
			ArrayList * ar = new ArrayList();
			ButtonAttrib * temp = *D2WIN::ptFirstButton;
			if(temp)
			{
				do
				{
					ar->Add(new D2Control(temp));

				}while(temp = temp->ptNext);
			}

			if(ar->Count > 0)
			{
				D2Control * ctls __gc[] = new D2Control * [ar->Count];
				ar->CopyTo(ctls);
				return ctls;
			}
			else
				return new D2Control * [0];

		}

		// Get control by matching name, names are matched if the control starts with
		//	the passed in string
		D2Control* D2Control::Get( String* name)[]{
		
			ArrayList*		a = new ArrayList();
			ButtonAttrib *	ba = *D2WIN::ptFirstButton;
			D2Control*		control;
			String*			cName;
			
			while( ba){
				control = new D2Control( ba);
				cName = control->get_Text();
				
				if( cName->StartsWith( name)){
					a->Add( new D2Control( ba));
				}
				ba = ba->ptNext;
			}

			if( a->Count > 0){
				D2Control* c __gc[] = new D2Control* [a->Count];
				a->CopyTo( c);
				return c;
			}

			return new D2Control* [0];
		}

		// Get control by matching name and type. Names are matched if the control starts with
		//	the passed in string.
		D2Control* D2Control::Get( String* name, ControlType type)[]{
		
			ArrayList*		a = new ArrayList();
			ButtonAttrib *	ba = *D2WIN::ptFirstButton;
			D2Control*		control;
			String*			cName;
			
			while( ba){
				control = new D2Control( ba);
				cName = control->get_Text();
				
				if( cName->StartsWith( name) && control->get_Type() == type){
					a->Add( new D2Control( ba));
				}
				ba = ba->ptNext;
			}

			if( a->Count > 0){
				D2Control* c __gc[] = new D2Control* [a->Count];
				a->CopyTo( c);
				return c;
			}

			return new D2Control* [0];
		}

		// Match controls based upon position
		D2Control* D2Control::Get( int x, int y)[]{
		
			ArrayList*		a = new ArrayList();
			ButtonAttrib *	ba = *D2WIN::ptFirstButton;
			D2Control*		control;
			
			while( ba){
				control = new D2Control( ba);
				
				if( control->get_X() == x && control->get_Y() == y){
					a->Add( new D2Control( ba));
				}
				ba = ba->ptNext;
			}

			if( a->Count > 0){
				D2Control* c __gc[] = new D2Control* [a->Count];
				a->CopyTo( c);
				return c;
			}

			return new D2Control* [0];
		}
		
		// Get control by matching the name of a label control and the finding the 
		//	closest control of the indicated type to it.  
		D2Control* D2Control::GetLabeled( String* label, ControlType type){
		
			// find the control of interest if there is one
			D2Control* labeled[] = Get( label, LabelBox);
			if( !labeled || labeled->Count == 0){
				return NULL;
			}

			// Now find the closest control of the given type not too far below the label			
			ArrayList*		a = new ArrayList();
			ButtonAttrib *	ba = *D2WIN::ptFirstButton;
			D2Control*		control;
			D2Control*		closestControl = NULL;
			int				closestDist = INT_MAX;
			int				dist, xDiff, yDiff;
			int				labelX = labeled[0]->get_X();
			int				labelY = labeled[0]->get_Y();
			
			while( ba){
				control = new D2Control( ba);
				
				xDiff = control->get_X() - labelX;
				yDiff = control->get_Y() - labelY;
				dist = xDiff * xDiff + yDiff * yDiff;
				
				if( control->get_Type() == type && dist < closestDist && yDiff > -5){
					closestDist = dist;
					closestControl = control;
				}
				ba = ba->ptNext;
			}

			return closestControl;
		}

		void D2Control::doClick(int x, int y, ClickType clicktype)
		{
			DWORD xpos = x;
			DWORD ypos = y;
			LPARAM lp = x + (y << 16);
			switch(clicktype)
			{
			case ClickType::LeftDown:
				SendMessage(D2GFX::GetWindowHandle(), WM_LBUTTONDOWN, 0, lp);
				break;
			case ClickType::LeftUp:
				SendMessage(D2GFX::GetWindowHandle(), WM_LBUTTONUP, 0, lp);
				break;
			case ClickType::RightDown:
				SendMessage(D2GFX::GetWindowHandle(), WM_RBUTTONDOWN, 0, lp);
				break;
			case ClickType::RightUp:
				SendMessage(D2GFX::GetWindowHandle(), WM_RBUTTONUP, 0, lp);
				break;
			}
		}
		
		void D2Control::Click()
		{//SendMouseClick(int x, int y, ClickType clicktype)
			doClick(control->Xpos + (control->width/2), control->Ypos - (control->height/2), ClickType::LeftDown);
			Thread::Sleep(100);
			doClick(control->Xpos + (control->width/2), control->Ypos - (control->height/2), ClickType::LeftUp);

			//coreClickControl(control);
		}

		void D2Control::Click(int x, int y)
		{//SendMouseClick(int x, int y, ClickType clicktype)
			doClick(x, y, ClickType::LeftDown);
			Thread::Sleep(100);
			doClick(x, y, ClickType::LeftUp);

			//coreClickControl(control);
		}

		ControlType D2Control::get_Type()
		{
			return (ControlType)control->eType;
		}

		bool D2Control::get_Enabled()
		{
			if(control->flags & 0x1)
				return true;
			return false;
		}

		/*
		void D2Control::set_Enabled(bool)
		{
			if(control->flags & 0x1)
				return true;
			return false;
		}
		*/

		int D2Control::get_X()
		{
			return (int)control->Xpos;
		}

		void D2Control::set_X(int NewX)
		{
			control->Ypos = NewX;
		}

		int D2Control::get_Y()
		{
			return (int)control->Ypos;
		}

		void D2Control::set_Y(int NewY)
		{
			control->Ypos = NewY;
		}

		int D2Control::get_Width()
		{
			return (int)control->width;
		}

		int D2Control::get_Height()
		{
			return (int)control->height;
		}

		String * D2Control::get_Text()
		{
			String * alltext = S"";
			D2TextInfo * ti;
			switch(control->eType)
			{
			case 6:
				return Convert::ToString(((D2WIN_Button*)control)->Text);
			case 4:
				ti = ((D2WIN_Textbox*)control)->FirstLine;
				if(ti)
				{
					do
					{
						alltext = String::Concat(alltext, Convert::ToString(ti->Text));
						if(ti->Text2)
						{
							alltext = String::Concat(", ", alltext, ", ", Convert::ToString(ti->Text2));
						}
						else
							alltext = String::Concat(alltext, " ");

					}while(ti = ti->ptNext);
				}
				return alltext;
			case 1:
				return Convert::ToString(((D2WIN_EditBox*)control)->Text);
			}
			return S"";
		}

		String * D2Control::get_ColoredText()
		{
			String * alltext = S"";
			D2TextInfo * ti;
			switch(control->eType)
			{
			case 6:
				return Convert::ToString(((D2WIN_Button*)control)->Text);
			case 4:
				ti = ((D2WIN_Textbox*)control)->FirstLine;
				if(ti)
				{
					do
					{
						alltext = String::Concat(alltext, S"ÿc", ti->Color.ToString(), Convert::ToString(ti->Text));
						if(ti->Text2)
						{
							alltext = String::Concat(", ", alltext, ", ", Convert::ToString(ti->Text2));
						}
						else
							alltext = String::Concat(alltext, " ");

					}while(ti = ti->ptNext);
				}
				return alltext;
			case 1:
				return Convert::ToString(((D2WIN_EditBox*)control)->Text);
			}
			return S"";
		}

		void D2Control::set_Text(String * text)
		{
			D2WIN_EditBox * textable;
			int lng;

			switch(control->eType)
			{
			case 6:
				lng = text->Length < 20 ? text->Length : 20;
				Marshal::Copy(text->ToCharArray(), 0, ((D2WIN_Button*)control)->Text, lng);
				return;
			case 1:
				
				textable = (D2WIN_EditBox*)control;
				char __nogc* pStr = static_cast<char*>(Marshal::StringToHGlobalAnsi(text).ToPointer()); 
				MultiByteToWideChar(0, 0, pStr, -1, textable->Text, textable->MaxLength);
				Marshal::FreeHGlobal(pStr);
				if(text->Length == 0)
					textable->Length = 0xFFFFFFFF;
				else
					textable->Length = text->Length - 1;
				textable->CursorPosition = text->Length;
				textable->CursorLoc = textable->Length;
				textable->CursorLoc2 = textable->Length;

				/*
				textable = (D2WIN_EditBox*)control;
				textable->Text[0] = 0x0;
				textable->Length = 0xFFFFFFFF;
				textable->CursorPosition = 0;
				textable->CursorLoc = 0xFFFFFFFF;
				textable->CursorLoc2 = 0;
				*/

				this->Click();
				Thread::Sleep(5);
                Game::SendKey(39, 0x014D0001);

			}
		}


	}
}