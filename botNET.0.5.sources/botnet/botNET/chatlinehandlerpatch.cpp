#include "botnet.h"
#include ".\chatlinehandlerpatch.h"
#include ".\game.h"
#include ".\eventargs.h"
#include ".\d2client.h"
#include ".\d2win.h"
#include ".\d2multi.h"

bool __stdcall cbCommandLine(wchar_t* msg);

namespace botNET
{
namespace Imports
{
namespace Patches
{


//OOG
	/*
void __fastcall ChatLineHandlerSTUB(char * msg)
{
	ButtonAttrib * editbox = *p_D2WIN_ptFocusedControl;

	wchar_t wmsg[0x100];
	ConvertToUnicode(msg, wmsg, 0xFF);
	if(cmdlinecallback(wmsg))
		D2MULTI_ChatLineSend(msg);
	else
		((D2WIN_EditBox*)editbox)->Text[0] = 0x0;

}*/

//IG
void __declspec(naked) ChatBoxHandlerSTUB()
{

	__asm
	{
			push ecx
			push eax
			push edi
			push esi

			push D2CLIENT::LastChatMessage
			call cbCommandLine
			cmp eax, 1

			pop esi
			pop edi
			pop eax
			pop ecx
			jnz end
			call D2CLIENT::ChatBoxSend
end:
			retn
	}

}

//OOG
void __declspec(naked) ChatLineHandlerSTUB(char * msg)
{

	__asm
	{
		push ecx
		call ChatLineHandler
		retn
	}

}


void __stdcall ChatLineHandler(char * msg)
{
	ButtonAttrib * editbox = *D2WIN::ptFocusedControl;

	wchar_t wmsg[0x100];
	MultiByteToWideChar(0, 0, msg, -1, wmsg, 0xFF);
	if(cbCommandLine(wmsg))
		D2MULTI::ChatLineSend(msg);
	else
		((D2WIN_EditBox*)editbox)->Text[0] = 0x0;

}





}//Patches
}//Imports
}//botNET

