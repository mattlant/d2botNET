
#include "botnet.h"
#include "screenhookmanager.h"
#include "screenhook.h"
#include "Game.h"
#include "Heap.h"

using namespace botNET::Drawing;
using namespace botNET::Collections;

namespace botNET
{

	namespace Drawing
	{

		void ScreenHookManager::add_OnDrawSH(OnDrawSHHandler* h)
		{
			//add first
			InternalOnDrawSHEvent += h;
			//now reorder by Z Order

		}

		void ScreenHookManager::remove_OnDrawSH(OnDrawSHHandler* h)
		{
			InternalOnDrawSHEvent -= h;
			ScreenHookManager::reorder();
		}

		void ScreenHookManager::raise_OnDrawSH()
		{
			if(InternalOnDrawSHEvent)
				InternalOnDrawSHEvent();
		}

		bool ScreenHookManager::CheckClickAll(int clickedx, int clickedy, MouseClickType Clicktype)
		{
			bool passclick = true;
			/*
			for(int i= 0; i < ScreenHooks->Count; i++)
			{
				ScreenHook * sh = __try_cast<ScreenHook*>(ScreenHooks->Item[i]);
				if(!sh->CheckClick(clickedx, clickedy, Clicktype))
					passclick = false;
			}
			*/
			return passclick;
			
		}

		void ScreenHookManager::reorder()
		{ 
			Delegate* ilist __gc[] = InternalOnDrawSHEvent->GetInvocationList();
			ScreenHookHeap = new botNET::Collections::Heap(ilist->Length+1, botNET::Collections::HeapDirection::LowHasPriority);
			for(int i = 0; i < ilist->Length; i++)
			{
				ScreenHook* temp = static_cast<ScreenHook*>(ilist[i]->Target);
				HeapNode* node = new HeapNode(ilist[i], (float)temp->ZOrder);
				ScreenHookHeap->Add(node); 
			}


			InternalOnDrawSHEvent = static_cast<OnDrawSHHandler*>(Delegate::RemoveAll(InternalOnDrawSHEvent, InternalOnDrawSHEvent));

			for(int i = 0; i < ilist->Length; i++)
			{
				HeapNode* hn = static_cast<HeapNode*>(ScreenHookHeap->Remove());
				if(!hn)
				{
					Game::Print(S"hn was null");
					break;
				}

				InternalOnDrawSHEvent = static_cast<OnDrawSHHandler*>(
					Delegate::Combine(InternalOnDrawSHEvent, static_cast<Delegate*>(hn->Item)));
			}

		}


	}

}

