#ifndef IMPORTUTILS_H
#define IMPORTUTILS_H

using namespace System::Diagnostics;

namespace botNET 
{
namespace Imports
{
	public __gc class Importer
	{
	public:
		static IntPtr GetFunctionAddress(System::Diagnostics::ProcessModule* module, int ordinal);

		__property static Process* get_DiabloProcess(); 
		__property static IntPtr get_DiabloHWND(); 
		__property static ProcessModule* get_D2Client();
		__property static ProcessModule* get_D2Common();
		__property static ProcessModule* get_D2Win();
		__property static ProcessModule* get_D2Gfx();
		__property static ProcessModule* get_D2Gdi();
		__property static ProcessModule* get_D2Multi();
		__property static ProcessModule* get_D2Launch();
		__property static ProcessModule* get_D2Net();
		__property static ProcessModule* get_D2Game();
		__property static ProcessModule* get_D2Cmp();
		__property static ProcessModule* get_BNClient();
		__property static ProcessModule* get_Fog();
		__property static ProcessModule* get_Storm();


	public private:

		static void Initialize();

		static Process* _d2proc;
		static IntPtr _d2hwnd;
		static ProcessModule* _d2clientmodule;
		static ProcessModule* _d2commonmodule;
		static ProcessModule* _d2winmodule;
		static ProcessModule* _d2gfxmodule;
		static ProcessModule* _d2gdimodule;
		static ProcessModule* _d2multimodule;
		static ProcessModule* _d2launchmodule;
		static ProcessModule* _d2netmodule;
		static ProcessModule* _d2gamemodule;
		static ProcessModule* _d2cmpmodule;
		static ProcessModule* _bnclientmodule;
		static ProcessModule* _fogmodule;
		static ProcessModule* _stormmodule;
	};

}

}

#endif