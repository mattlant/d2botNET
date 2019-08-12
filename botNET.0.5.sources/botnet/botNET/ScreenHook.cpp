
#include "botnet.h"
#include "screenhook.h"
#include "Heap.h"
#include "screenhookmanager.h"
#include "Game.h"
#include "d2client.h"
#include "settings.h"

namespace botNET 
{

	namespace Drawing	
	{

		ScreenHook::ScreenHook(int x, int y, int _color, ScreenHookTransparency _transparency)
		{
			this->_point = System::Drawing::Point(x, y);

			autodispose = true;
			enabled = false;
			visible = true;
			transparency = _transparency;
			color = _color;
			this->id = ScreenHookManager::IDBaseCount++;
			ZOrder = 1;
			ismousecurrentlyover = false;
			ScreenHookManager::OnDrawSH += new OnDrawSHHandler(this, &ScreenHook::e_draw);
			Game::OnEndGame += new OnEndGameHandler(this, &ScreenHook::endgamedispose);
			bool mousedownhook = false;
			bool mouseuphook = false;
			bool mouserepeathook = false;
		}

		ScreenHook::ScreenHook(int x, int y, int _color, ScreenHookTransparency _transparency, bool noadd)
		{
			this->_point = System::Drawing::Point(x, y);

			autodispose = false;
			visible = true;
			transparency = _transparency;
			color = _color;
			ZOrder = 1;
			ismousecurrentlyover = false;
			this->nohookup = noadd;
			//ScreenHookManager::OnDrawSHEvent += new DrawEventHandler(this, &ScreenHook::e_draw);
			bool mousedownhook = false;
			bool mouseuphook = false;
			bool mouserepeathook = false;
		}

		ScreenHook::~ScreenHook(void)
		{
			if(!this->nohookup)
				ScreenHookManager::OnDrawSH -= new OnDrawSHHandler(this, &ScreenHook::e_draw);

			this->Dispose();
		}

		void ScreenHook::Draw()
		{
			RaiseScreenHookDrawEvent();
			bool isover = this->IsMouseOver;
			if(isover && !this->ismousecurrentlyover)
			{
				this->ismousecurrentlyover = true;
				RaiseScreenHookMouseOverEvent(new MouseActionEventArgs(MouseEventType::MouseOver, 0, 0));
			}
			else if(!isover && this->ismousecurrentlyover)
			{
				this->ismousecurrentlyover = false;
				RaiseScreenHookMouseOutEvent(new MouseActionEventArgs(MouseEventType::MouseOut, 0, 0));
			}
		}

		void ScreenHook::e_draw()
		{
			//this is our handler, call our overriden Draw method
			this->Draw();
		}

		void ScreenHook::e_click(Object* sender, MouseActionEventArgs* e)
		{
			this->CheckClick(e);
		}

		void ScreenHook::Delete()
		{
			//simply call dispose
			this->Dispose();
		}

		void ScreenHook::Dispose()
		{
			this->Dispose(true);
			GC::SuppressFinalize(this);
		}

		void ScreenHook::Dispose(bool disposing)
		{
			if(!this->disposed)
			{
				//check if visible, if so remove its draw handler
				if(visible)
					ScreenHookManager::OnDrawSH -= new OnDrawSHHandler(this, &ScreenHook::e_draw);

				//remove the end game handler
				Game::OnEndGame -= new OnEndGameHandler(this, &ScreenHook::endgamedispose);

				if(mouseclickhook)
					Game::OnMouseClick -= new OnMouseActionHandler(this, &ScreenHook::e_click);

				this->disposed = true;
			}
		}

		void ScreenHook::endgamedispose(Object* sender, GameEventArgs* e)
		{
			this->Dispose(true);
		}

		bool ScreenHook::CheckClick(MouseActionEventArgs* e)
		{
			//Check if we clicked, if so raise event handler
			if(enabled)
			{
				if(this->Rectangle.Contains(e->_point))
				{
					raise_OnMouseClick(NULL, e);
					return false;
				}
			}
			return true;
		}

		bool ScreenHook::get_IsMouseOver() 
		{	
			return this->Rectangle.Contains(*D2CLIENT::MouseX, *D2CLIENT::MouseY);
		}

		Int64 ScreenHook::get_ID() {	return id; }

		int ScreenHook::get_ZOrder()
		{
			return this->_zorder;
			ScreenHookManager::reorder();
		}

		void ScreenHook::set_ZOrder(int value)
		{
			this->_zorder = value;
		}

		bool ScreenHook::get_Visible() 
		{	
			return visible; 
		}
		void ScreenHook::set_Visible(bool value)	
		{ 
			if(!visible && value)
				ScreenHookManager::OnDrawSH += new OnDrawSHHandler(this, &ScreenHook::e_draw);
			if(visible && !value)
				ScreenHookManager::OnDrawSH -= new OnDrawSHHandler(this, &ScreenHook::e_draw);
			visible = value; 
		}

		bool ScreenHook::get_AutoDispose() 
		{	
			return visible; 
		}
		void ScreenHook::set_AutoDispose(bool value)	
		{ 
			if(value)
				Game::OnEndGame += new OnEndGameHandler(this, &ScreenHook::endgamedispose);
			if(!value)
				Game::OnEndGame -= new OnEndGameHandler(this, &ScreenHook::endgamedispose);
			this->autodispose = value; 
		}

		bool ScreenHook::get_Enabled() {	return enabled; }
		void ScreenHook::set_Enabled(bool value)	{ enabled = value; }

		void ScreenHook::set_Exposed(bool value)	{ this->Visible = value; this->Enabled = value; }

		int ScreenHook::get_X() {	return this->_point.X; }
		void ScreenHook::set_X(int X) {	this->_point.X = X; }

		int ScreenHook::get_Y() {	return this->_point.Y; }
		void ScreenHook::set_Y(int Y) {	this->_point.Y = Y; }

		System::Drawing::Point ScreenHook::get_Point()
		{
			return this->_point;
		}

		void ScreenHook::set_Point(System::Drawing::Point value)
		{
			this->_point = value;
		}

		System::Drawing::Size ScreenHook::get_Size()
		{
			return this->_size;
		}

		System::Drawing::Rectangle ScreenHook::get_Rectangle()
		{
			return System::Drawing::Rectangle(this->_point, this->_size);
		}


		int ScreenHook::get_Color() {	return color; }
		void ScreenHook::set_Color(int Colour) {	color = Colour; }

		ScreenHookTransparency ScreenHook::get_Transparency() {	return transparency; }
		void ScreenHook::set_Transparency(ScreenHookTransparency value) {	transparency = value; }

		int ScreenHook::get_Width() {	return this->_size.Width; }
		int ScreenHook::get_Height() {	return this->_size.Height; }

		//**** MOUSE DOWN ****
		void ScreenHook::add_OnMouseClick(OnMouseActionHandler* h)
		{
			if(mouseclickhook == 0)
				Game::OnMouseClick += new OnMouseActionHandler(this, &ScreenHook::e_click);
			mouseclickhook++;
			InternalOnMouseClick += h;
		}

		void ScreenHook::remove_OnMouseClick(OnMouseActionHandler* h)
		{
			if(mouseclickhook != 0)
				mouseclickhook--;

			InternalOnMouseClick -= h;

			if(mouseclickhook == 0)
				Game::OnMouseClick -= new OnMouseActionHandler(this, &ScreenHook::e_click);
		}

		void ScreenHook::raise_OnMouseClick(System::Object* sender, MouseActionEventArgs* e)
		{
			if(InternalOnMouseClick)
				InternalOnMouseClick(this, e);
		}


		void ScreenHook::RaiseScreenHookDrawEvent()
		{
			try{
				OnDraw(this, new EventArgs());
			}
			catch (Exception * ex){ 
				if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a ScreenHookDrawEvent: " , ex->Message)); 
			}
		}

		void ScreenHook::RaiseScreenHookMouseOverEvent(MouseActionEventArgs * e)
		{
			try{
				OnMouseOver(this, e);
			}
			catch (Exception * ex){ 
				if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a ScreenHookMouseOverEvent: " , ex->Message)); 
			}
		}

		void ScreenHook::RaiseScreenHookMouseOutEvent(MouseActionEventArgs * e)
		{
			try{
				OnMouseOut(this, e);
			}
			catch (Exception * ex){ 
				if(Settings::Debugging::gPrintExceptions) Game::Print(String::Concat(S"An Exception occured in a ScreenHookMouseOutEvent: " , ex->Message)); 
			}
		}


	}

}
