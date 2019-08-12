#include "botnet.h"
#include "importutils.h"


using namespace System::Diagnostics;

namespace botNET 
{
namespace Imports
{
	void Importer::Initialize()
	{
		Importer::_d2proc = Process::GetCurrentProcess();
		Importer::_d2hwnd = Importer::_d2proc->MainWindowHandle;
		ProcessModuleCollection* pmc = Importer::_d2proc->Modules;
		IEnumerator* epmc = pmc->GetEnumerator();
		ProcessModule* pm;
		while(epmc->MoveNext())
		{
			pm = static_cast<ProcessModule*>(epmc->Current);
			if(pm->FileName->ToLower()->EndsWith("d2client.dll"))
				Importer::_d2clientmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2common.dll"))
				Importer::_d2commonmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2win.dll"))
				Importer::_d2winmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2gfx.dll"))
				Importer::_d2gfxmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2gdi.dll"))
				Importer::_d2gdimodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2multi.dll"))
				Importer::_d2multimodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2launch.dll"))
				Importer::_d2launchmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2net.dll"))
				Importer::_d2netmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2game.dll"))
				Importer::_d2gamemodule = pm;
			if(pm->FileName->ToLower()->EndsWith("d2cmp.dll"))
				Importer::_d2cmpmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("bnclient.dll"))
				Importer::_bnclientmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("fog.dll"))
				Importer::_fogmodule = pm;
			if(pm->FileName->ToLower()->EndsWith("storm.dll"))
				Importer::_stormmodule = pm;
		}
	}

	IntPtr Importer::GetFunctionAddress(ProcessModule* module, int ordinal)
	{
		IntPtr temp = IntPtr(GetProcAddress((HMODULE)(module->BaseAddress.ToPointer()), MAKEINTRESOURCE(ordinal)));
		return temp;
	}

	Process* Importer::get_DiabloProcess()
	{
		return Importer::_d2proc;
	}

	IntPtr Importer::get_DiabloHWND()
	{
		return Importer::_d2hwnd;
	}

	ProcessModule* Importer::get_D2Client()
	{
		return Importer::_d2clientmodule;
	}

	ProcessModule* Importer::get_D2Common()
	{
		return Importer::_d2commonmodule;
	}

	ProcessModule* Importer::get_D2Gfx()
	{
		return Importer::_d2gfxmodule;
	}

	ProcessModule* Importer::get_D2Gdi()
	{
		return Importer::_d2gdimodule;
	}

	ProcessModule* Importer::get_D2Multi()
	{
		return Importer::_d2multimodule;
	}

	ProcessModule* Importer::get_D2Launch()
	{
		return Importer::_d2launchmodule;
	}

	ProcessModule* Importer::get_D2Net()
	{
		return Importer::_d2netmodule;
	}

	ProcessModule* Importer::get_D2Game()
	{
		return Importer::_d2gamemodule;
	}

	ProcessModule* Importer::get_BNClient()
	{
		return Importer::_bnclientmodule;
	}

	ProcessModule* Importer::get_D2Win()
	{
		return Importer::_d2winmodule;
	}

	ProcessModule* Importer::get_D2Cmp()
	{
		return Importer::_d2cmpmodule;
	}

	ProcessModule* Importer::get_Fog()
	{
		return Importer::_fogmodule;
	}

	ProcessModule* Importer::get_Storm()
	{
		return Importer::_stormmodule;
	}





}
}
