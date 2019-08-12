using System;
using System.Collections;

namespace botNET.Pathing
{
	/// <summary>
	/// Summary description for Heap.
	/// </summary>
	public class Heap
	{
		private HeapNode[] list;
		private HeapDirection direction;

		private int length = 1;

		/// <summary>
		/// Creates the Heap
		/// </summary>
		/// <param name="maxsize">Maximum size of teh heap</param>
		/// <param name="Direction">Sets wether Low is a priority or High is a priority</param>
		public Heap(int maxsize, HeapDirection Direction)
		{
			this.list = new HeapNode[maxsize];
			this.direction = Direction;
		}

		/// <summary>
		/// Adds a Node to teh Heap
		/// </summary>
		/// <param name="d">A node used on the heap</param>
		public void Add(HeapNode d)
		{
			switch(this.direction)
			{
				case HeapDirection.LowPriority:
				{
					int i = this.length;
					int id2 = i/2;

					while (i > 1 && this.list[id2].Priority > d.Priority)
					{
						this.list[i] = this.list[id2];
						i  =  id2;
						id2 =i/2;
					}
					this.list[i] = d;
					this.length++;
					break;
				}
			}
		}
		/// <summary>
		/// Removes a Node from the Heap with the highest prioroty
		/// </summary>
		/// <returns>Returns a HeapNode object</returns>
		public HeapNode Remove()
		{
			switch(this.direction)
			{
				case HeapDirection.LowPriority:
				{
					if (this.length == 1) return null;
					int j, i = 1;

					HeapNode d = this.list[1];
					int hl1 = this.length-1;
					int hl12 = hl1 / 2;

					HeapNode tmp = this.list[hl1];
					while (i <= hl12) 
					{
						j = i+i;
						if ((j < hl1) && this.list[j].Priority > this.list[j + 1].Priority)
							j++;
						if (this.list[j].Priority >= tmp.Priority)
							break;
						this.list[i] = this.list[j];
						i = j;
					}
					this.list[i] = tmp;
					this.length--;
					return d;
				}
			}
			return null;
		}
	}

	/// <summary>
	/// Defines heap priority
	/// </summary>
	public enum HeapDirection
	{
		/// <summary>
		/// Used to instruct the heap to consider low priority as more important
		/// </summary>
		LowPriority,
		/// <summary>
		/// Used to instruct the heap to consider high priority as more important
		/// </summary>
		HighPriority
	}

	/// <summary>
	/// A Class used to put an object onto the heap
	/// </summary>
	public class HeapNode 
	{
		/// <summary>
		/// The object to put on the heap
		/// </summary>
		public object Item;
		/// <summary>
		/// The priority of the item
		/// </summary>
		public double Priority;
		/// <summary>
		/// Creates a HeapNode object for the Heap
		/// </summary>
		/// <param name="Item">The object to put on the heap</param>
		/// <param name="Priority">The priority of the item</param>
		public HeapNode(object Item, double Priority)
		{
			this.Item = Item;
			this.Priority = Priority;
		}
	}


	/*
BotOS.Arrays.Heap = function(pr, o)
{
	if(!pr) {pr = "p";}
	if(!o) {o = mlHEAPHIGH;}
	this._p = pr; //private
	this._o = o; //private
	if(this._o == mlHEAPHIGH){
		this.Insert = Heap_inserthigh;
		this.Remove = Heap_removehigh; }
	else{
		this.Insert = Heap_insertlow;
		this.Remove = Heap_removelow; }

	this.Peek = Heap_peek;
	this.Clear = Heap_clear;
	this.getLength = Heap_qlength;

	this.list = new Array(); //private
	this.list.length++;

	function Heap_inserthigh(d)
	{
		var i = this.list.length;
		var id2 = Math.floor(i/2);
		while (i > 1 && this.list[id2][this._p] < d[this._p])
		{
			this.list[i] = this.list[id2];
			i  =  id2;
			id2 = Math.floor(i/2);
		}
		this.list[i] = d;
	}
	function Heap_removehigh()
	{
		if (this.list.length == 1) return null;
		var j, i = 1;
		//var j;
		var d = this.list[1];
		var hl1 = this.list.length-1;
		var hl12 = Math.floor(hl1 / 2);
		var tmp = this.list[hl1];
		while (i <= hl12) {
			j = i + i;
			if ((j < hl1) && this.list[j][this._p] < this.list[j + 1][this._p])
				j++;
			if (this.list[j][this._p] <= tmp[this._p])
				break;
			this.list[i] = this.list[j];
			i = j;
		}
		this.list[i] = tmp;
		this.list.pop();
		return d;
	}
	function Heap_insertlow(d)
	{
		var i = this.list.length;
		var id2 = Math.floor(i/2);
		while (i > 1 && this.list[id2][this._p] > d[this._p])
		{
			this.list[i] = this.list[id2];
			i  =  id2;
			id2 = Math.floor(i/2);
		}
		this.list[i] = d;
	}
	function Heap_removelow()
	{
		if (this.list.length == 1) return null;
		var j, i = 1;
		//var j;
		var d = this.list[1];
		var hl1 = this.list.length-1;
		var hl12 = Math.floor(hl1 / 2);
		var tmp = this.list[hl1];
		while (i <= hl12) {
			j = i+i;
			if ((j < hl1) && this.list[j][this._p] > this.list[j + 1][this._p])
				j++;
			if (this.list[j][this._p] >= tmp[this._p])
				break;
			this.list[i] = this.list[j];
			i = j;
		}
		this.list[i] = tmp;
		this.list.pop();
		return d;
	}

	function Heap_peek()
	{
		if (this.list.length == 1) return null;
		return this.list[1];
	}

	function Heap_clear()
	{
		this.list.length = 1;
	}

	function Heap_qlength()
	{
		return this.list.length-1;
	}

}
*/
}
