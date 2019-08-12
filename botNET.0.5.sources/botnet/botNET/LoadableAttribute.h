#ifndef LOADABLEATTRIBUTE_H
#define LOADABLEATTRIBUTE_H

using namespace System;

namespace botNET
{
	///<summary>
	/// This attribute marks ILoadable impelementing class as main class in assembly.
	///</summary>
	///<remarks> Be warned that this attribute is required and if more then one ILoadable implementing classes are marked with it, only first one found is loaded. </remarks>
	[AttributeUsage(AttributeTargets::Class, AllowMultiple = false)]
	__gc public __sealed class LoadableAttribute : public Attribute
	{
	};
}

#endif