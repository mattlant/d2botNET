#ifndef SCREENHOOK_H
#define SCREENHOOK_H

#include "definitions.h"

#include "delegates.h"

#include "Heap.h"
#include "standardenumerations.h"
#include "EventArgs.h"

namespace botNET
{

	namespace Drawing
	{

		__gc public	class ScreenHook : public IDisposable
		{
		public:
			virtual	void Draw(); //Must	be overriden to actually do the drawing
			void Delete();
			void Dispose();


			__property virtual bool	get_IsMouseOver();

			__property Int64 get_ID();

			__property int get_ZOrder();
			__property void set_ZOrder(int value);

			__property virtual bool	get_Visible();
			__property virtual void	set_Visible(bool);

			__property bool	get_AutoDispose();
			__property void	set_AutoDispose(bool);

			__property bool	get_Enabled();
			__property void	set_Enabled(bool);

			__property void	set_Exposed(bool);

			__property int get_X();
			__property void	set_X(int);

			__property int get_Y();
			__property void	set_Y(int);

			__property System::Drawing::Point get_Point();
			__property void set_Point(System::Drawing::Point value);

			__property System::Drawing::Size get_Size();

			__property System::Drawing::Rectangle get_Rectangle();


			__property ScreenHookTransparency get_Transparency();
			__property void	set_Transparency(ScreenHookTransparency);

			__property int get_Color();
			__property void	set_Color(int);

			__property int get_Width();
			__property int get_Height();

			//Static Event Handler stuff
			__event	OnDrawHandler *	OnDraw;
			//__event	OnMouseHandler * OnMouseDown;
			//__event	OnMouseHandler * OnMouseUp;
			//__event	OnMouseHandler * OnMouseRepeat;
			__event	OnMouseActionHandler * OnMouseOver;
			__event	OnMouseActionHandler * OnMouseOut;

			~ScreenHook(void);

			__event void add_OnMouseClick( OnMouseActionHandler* h);
			__event void remove_OnMouseClick( OnMouseActionHandler* h);

		protected:
			ScreenHook() {}
			ScreenHook(int _x, int _y, int _color, ScreenHookTransparency _transparency);
			ScreenHook(int _x, int _y, int _color, ScreenHookTransparency _transparency, bool noadd);

			virtual void Dispose(bool diposing);

			Int64	id;
			int	color;
			ScreenHookTransparency transparency;
			bool enabled;
			int	ismousecurrentlyover;
			int nohookup;
			int	autodispose;
			int	disposed;
			int	_zorder;
			int _x;
			int _y;

			int mouseclickhook;

			System::Drawing::Point _point;
			System::Drawing::Size _size;

		public private:
			virtual	bool CheckClick(MouseActionEventArgs* e);
			void e_draw(); 
			void e_click(Object* sender, MouseActionEventArgs* e);
			void endgamedispose(Object* sender, GameEventArgs* e);
			bool visible;

			OnMouseActionHandler * InternalOnMouseClick;

			__event void raise_OnMouseClick(System::Object* sender, MouseActionEventArgs* e );

			void RaiseScreenHookDrawEvent();
			void RaiseScreenHookMouseOverEvent(MouseActionEventArgs	* e);
			void RaiseScreenHookMouseOutEvent(MouseActionEventArgs * e);



		};

	}


}

#endif