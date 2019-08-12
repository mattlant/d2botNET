#include "botnet.h"
#include "d2client.h"

using namespace botNET::Imports;

		void __declspec( naked ) D2CLIENT_ClickMapASM(DWORD ClickType, DWORD ClickFlag, UnitAny * unit, DWORD x, DWORD Y)
		{

			__asm {
				PUSH EBP
				MOV EBP,ESP
				PUSH ECX
				MOV EAX,DWORD PTR DS:[D2CLIENT::IsPaused]
				XOR ECX,ECX
				PUSH EBX
				PUSH ESI
				CMP DWORD PTR DS:[EAX],ECX
				PUSH EDI
				JNZ endhere
				MOV DWORD PTR DS:[EAX],0x1
				MOV EAX,DWORD PTR DS:[D2CLIENT::MouseX] ;0xD40EC
				MOV EDX,DWORD PTR DS:[D2CLIENT::MouseY] ;0xD40F0         
				MOV EBX,DWORD PTR DS:[EAX]
				MOV EDX,DWORD PTR DS:[EDX]
				MOV DWORD PTR DS:[EAX],ECX
				MOV EAX,DWORD PTR DS:[D2CLIENT::MouseY] ;0xD40F0
				MOV DWORD PTR SS:[EBP-0x4],EDX
				MOV DWORD PTR DS:[EAX],ECX
				MOV ECX,DWORD PTR SS:[EBP+0x8]
				MOV EDX,0x0
				PUSH DWORD PTR SS:[EBP+0xC]
				PUSH 0x0
				CALL realdeal
				JMP SHORT endhere

		realdeal:
				SUB ESP,0x28
				PUSH EBX
				PUSH ESI
				MOV ESI,ECX
				PUSH EDI
				MOV EAX,DWORD PTR SS:[EBP+0x18]
				MOV DWORD PTR SS:[ESP+0x38],EAX
				MOV EAX,DWORD PTR SS:[EBP+0x14]
				MOV DWORD PTR SS:[ESP+0xC],EAX
				MOV ECX,0x8
				XOR EAX,EAX
				LEA EDI,DWORD PTR SS:[ESP+0x14]
				REP STOS DWORD PTR ES:[EDI]
				MOV DWORD PTR SS:[ESP+0x14],EAX
				MOV EAX, 0x6FB283D0
				CALL EAX							;getplayer unit		
				MOV DWORD PTR SS:[ESP+0x18],EAX
				MOV EAX,DWORD PTR SS:[EBP+0x10]
				PUSH 0x6FB4999F        ;mouse click test     
				RETN
		endhere:
				MOV EAX,DWORD PTR DS:[D2CLIENT::MouseX]
				MOV ECX,DWORD PTR SS:[EBP-0x4]
				MOV DWORD PTR DS:[EAX],EBX
				MOV EAX,DWORD PTR DS:[D2CLIENT::MouseY]
				MOV DWORD PTR DS:[EAX],ECX
				POP EDI
				POP ESI
				POP EBX
				LEAVE
				RETN
			}

		}
