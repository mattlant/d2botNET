#include "botnet.h"
#include ".\crashpatch.h"
#include ".\game.h"
#include ".\fog.h"
#include ".\crashhandler.h"


namespace botNET
{
namespace Imports
{
namespace Patches
{

void __declspec(naked) ExceptionSTUB(DWORD unk1, DWORD unk2)
{

	__asm
	{
		push edx
		push ecx
		call ExceptionHANDLER
		ret
	}

}

void __declspec(naked) ErrorSTUB(DWORD unk1, DWORD unk2)
{

	__asm
	{
		push edx
		push ecx
		call ErrorHANDLER
		ret
	}

}

void __stdcall ExceptionHANDLER(DWORD unk1, DWORD unk2)
{
	botNET::Diagnostics::CrashHandler::DumpCrash(0);
	FOG::GetComputerInfo(unk1, unk2);

}

void __stdcall ErrorHANDLER(DWORD unk1, DWORD unk2)
{
	botNET::Diagnostics::CrashHandler::DumpCrash(1);
	FOG::GetComputerInfo(unk1, unk2);

}

}//Patches
}//Imports
}//botNET

