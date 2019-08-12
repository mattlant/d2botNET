#ifndef BOTNET_H
#define BOTNET_H

#define XP_WIN
#include <windows.h>
#undef MessageBox
#undef GetObject

#include <winbase.h>
#include <stdio.h>
#include <conio.h>

#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>
#using <System.Windows.Forms.dll>

namespace botNET
{
	namespace Mapping	{}
	namespace Messaging	{}
	namespace Threading	{}
	namespace Drawing	{}
	namespace Units	{}
	namespace Collections	{}
	namespace Compiler	{}
	namespace Configuration	{}
	namespace Diagnostics	{}
	namespace Pathing	{}
	namespace Imports	{}
}

using namespace System;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Xml;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace botNET::Imports;

extern CRITICAL_SECTION PrintBufferCritSect;
extern CRITICAL_SECTION RoomCritSect;


#include "standardenumerations.h"
#include "delegates.h"


#endif