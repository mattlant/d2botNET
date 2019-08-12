#ifndef PATCHER_H
#define PATCHER_H

namespace botNET
{
	namespace Imports
	{

		private __gc class Patcher
		{
		public:
			static void Initialize(bool install);

			static void PatchScreenDraw(bool install);
			static void PatchCrashHandler(bool install);
			static void PatchActChange(bool install);
			static void PatchEndGame(bool install);
			static void PatchNewGame(bool install);
			static void PatchPackets(bool install);
			static void PatchChatBox(bool install);
			static void PatchMessageHandler(bool install);
			static void PatchMouseMoves (bool install);

			//static bool PatchCALL(LPVOID lpvAddress, LPVOID lpvData);
			static UInt32 PatchCALL(DWORD CALLAddress, DWORD NewTarget);
			static void UnPatchCALL(DWORD CALLAddress, DWORD OldOffset);
			static void PatchMemory (DWORD address, DWORD length, BYTE *buffer, BYTE *original);
		};
	}
}


#endif