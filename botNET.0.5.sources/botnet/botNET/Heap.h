#ifndef HEAP_H
#define HEAP_H

#include "iheapnode.h"

namespace botNET
{
	namespace Collections
	{

		/// <summary>
		/// A Class used to put an object onto the heap
		/// </summary>
		__gc public class HeapNode : public IHeapNode
		{
		public:
			/// <summary>
			/// Creates a HeapNode object for the Heap
			/// </summary>
			/// <param name="Item">The object to put on the heap</param>
			/// <param name="Priority">The priority of the item</param>
			HeapNode(Object * Item, float Priority);

			/// <summary>
			/// The object to put on the heap
			/// </summary>
			Object * Item;

			/// <summary>
			/// The priority of the item
			/// </summary>
			__property float get_Priority();
			__property void set_Priority(float value);

		private:
			float _p;
		};


		/// <summary>
		/// Defines heap priority
		/// </summary>
		__value public enum HeapDirection
		{
			/// <summary>
			/// Used to instruct the heap to consider low priority as more important
			/// </summary>
			LowHasPriority,
			/// <summary>
			/// Used to instruct the heap to consider high priority as more important
			/// </summary>
			HighHasPriority
		};


		/// <summary>
		/// This is an implementation of a Binary Heap class
		/// </summary>
		__gc public class Heap : public System::Collections::IEnumerable, public System::Collections::ICollection
		{
		public:
			/// <summary>
			/// Creates the Heap
			/// </summary>
			/// <param name="maxsize">Maximum size of teh heap</param>
			/// <param name="Direction">Sets wether Low is a priority or High is a priority</param>
			Heap(int maxsize, HeapDirection Direction);

			~Heap(void);

			//IEnumerable
			IEnumerator* GetEnumerator();

			//ICollection
			__property int get_Count();
			__property bool get_IsSynchronized();
			__property Object* get_SyncRoot();
			void CopyTo(Array* target, int index);


			/// <summary>
			/// Adds a Node to teh Heap
			/// </summary>
			/// <param name="d">A node used on the heap</param>
			void Add(IHeapNode * Node);

			/// <summary>
			/// Removes a Node from the Heap with the highest prioroty
			/// </summary>
			/// <returns>Returns a HeapNode object</returns>
			IHeapNode * Remove();

			/// <summary>
			/// Returns the Highest Priority Item, but does not remove
			/// </summary>
			/// <returns>Returns a HeapNode object</returns>
			IHeapNode * Peek();

			/// <summary>
			/// Clears the Heap
			/// </summary>
			void Clear();

			/// <summary>
			/// Clears the Heap
			/// </summary>
			__property int get_Length();

		public private:
			IHeapNode * list __gc[];
			HeapDirection direction;
			int length;

		};


	}
}

#endif