#ifndef GLOBALMESSAGEHANDLERPATCH_H
#define GLOBALMESSAGEHANDLERPATCH_H

namespace botNET
{
namespace Imports
{
namespace Patches
{

bool __stdcall MessageHandlerSTUB(HWND hwnd, int Message, WPARAM wParam, LPARAM lParam, bool * NotDef, int * retVal);

}
}
}

#endif