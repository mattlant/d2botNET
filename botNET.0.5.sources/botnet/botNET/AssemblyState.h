#ifndef ASSEMBLYSTATE_H
#define ASSEMBLYSTATE_H

using namespace System;

namespace botNET
{
	///<summary>
	/// Describes state of assembly module.
	///</summary>
	public __value enum AssemblyState
	{
		///<summary>
		/// Assembly is during loading process.
		///</summary>
		Loading = 1,

		///<summary>
		/// Assembly is loaded and running.
		///</summary>
		Loaded,

		///<summary>
		/// Assembly is in the process of disposing.
		///</summary>
		Disposing,

		///<summary>
		/// Assembly is already disposed.
		///</summary>
		Disposed,

		///<summary>
		/// Assembly is either newver loaded or disposed and removed from botNET.
		///</summary>
		Unknown,
	};
}

#endif