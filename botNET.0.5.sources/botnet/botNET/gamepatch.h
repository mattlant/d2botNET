#ifndef GAMEPATCH_H
#define GAMEPATCH_H

#include "definitions.h"

namespace botNET
{
namespace Imports
{
namespace Patches
{

void __stdcall ActChangeSTUB(int act);
void EndGameSTUB (void);
void __stdcall EndGameHANDLER (UnitPlayer * ptPlayer);
Room1 * __stdcall NewGameHANDLER(void);
void NewGameSTUB (void);



}
}
}

#endif