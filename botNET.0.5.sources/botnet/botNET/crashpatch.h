#ifndef CRASHPATCH_H
#define CRASHPATCH_H

namespace botNET
{
namespace Imports
{
namespace Patches
{

void ExceptionSTUB(DWORD unk1, DWORD unk2);
void ErrorSTUB(DWORD unk1, DWORD unk2);
void __stdcall ExceptionHANDLER(DWORD unk1, DWORD unk2);
void __stdcall ErrorHANDLER(DWORD unk1, DWORD unk2);


}
}
}

#endif