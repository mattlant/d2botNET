#ifndef SCREENHOOKMGR_H
#define SCREENHOOKMGR_H

#include "delegates.h"
#include "standardenumerations.h"
#include "EventArgs.h"

namespace botNET
{
	namespace Collections
	{
		__gc public class Heap;
	}

	namespace Drawing
	{

		public __gc class ScreenHook;
	
		private __gc class ScreenHookManager
		{
		public private:

			static bool	CheckClickAll(int clickedx,	int	clickedy, MouseClickType Clicktype);

			static bool	DisableAll; // TODO: this shall be checked in the RaiseDrawSHEvent

			//********************* EVENTSTUFF ******************************
			static OnDrawSHHandler * InternalOnDrawSHEvent;
			static __event void add_OnDrawSH( OnDrawSHHandler* h);
			static __event void remove_OnDrawSH( OnDrawSHHandler* h);
			static __event void raise_OnDrawSH();

			static Int64 IDBaseCount;
			static botNET::Collections::Heap * ScreenHookHeap;
			static ArrayList * DrawDelegates;


			static void reorder();

		};

	}

}


#endif

