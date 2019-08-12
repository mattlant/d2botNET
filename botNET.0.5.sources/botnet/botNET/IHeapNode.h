#ifndef IHEAPNODE_H
#define IHEAPNODE_H


namespace botNET
{
	namespace Collections
	{

		/// <summary>
		/// A Class used to put an object onto the heap
		/// </summary>
		__gc public __interface IHeapNode
		{
		public:
			__property float get_Priority();
			__property void set_Priority(float value);
		};


	}

}

#endif