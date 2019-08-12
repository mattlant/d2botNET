//////////////////////////////////////////////////////////////////////
// Main.cpp
// -------------------------------------------------------------------
// Main file for D2Hackit loader.
//
// If a single D2 window is found, it will be loaded/unloaded without
// any user interaction.  If multiple windows are found, the user will
// be prompted as to whether the program should load/unload each 
// particular window.
//
// This code is version independent in the sense that it finds the
// location of game.exe and it's WinProc which is what we need to put
// our code inside the game and execute it.
//
// We also get exported kernel functions dynamically instead of 
// calling them via vectors inside the game. The *only* criteria for
// this loader to work is that the instruction at WinProc is 5 bytes
// long. 
//
// <thohell@home.se>
//////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

#define DllExport   __declspec(dllexport)

//////////////////////////////////////////////////////////////////////
// LOADERDATA *loader in psi;
// -------------------------------------------------------------------
// Contains information passed from the loader.
//////////////////////////////////////////////////////////////////////
typedef struct loaderdata_t
{
	DWORD	LoaderMagic;
	DWORD	LoaderVersion;
	DWORD	CodeLocation;
	HWND	hwnd;
	DWORD	pid;
	HANDLE	hProcess;
	DWORD	pLoadLibraryA;
	DWORD	pFreeLibrary;
	DWORD	pGetModuleHandleA;
	char	ModuleName[0x10];
	DWORD	WinProcLocation;
	DWORD	WinProcPatchsize;

} LOADERDATA;


//////////////////////////////////////////////////////////////////////
// Version history.
// -------------------------------------------------------------------
// 1.00 2001-09-24 Original release
// 1.01 2001-09-24 Rewrote GetPatchAddress to generic GetBaseAddress
// 1.02 2001-09-28 Major rewrite to include support for NT 4.0
// 1.03 2001-10-16 Removed PSAPI code, it's buggy
// 1.04 2001-10-17 Rewrite to give back WinProc after load
// 1.05 2001-11-20 Added support for D2Loader
// 1.06 2001-12-21 Added logic for multiple sessions (D2Loader -multiclient)
//////////////////////////////////////////////////////////////////////
#define LOADERVERSION		MAKELONG(1,06)


//////////////////////////////////////////////////////////////////////
// Macros to make our life easier
//////////////////////////////////////////////////////////////////////
#define INST_CALL 0xe8
#define make_space __asm nop __asm nop __asm nop __asm nop __asm nop __asm nop
#define FUNCTLEN(func) ((DWORD)func##_END-(DWORD)func)


//////////////////////////////////////////////////////////////////////
// Data definitions for c code and assembler
//////////////////////////////////////////////////////////////////////
#define DATA				0x200			// Offset between data+code
#define LOADERMAGIC			0xD1AB101D
#define LOADERMAGICID		0x00
#define LOADERVERSIONID		0x04
#define CODELOCATION		0x08
#define GAME_HWND			0x0c
#define GAME_PID			0x10
#define GAME_HANDLE			0x14
#define PLOADLIBRARYA		0x18			
#define PFREELIBRARY		0x1c			
#define PGETMODULEHANDLEA	0x20			
#define MODULENAME			0x24			// char[0x10]
#define FILENAME			0x3c			// char[...]



//////////////////////////////////////////////////////////////////////
// Function Prototypes
//////////////////////////////////////////////////////////////////////
void WriteProcessBYTES(HANDLE hProcess, DWORD lpAddress, void* buf, int len);
void ReadProcessBYTES(HANDLE hProcess, DWORD lpAddress, void* buf, int len);
DWORD ReadProcessDWORD(HANDLE hProcess, DWORD lpAddress);
void Intercept(HANDLE hProcess, int inst, DWORD pOldCode, DWORD pNewCode, int nBytes);
void AsmCode(void);
void AsmCode_END(void);

// hd is a structure for the data required by the DLL load routine

// windowlist will hold a list of Diablo II Window handles
HWND windowlist[16];

// NumWindows holds the number of D2 windows found by EnumWindows()
int  NumWindows = 0;

//////////////////////////////////////////////////////////////////////
// WinMain
// -------------------------------------------------------------------
// The meat of the application.
//////////////////////////////////////////////////////////////////////
DllExport bool Go(HANDLE hProc, DWORD BaseAddress, HWND hwnd) /*(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)*/
{
	DWORD check;
	DWORD PatchAddress;
	DWORD DataAddress;
	DWORD WinProcAddress;
    char dllFullName[256];
    int mode;
	loaderdata_t hd;

	// Sets up NumWindows, and the windolist[] array of HWND's
    // See EnumWindowsProc() for deatils.....
	//EnumWindows(EnumWindowsProc, 0);
	
	//if(NumWindows == 0)
	//	MessageBox(NULL, "No D2 Windows found!", "Loader Error", MB_ICONERROR);

	// Loop through all the D2 windows found
	//for(x=0; x<NumWindows; x++) {

		// Set the HWND for the current window
		hd.hwnd = hwnd;
		
		// Get Diablo II's Process handle
		//GetWindowThreadProcessId(hd.hwnd, &hd.pid);
		hd.hProcess = hProc;
		if (!hd.hProcess) return false;
		
		// Find a good spot to put our code.  Look first for the original game.
		PatchAddress =  BaseAddress;
		PatchAddress += 0x400;
		DataAddress   = PatchAddress+DATA;

		// Get location of the game's WinProc
		WinProcAddress = GetClassLong(hd.hwnd,GCL_WNDPROC);
		if (!WinProcAddress) return false;

		// Initialize our data structure
		sprintf(hd.ModuleName, "%s", "botNET");

		hd.LoaderMagic      = LOADERMAGIC;
		hd.CodeLocation     = PatchAddress;
		hd.LoaderVersion    = LOADERVERSION;
		hd.WinProcLocation  = WinProcAddress;
		hd.WinProcPatchsize = 5;

		HMODULE hModule = GetModuleHandle("Kernel32.dll");
		if (!hModule) return false;

		// We're getting offsets to kernel functions from this userspace.
		// They will be the same inside the game, so we won't need to use
		// functions imported from the game.

		hd.pLoadLibraryA = (DWORD)GetProcAddress(hModule, "LoadLibraryA");
		if (!hd.pLoadLibraryA ) return false;

		hd.pFreeLibrary = (DWORD)GetProcAddress(hModule, "FreeLibrary");
		if (!hd.pFreeLibrary ) return false;

		hd.pGetModuleHandleA = (DWORD)GetProcAddress(hModule, "GetModuleHandleA");
		if (!hd.pGetModuleHandleA ) return false;

		// Get the first DWORD from DataAddress to see if we're loading or
		// unloading.  Set up the text for the message box
		ReadProcessBYTES(hd.hProcess, DataAddress, &check, sizeof(DWORD));
		if (check != LOADERMAGIC) { 
			mode = 1;		// We are loading
		} else {
			mode = 0;		// We are unloading
		}


		// Patch in our code
		WriteProcessBYTES(hd.hProcess, PatchAddress, &AsmCode, FUNCTLEN(AsmCode));
	
		// Patch in our data
		WriteProcessBYTES(hd.hProcess, DataAddress, &hd, sizeof(LOADERDATA));
	
		// Patch in full path+filename to server dll
		GetCurrentDirectory(255, dllFullName);
		strcat(dllFullName, "\\botNET.dll");
		WriteProcessBYTES(hd.hProcess, DataAddress+sizeof(LOADERDATA), dllFullName, strlen(dllFullName)+1);
	
		// Now hi-jack WinProc of the game to our code
		Intercept(hd.hProcess, INST_CALL, WinProcAddress, PatchAddress, 5);
	
		// Send WM_APP to toggle load/unload of the dll
		SendMessage(hd.hwnd, WM_APP,0,0);
	
		// Give back WinProc, we don't need it anymore
		Intercept(hd.hProcess, INST_CALL, PatchAddress, WinProcAddress, 5);

		// If we're unloading, then clear LOADERMAGIC from the data area
		if(mode == 0) {
			check = 0;
			WriteProcessBYTES(hd.hProcess, DataAddress, &check, sizeof(DWORD));
		}
	return true;
}

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved)
{

	return TRUE;
}

	


//////////////////////////////////////////////////////////////////////
// WriteProcessBYTES()
// -------------------------------------------------------------------
// Originally mousepads code
//////////////////////////////////////////////////////////////////////
void WriteProcessBYTES(HANDLE hProcess, DWORD lpAddress, void* buf, int len)
{
	DWORD oldprot,dummy = 0;
	VirtualProtectEx(hProcess, (void*) lpAddress, len, PAGE_READWRITE, &oldprot);
	WriteProcessMemory(hProcess, (void*) lpAddress, buf, len, 0);
	VirtualProtectEx(hProcess, (void*) lpAddress, len, oldprot, &dummy);
}

//////////////////////////////////////////////////////////////////////
// ReadProcessBYTES()
// -------------------------------------------------------------------
// Originally mousepads code
//////////////////////////////////////////////////////////////////////
void ReadProcessBYTES(HANDLE hProcess, DWORD lpAddress, void* buf, int len)
{
	DWORD oldprot, dummy = 0;
	VirtualProtectEx(hProcess, (void*) lpAddress, len, PAGE_READWRITE, &oldprot);
	ReadProcessMemory(hProcess, (void*) lpAddress, buf, len, 0);
	VirtualProtectEx(hProcess, (void*) lpAddress, len, oldprot, &dummy);
}


//////////////////////////////////////////////////////////////////////
// Intercept()
// -------------------------------------------------------------------
// Originally mousepads code but modified to also copy original code
// to the entrypoint of our code.
//////////////////////////////////////////////////////////////////////
void Intercept(HANDLE hProcess, int instruction, DWORD lpSource, DWORD lpDest, int len)
{
	BYTE* buffer = new BYTE[len];
	ReadProcessBYTES(hProcess, lpSource, buffer, len);
	WriteProcessBYTES(hProcess, lpDest, buffer, len);
	
	buffer[0] = instruction;
	*(DWORD*) (buffer + 1) = lpDest - (lpSource + 5);
	memset(buffer + 5, 0x90, len - 5);		// nops
	
	WriteProcessBYTES(hProcess, lpSource, buffer, len);
	
	delete buffer;
}

//////////////////////////////////////////////////////////////////////
// Asm_Code()
// -------------------------------------------------------------------
// This is our assembler routine that we patch in to the game. Since
// this code is relocateable, you can patch in anywhere in the game's
// address-space. We chose to put it at game.exe+0x400 bytes.
//
// This code hi-jacks WinProc and loads/unloads our dll when it 
// receives WM_APP.
//////////////////////////////////////////////////////////////////////
void _declspec(naked) AsmCode(void)
{
	__asm {
		make_space						// Make room for original code
		pushad
		call getaddress					// Get our EIP
getaddress:
		pop esi
		sub esi, 0x0c					// We now have base address in esi
		add esi, DATA					// Add offset to data
		mov eax, [esp+0x2c]				// esp+0x2c = uMsg
		cmp eax, WM_APP					// Check for our signal
		je do_our_stuff
hack_exit:
		popad
		ret
do_our_stuff:
		mov eax, esi
		add eax, MODULENAME
		push eax
		mov eax, [esi+PGETMODULEHANDLEA]
		call eax						// Is our dll loaded ?
		cmp eax, 0
		je load_dll						// No, load it
		push eax						// Yes, unload it
		mov eax, [esi+PFREELIBRARY]
		call eax
		jmp hack_exit
load_dll:							
		mov eax, esi
		add eax, FILENAME
		push eax
		mov eax, [esi+PLOADLIBRARYA]
		call eax
		jmp hack_exit
	}
}
void _declspec(naked) AsmCode_END(void){};
