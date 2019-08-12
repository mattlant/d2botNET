#include "botnet.h"
#include "fog.h"
#include "importutils.h"


namespace botNET
{
	namespace Imports
	{

		void FOG::Initialize()
		{
			BaseAddress = Importer::Fog->BaseAddress.ToInt32();

			FOG::fptrReceiveRealmPacket = reinterpret_cast<void*> (BaseAddress + 0x1430);
			FOG::fptrErrorReasonWriter = reinterpret_cast<void*> (BaseAddress + 0xEEA0);

			FOG::fptrMemAlloc = Importer::GetFunctionAddress(Importer::Fog, 10045).ToPointer();
			FOG::fptrMemDeAlloc = Importer::GetFunctionAddress(Importer::Fog, 10046).ToPointer();
			FOG::fptrSend = Importer::GetFunctionAddress(Importer::Fog, 10007).ToPointer();
			FOG::fptrGetComputerInfo = Importer::GetFunctionAddress(Importer::Fog, 10226).ToPointer();

			FOG::asmCallErrorReasonWriter = (BaseAddress + 0xF162);
			FOG::asmCallExceptionHandlerGetComputerInfo = (BaseAddress + 0xE712);
			FOG::asmCallErrorHandlerGetComputerInfo = (BaseAddress + 0xEEE9);
			FOG::asmCallReceiveRealmPacket = (BaseAddress + 0x16D1);
			FOG::asmCallFOGSend = (BaseAddress + 0x135A);
		}


		//Implemenation
		void FOG::ReceiveRealmPacket(BYTE * Packet, void* unk, DWORD aLength)
		{
			__asm
			{
				push aLength
				mov edx, unk
				mov ecx, Packet
				mov eax, FOG::fptrReceiveRealmPacket		;0x1430
				call eax
			}
		}

		void FOG::ErrorReasonWriter(DWORD unk1, DWORD unk2, DWORD unk3, char* reason, DWORD unk5)
		{
			__asm
			{
				push unk5
				push reason
				push unk3
				mov edx, unk2
				mov ecx, unk1
				mov eax, FOG::fptrErrorReasonWriter		;0xEEA0
				call eax
			}
		}

		void * FOG::MemAlloc(int Mempool, int isize, int unk, int line, const char * file)
		{
			void * retval;
			__asm
			{
				push file
				push line
				push unk
				mov edx, isize
				mov ecx, Mempool
				mov eax, FOG::fptrMemAlloc		;-0x273D
				call eax
				mov eax, retval
			}
			return retval;
		}

		void FOG::MemDeAlloc(int Mempool, void * MemChunk, int unk, int line, const char * file)
		{
			__asm
			{
				push file
				push line
				push unk
				mov edx, MemChunk
				mov ecx, Mempool
				mov eax, FOG::fptrMemDeAlloc		;-0x273E
				call eax
			}
		}

		void FOG::Send(DWORD* bnClient, LPBYTE lpBuf, DWORD len)
		{
			__asm
			{
				push len
				mov edx, lpBuf
				mov ecx, bnClient
				mov eax, FOG::fptrSend		;-0x2717
				call eax
			}
		}

		void FOG::GetComputerInfo(DWORD unk1, DWORD unk5)
		{
			__asm
			{
				mov edx, unk5
				mov ecx, unk1
				mov eax, FOG::fptrGetComputerInfo		;-0x27F2
				call eax
			}
		}


	}

}
