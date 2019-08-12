#ifndef FOG_H
#define FOG_H



namespace botNET
{
	namespace Imports
	{
		__nogc class FOG
		{
		public:
			static void Initialize();

			static UInt32 BaseAddress;

			[DllImport("fog", EntryPoint="#10070", CallingConvention=CallingConvention::StdCall)]
			static void RealmSend(void* bnData, BYTE* packet, DWORD len);

			//Functions and their pointers'
			static void ReceiveRealmPacket(BYTE * Packet, void* unk, DWORD Length);
			static void* fptrReceiveRealmPacket; //0x1430

			static void ErrorReasonWriter(DWORD unk1, DWORD unk2, DWORD unk3, char* reason, DWORD unk5);
			static void* fptrErrorReasonWriter; //0xEEA0

			static void * MemAlloc(int Mempool, int size, int unk, int line, const char * file);
			static void* fptrMemAlloc; //-0x273D

			static void MemDeAlloc(int Mempool, void * MemChunk, int unk, int line, const char * file);
			static void* fptrMemDeAlloc; //-0x273E

			static void Send(DWORD *bnClient, LPBYTE lpBuf, DWORD len);
			static void* fptrSend; //-0x2717

			static void GetComputerInfo(DWORD unk1, DWORD unk5);
			static void* fptrGetComputerInfo; //-0x27F2



			static DWORD asmCallErrorReasonWriter;
			static DWORD asmCallExceptionHandlerGetComputerInfo;
			static DWORD asmCallErrorHandlerGetComputerInfo;
			static DWORD asmCallReceiveRealmPacket;

			static DWORD asmCallFOGSend;

			static DWORD oldCallErrorReasonWriter;
			static DWORD oldCallExceptionHandlerGetComputerInfo;
			static DWORD oldCallErrorHandlerGetComputerInfo;
			static DWORD oldCallReceiveRealmPacket;

			static DWORD oldCallFOGSend;
		};


	}


}

#endif