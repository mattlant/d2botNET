#include "botnet.h"
#include "d2win.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void D2WIN::Initialize()
		{
			BaseAddress = Importer::D2Win->BaseAddress.ToInt32();

			D2WIN::fptrTextBoxPrint =				Importer::GetFunctionAddress(Importer::D2Win, 10051).ToPointer();
			D2WIN::fptrDrawTextHook =				Importer::GetFunctionAddress(Importer::D2Win, 10117).ToPointer();
			D2WIN::fptrSetTextHookFont =			Importer::GetFunctionAddress(Importer::D2Win, 10127).ToPointer();
			D2WIN::fptrGetTextHookWidth =			Importer::GetFunctionAddress(Importer::D2Win, 10121).ToPointer();
			D2WIN::fptrGetCurrentFontHeight =		Importer::GetFunctionAddress(Importer::D2Win, 10125).ToPointer();
			D2WIN::fptrGetNTextHookWidth =			Importer::GetFunctionAddress(Importer::D2Win, 10122).ToPointer();
			D2WIN::fptrDrawScreen =					Importer::GetFunctionAddress(Importer::D2Win, 10019).ToPointer();
			D2WIN::fptrSetPalette =					Importer::GetFunctionAddress(Importer::D2Win, 10177).ToPointer();

			D2WIN::fptrChatLineEnter = reinterpret_cast<void*> (BaseAddress + 0xDB50);
			D2WIN::fptrMouseHandler = reinterpret_cast<void*> (BaseAddress + 0xE070);


			D2WIN::ptFirstButton = reinterpret_cast<ButtonAttrib**> (BaseAddress + 0x5E24C);
			D2WIN::sgtWindowData_deadChildrenLocked = reinterpret_cast<int*> (BaseAddress + 0x5E254);
			D2WIN::ptFocusedControl = reinterpret_cast<ButtonAttrib**> (BaseAddress + 0x5E25C);
			D2WIN::CurrentFont = reinterpret_cast<DWORD*> (BaseAddress + 0x1DB24);

	
			D2WIN::asmCallChatLineEnter = (BaseAddress + 0x1DEF0);
			D2WIN::asmCallOOGGlobalMessageHandler = (BaseAddress + 0xDA3F);
			D2WIN::asmCallDrawScreen = (BaseAddress + 0xD04C);

		}

		void D2WIN::TextBoxPrint(ButtonAttrib * textbox, wchar_t * text, int color, int unk0, int unk1) //10117
		{	
			__asm {	push unk1
					push unk0
					push color
					mov edx, text
					mov ecx, textbox
					mov eax, 0x6F8B0040
					call eax				
			}
		}

		void D2WIN::DrawTextHook(wchar_t * text, int x, int y, int color, int unk_0) //10117
		{	
			__asm {	push unk_0
					push color
					push y
					mov edx, x
					mov ecx, text
					mov eax, 0x6F8AAD40
					call eax				
			}
		}

		//Returns old font
		DWORD D2WIN::SetTextHookFont(DWORD fontnumber) //10127
		{	
			DWORD retval;

			__asm {	mov ecx, fontnumber
					mov eax, 0x6F8A9FF0
					call eax
					mov retval, eax			
			}
			return retval;
		}

		DWORD D2WIN::GetTextHookWidth(wchar_t * text) //10121
		{	
			DWORD retval;

			__asm {	mov ecx, text
					mov eax, 0x6F8AA2A0
					call eax
					mov retval, eax			
			}
			return retval;
		}

		BYTE D2WIN::GetCurrentFontHeight(void) //10125
		{	
			BYTE retval;

			__asm {	mov eax, 0x6F8AA2F0
					call eax
					mov retval, al			
			}
			return retval;
		}

		DWORD D2WIN::GetNTextHookWidth(wchar_t * text, int nChar) //10122
		{   
			DWORD retval;

			__asm {	mov edx, nChar
					mov ecx, text
					mov eax, 0x6F8AA260
					call eax
					mov retval, eax			
			}
			return retval;
		}

		void D2WIN::ChatLineEnter(D2MSG * ptMsg)
		{
			__asm
			{
				push ptMsg
				mov eax, D2WIN::fptrChatLineEnter		;0xDB50
				call eax
			}
		}

		void D2WIN::MouseHandler(D2MSG * ptMsg)
		{
			__asm
			{
				push ptMsg
				mov eax, D2WIN::fptrMouseHandler		;0xE070
				call eax
			}
		}

		void D2WIN::DrawScreen(void)
		{
			__asm
			{
				mov eax, D2WIN::fptrDrawScreen		;-0x2723
				call eax
			}
		}

		void D2WIN::SetPalette(BYTE unk)
		{
			__asm
			{
				mov cl, unk
				mov eax, D2WIN::fptrSetPalette		;#10177
				call eax
			}
		}

	}

}
