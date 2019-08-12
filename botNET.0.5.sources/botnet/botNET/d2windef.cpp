#include "botnet.h"
#include "d2win.h"


namespace botNET
{
	namespace Imports
	{
		UInt32 D2WIN::BaseAddress = 0;


		void* D2WIN::fptrTextBoxPrint =				0;
		void* D2WIN::fptrDrawTextHook =				0;
		void* D2WIN::fptrSetTextHookFont =			0;
		void* D2WIN::fptrGetTextHookWidth =			0;
		void* D2WIN::fptrGetCurrentFontHeight =		0;
		void* D2WIN::fptrGetNTextHookWidth =		0;
		void* D2WIN::fptrChatLineEnter = 0; //0xDB50
		void* D2WIN::fptrMouseHandler = 0; //0xE070
		void* D2WIN::fptrDrawScreen = 0; //-0x2723
		void* D2WIN::fptrSetPalette = 0; //#10177

		ButtonAttrib** D2WIN::ptFirstButton = 0; //0x5E24C
		int* D2WIN::sgtWindowData_deadChildrenLocked = 0; //0x5E254
		ButtonAttrib** D2WIN::ptFocusedControl = 0; //0x5E25C
		DWORD* D2WIN::CurrentFont = 0; //0x1DB24

		DWORD D2WIN::asmCallChatLineEnter = 0; //0x1DEF0
		DWORD D2WIN::oldCallChatLineEnter = 0; //0x1DEF0
		DWORD D2WIN::asmCallOOGGlobalMessageHandler = 0; //0xDA3F
		DWORD D2WIN::oldCallOOGGlobalMessageHandler = 0; //0xDA3F
		DWORD D2WIN::asmCallDrawScreen = 0;		//0xD04C
		DWORD D2WIN::oldCallDrawScreen = 0;		//0xD04C

	}

}