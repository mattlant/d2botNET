#include "botnet.h"
#include ".\heap.h"



namespace botNET
{
	namespace Collections
	{

/***********************************************************
* Heap CLass
**********************************************************/
		Heap::Heap(int maxsize, HeapDirection Direction)
		{
			this->list = new IHeapNode * [maxsize + 1];
			this->direction = Direction;
			this->length = 1;
		}

		
		Heap::~Heap(void)
		{
		} 

		IEnumerator* Heap::GetEnumerator()
		{
			return this->list->GetEnumerator();
		}

		int Heap::get_Count()
		{
			return this->length - 1;
		}

		bool Heap::get_IsSynchronized()
		{
			return this->list->IsSynchronized;
		}

		System::Object* Heap::get_SyncRoot()
		{
			return this->list->SyncRoot;
		}

		void Heap::CopyTo(Array* target, int index)
		{
			this->list->CopyTo(target, index);
		}


		void Heap::Add(IHeapNode * Node)
		{
			switch(this->direction)
			{
				case HeapDirection::LowHasPriority:
				{
					int i = this->length;
					int id2 = i/2;

					while (i > 1 && this->list[id2]->Priority > Node->Priority)
					{
						this->list[i] = this->list[id2];
						i  =  id2;
						id2 =i/2;
					}
					this->list[i] = Node;
					this->length++;
					break;
				}
				case HeapDirection::HighHasPriority:
					int i = this->length;
					int id2 = i/2;

					while (i > 1 && this->list[id2]->Priority < Node->Priority)
					{
						this->list[i] = this->list[id2];
						i  =  id2;
						id2 =i/2;
					}
					this->list[i] = Node;
					this->length++;
					break;
			}
		}

		IHeapNode * Heap::Remove()
		{
			int j, i = 1;
			int hl1 = this->length-1;
			int hl12 = hl1 / 2;

			IHeapNode * d = this->list[1];

			IHeapNode * tmp = this->list[hl1];

			switch(this->direction)
			{
				case HeapDirection::LowHasPriority:
				{
					if (this->length == 1) return NULL;

					while (i <= hl12) 
					{
						j = i+i;
						if ((j < hl1) && this->list[j]->Priority > this->list[j + 1]->Priority)
							++j;
						if (this->list[j]->Priority >= tmp->Priority)
							break;
						this->list[i] = this->list[j];
						i = j;
					}
					this->list[i] = tmp;
					this->length--;
					return d;
				}
				case HeapDirection::HighHasPriority:
					if (this->length == 1) return NULL;

					while (i <= hl12) 
					{
						j = i+i;
						if ((j < hl1) && this->list[j]->Priority < this->list[j + 1]->Priority)
							++j;
						if (this->list[j]->Priority <= tmp->Priority)
							break;
						this->list[i] = this->list[j];
						i = j;
					}
					this->list[i] = tmp;
					this->length--;
					return d;

			}
			return NULL;
		}

		IHeapNode * Heap::Peek()
		{
			if(this->length == 1) return NULL;
			return this->list[1];
		}

		void Heap::Clear()
		{
			this->length = 1;
		}

		int Heap::get_Length()
		{
			return this->length - 1;
		}



/***********************************************************
* HeapNode CLass, used for the Heap
**********************************************************/
		HeapNode::HeapNode(Object * Item, float Priority)
		{
			this->Item = Item;
			this->Priority = Priority;
		}

		float HeapNode::get_Priority()
		{
			return this->_p;
		}

		void HeapNode::set_Priority(float value)
		{
			this->_p = value;
		}


	}
}