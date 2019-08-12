#ifndef D2GFX_H
#define D2GFX_H

#include "definitions.h"

//typedef void __stdcall tdDrawRectangle(int X1, int Y1, int X2, int Y2, int color, int Transparency);

namespace botNET
{
	namespace Imports
	{
		__nogc class D2GFX
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			[DllImport("d2gfx", EntryPoint="#10026", CallingConvention=CallingConvention::StdCall)]
			static bool IsMinimized(void);

			[DllImport("d2gfx", EntryPoint="#10027", CallingConvention=CallingConvention::StdCall)]
			static HWND GetWindowHandle(void);

			[DllImport("d2gfx", EntryPoint="#10041", CallingConvention=CallingConvention::StdCall)]
			static void GetScreenDimensions(int * X, int * Y);

			[DllImport("d2gfx", EntryPoint="#10051", CallingConvention=CallingConvention::StdCall)]
			static void DrawDiamond(Res * prc, BYTE color);

			[DllImport("d2gfx", EntryPoint="#10055", CallingConvention=CallingConvention::StdCall)]
			static void DrawRectangle(int X1, int Y1, int X2, int Y2, int color, int Transparency);

			[DllImport("d2gfx", EntryPoint="#10056", CallingConvention=CallingConvention::StdCall)]
			static void DrawRectangle2(int X1, int Y1, int X2, int Y2, int color, int Transparency);

			[DllImport("d2gfx", EntryPoint="#10057", CallingConvention=CallingConvention::StdCall)]
			static void DrawLine(DWORD X1, DWORD Y1, DWORD X2, DWORD Y2, BYTE color, BYTE);

			[DllImport("d2gfx", EntryPoint="#10072", CallingConvention=CallingConvention::StdCall)]
			static void PrintImage(void * ptStruct, int Xpos, int Ypos, DWORD layer, DWORD _2, DWORD _3);

			[DllImport("d2gfx", EntryPoint="#10077", CallingConvention=CallingConvention::StdCall)]
			static void PrintImageNonStatic(void *context, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD bright);

			//static tdDrawRectangle* ptrDrawRectangle;6FA7490E

			static DWORD asmCallIsIconic;
			static DWORD oldCallIsIconic;

		};

	}

}

#endif