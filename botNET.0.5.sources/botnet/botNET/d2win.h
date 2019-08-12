#ifndef D2WIN_H
#define D2WIN_H

#include "definitions.h"

namespace botNET
{
	namespace Imports
	{
		__nogc class D2WIN
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;
//D2FUNCPTR(D2WIN, TextBoxPrint, void __fastcall, (ButtonAttrib * textbox, wchar_t * text, int color, int unk0, int unk1), -0x2743);
//6F8B0040 >/$ 81EC 24080000  SUB ESP,824


			static void TextBoxPrint(ButtonAttrib * textbox, wchar_t * text, int color, int unk0, int unk1); //10051
			static void* fptrTextBoxPrint;

			static void DrawTextHook(wchar_t * text, int x, int y, int color, int unk_0); //10117
			static void* fptrDrawTextHook;

			static DWORD SetTextHookFont(DWORD fontnumber); //10127 //Returns old font
			static void* fptrSetTextHookFont;

			static DWORD GetTextHookWidth(wchar_t * text); //10121
			static void* fptrGetTextHookWidth;

			static BYTE GetCurrentFontHeight(void); //10125
			static void* fptrGetCurrentFontHeight;

			static DWORD GetNTextHookWidth(wchar_t * text, int nChar); //10122
			static void* fptrGetNTextHookWidth;

			static void ChatLineEnter(D2MSG * ptMsg);
			static void* fptrChatLineEnter; //0xDB50

			static void MouseHandler(D2MSG * ptMsg);
			static void* fptrMouseHandler; //0xE070

			static void DrawScreen(void);
			static void* fptrDrawScreen; //-0x2723 //#10019

			static void SetPalette(BYTE unk);
			static void* fptrSetPalette; //#10177



			static ButtonAttrib** ptFirstButton;
			static int* sgtWindowData_deadChildrenLocked;
			static ButtonAttrib** ptFocusedControl;
			static DWORD* CurrentFont;



			static DWORD asmCallChatLineEnter;
			static DWORD oldCallChatLineEnter;
			static DWORD asmCallOOGGlobalMessageHandler;
			static DWORD oldCallOOGGlobalMessageHandler;
			static DWORD asmCallDrawScreen;		//0xD04C
			static DWORD oldCallDrawScreen;		//0xD04C

		};


	}


}

#endif
/*
D2FUNCPTR(D2WIN, DrawText, void __fastcall, (wchar_t * pszwText, int x, int y, int nColor, int unknown), -0x2785);	// #10117
6F8AAD40 >/$ 53             PUSH EBX

D2FUNCPTR(D2WIN, GetTextWidth, int __fastcall, (wchar_t * pszwText), -0x2789);								// #10121
D2FUNCPTR(D2WIN, GetNTextWidth, int __fastcall, (wchar_t * pszwText, int nChar), -0x278A);					// #10122
D2FUNCPTR(D2WIN, GetFontHeight, BYTE __fastcall, (void), -0x278D);										// #10125
D2FUNCPTR(D2WIN, DrawTextFont, DWORD __fastcall, (int fontnum), -0x278F);									// #10127
*/