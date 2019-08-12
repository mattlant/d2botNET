#include "botnet.h"
#include "patcher.h"
#include "d2client.h"
#include "d2win.h"
#include "d2multi.h"
#include "bnclient.h"
#include "log.h"
#include "globalmessagehandlerpatch.h"
#include "chatlinehandlerpatch.h"
#include "screendrawpatch.h"
#include "gamepatch.h"
#include "crashpatch.h"
#include "packetpatch.h"
#include "fog.h"

namespace botNET
{
	namespace Imports
	{



		void Patcher::Initialize(bool install)
		{
			PatchMessageHandler(install);
			PatchChatBox(install);
			PatchPackets(install);
			PatchScreenDraw(install);
			PatchActChange(install);
			PatchEndGame(install);
			PatchNewGame(install);
			PatchCrashHandler(install);
			PatchMouseMoves(install);
		}

		void Patcher::PatchMemory (DWORD address, DWORD length, BYTE *buffer, BYTE *original)
		{
			DWORD dwOldProtect, dwOldProtect2;
			VirtualProtect((void*)address, length, PAGE_READWRITE, &dwOldProtect);
			if (original)
				CopyMemory ((void *)original, (void *)address, length);
			CopyMemory ((void *)address, (void *)buffer, length);
			VirtualProtect((void*)address, length, dwOldProtect, &dwOldProtect2);
		}

		void Patcher::PatchMouseMoves (bool install)
		{
			if (install)
			{
				BYTE nopBuffer[] = {0x90,0x90,0x90,0x90,0x90};
				PatchMemory (D2CLIENT::BaseAddress + 0x83647, 5, nopBuffer, D2CLIENT::oldMouseMove1);
				PatchMemory (D2CLIENT::BaseAddress + 0x83694, 5, nopBuffer, D2CLIENT::oldMouseMove2);
				PatchMemory (D2CLIENT::BaseAddress + 0x8372E, 5, nopBuffer, D2CLIENT::oldMouseMove3);
				PatchMemory (D2CLIENT::BaseAddress + 0x83773, 5, nopBuffer, D2CLIENT::oldMouseMove4);
			}
			else
			{
				PatchMemory (D2CLIENT::BaseAddress + 0x83647, 5, D2CLIENT::oldMouseMove1, NULL);
				PatchMemory (D2CLIENT::BaseAddress + 0x83694, 5, D2CLIENT::oldMouseMove2, NULL);
				PatchMemory (D2CLIENT::BaseAddress + 0x8372E, 5, D2CLIENT::oldMouseMove3, NULL);
				PatchMemory (D2CLIENT::BaseAddress + 0x83773, 5, D2CLIENT::oldMouseMove4, NULL);
			}
		}

		void Patcher::PatchScreenDraw(bool install)
		{
			if(install)
			{
				D2CLIENT::oldCallDrawPanel = 
					PatchCALL(D2CLIENT::asmCallDrawPanel, (DWORD)&botNET::Imports::Patches::DrawPanelSTUB);
				D2CLIENT::oldCallDrawScreen = 
					PatchCALL(D2CLIENT::asmCallDrawScreen, (DWORD)&botNET::Imports::Patches::DrawIGScreenSTUB);
				D2WIN::oldCallDrawScreen = 
					PatchCALL(D2WIN::asmCallDrawScreen, (DWORD)&botNET::Imports::Patches::DrawOOGScreenSTUB);
				D2CLIENT::oldCallDrawAutoMap = 
					PatchCALL(D2CLIENT::asmCallDrawAutoMap, (DWORD)&botNET::Imports::Patches::DrawAutoMapSTUB);
			}
			else
			{
				UnPatchCALL(D2CLIENT::asmCallDrawPanel, D2CLIENT::oldCallDrawPanel);
				UnPatchCALL(D2CLIENT::asmCallDrawScreen, D2CLIENT::oldCallDrawScreen);
				UnPatchCALL(D2WIN::asmCallDrawScreen, D2WIN::oldCallDrawScreen);
				UnPatchCALL(D2CLIENT::asmCallDrawAutoMap, D2CLIENT::oldCallDrawAutoMap);
			}

		}

		void Patcher::PatchPackets(bool install)
		{
			if(install)
			{
				//Game RECV
				D2CLIENT::oldCallGameReceivePacketHandlerNew = 
					PatchCALL(D2CLIENT::asmCallGameReceivePacketHandlerNew, (DWORD)&botNET::Imports::Patches::GamePacketReceiveSTUB);
				//BN RECV
				BNCLIENT::oldCallReceiveBNPacket = 
                    PatchCALL(BNCLIENT::asmCallReceiveBNPacket, (DWORD)&botNET::Imports::Patches::BNPacketReceiveSTUB);
				//REALM RECV
				FOG::oldCallReceiveRealmPacket = 
                    PatchCALL(FOG::asmCallReceiveRealmPacket, (DWORD)&botNET::Imports::Patches::RealmPacketReceiveSTUB);
				//GAME SEND
				D2CLIENT::oldCallD2NETGameSend0 = 
                    PatchCALL(D2CLIENT::asmCallD2NETGameSend0, (DWORD)&botNET::Imports::Patches::GamePacketSendSTUB);
				D2CLIENT::oldCallD2NETGameSend1 = 
                    PatchCALL(D2CLIENT::asmCallD2NETGameSend1, (DWORD)&botNET::Imports::Patches::GamePacketSendSTUB);
				//BN SEND
				//BNCLIENT::oldCallFOGSend = 
                //    PatchCALL(BNCLIENT::asmCallFOGSend, (DWORD)&botNET::Imports::Patches::BN_RealmPacketSendSTUB);
				//REALM SEND
				//FOG::oldCallFOGSend = 
                 //   PatchCALL(FOG::asmCallFOGSend, (DWORD)&botNET::Imports::Patches::BN_RealmPacketSendSTUB);
			}
			else
			{
					UnPatchCALL(D2CLIENT::asmCallGameReceivePacketHandlerNew, D2CLIENT::oldCallGameReceivePacketHandlerNew);
                    UnPatchCALL(BNCLIENT::asmCallReceiveBNPacket, BNCLIENT::oldCallReceiveBNPacket);
                    UnPatchCALL(FOG::asmCallReceiveRealmPacket, FOG::oldCallReceiveRealmPacket);
                    UnPatchCALL(D2CLIENT::asmCallD2NETGameSend0, D2CLIENT::oldCallD2NETGameSend0);
                    UnPatchCALL(D2CLIENT::asmCallD2NETGameSend1, D2CLIENT::oldCallD2NETGameSend1);
                    UnPatchCALL(BNCLIENT::asmCallFOGSend, BNCLIENT::oldCallFOGSend);
                    UnPatchCALL(FOG::asmCallFOGSend, FOG::oldCallFOGSend);
			}
		}

		void Patcher::PatchCrashHandler(bool install)
		{
			if(install)
			{
				FOG::oldCallExceptionHandlerGetComputerInfo = 
					PatchCALL(FOG::asmCallExceptionHandlerGetComputerInfo, (DWORD)&botNET::Imports::Patches::ExceptionSTUB);
				FOG::oldCallErrorHandlerGetComputerInfo = 
                    PatchCALL(FOG::asmCallErrorHandlerGetComputerInfo, (DWORD)&botNET::Imports::Patches::ErrorSTUB);
			}
			else
			{
				UnPatchCALL(FOG::asmCallExceptionHandlerGetComputerInfo, FOG::oldCallExceptionHandlerGetComputerInfo);
                UnPatchCALL(FOG::asmCallErrorHandlerGetComputerInfo, FOG::oldCallErrorHandlerGetComputerInfo);
			}
		}

		void Patcher::PatchActChange(bool install)
		{
			if(install)
			{
				D2CLIENT::oldCallD2CMPSetAct = 
					PatchCALL(D2CLIENT::asmCallD2CMPSetAct, (DWORD)&botNET::Imports::Patches::ActChangeSTUB);
			}
			else
			{
				UnPatchCALL(D2CLIENT::asmCallD2CMPSetAct, D2CLIENT::oldCallD2CMPSetAct);
			}
		}

		void Patcher::PatchNewGame(bool install)
		{
			if (install)
			{
				D2CLIENT::oldJoinGame =
					PatchCALL (D2CLIENT::asmJoinGame, (DWORD)&botNET::Imports::Patches::NewGameSTUB);
			}
			else
			{
				UnPatchCALL (D2CLIENT::asmJoinGame, D2CLIENT::oldJoinGame);
			}
		}

		void Patcher::PatchEndGame(bool install)
		{
			if (install)
			{
				D2CLIENT::oldLeaveGame =
					PatchCALL (D2CLIENT::asmLeaveGame, (DWORD)&botNET::Imports::Patches::EndGameSTUB);
			}
			else
			{
				UnPatchCALL (D2CLIENT::asmLeaveGame, D2CLIENT::oldLeaveGame);
			}
		}

		/*void Patcher::PatchEndGame(bool install)
		{
			if(install)
			{
				D2CLIENT::oldCallEndGameChangePalette =
                    PatchCALL(D2CLIENT::asmCallEndGameChangePalette, (DWORD)&botNET::Imports::Patches::EndGameSTUB);
			}
			else
			{
                UnPatchCALL(D2CLIENT::asmCallEndGameChangePalette, D2CLIENT::oldCallEndGameChangePalette);
			}
		}*/

		void Patcher::PatchChatBox(bool install)
		{
			DWORD Offset = 0;
			if(install)
			{
				//IG
				D2CLIENT::oldCallChatBoxSend = 
					PatchCALL(D2CLIENT::asmCallChatBoxSend, (DWORD)&botNET::Imports::Patches::ChatBoxHandlerSTUB);
				//OOG
				D2MULTI::oldCallChatLineSend = 
                    PatchCALL(D2MULTI::asmCallChatLineSend, (DWORD)&botNET::Imports::Patches::ChatLineHandlerSTUB);
			}
			else
			{
				UnPatchCALL(D2CLIENT::asmCallChatBoxSend, D2CLIENT::oldCallChatBoxSend);
                UnPatchCALL(D2MULTI::asmCallChatLineSend, D2MULTI::oldCallChatLineSend);
			}
		}

		void Patcher::PatchMessageHandler(bool install)
		{
			DWORD Offset = 0;
			if(install)
			{
				D2CLIENT::oldCallIGGlobalMessageHandler = 
					PatchCALL(D2CLIENT::asmCallIGGlobalMessageHandler, (DWORD)&botNET::Imports::Patches::MessageHandlerSTUB);
				D2WIN::oldCallOOGGlobalMessageHandler = 
                    PatchCALL(D2WIN::asmCallOOGGlobalMessageHandler, (DWORD)&botNET::Imports::Patches::MessageHandlerSTUB);
			}
			else
			{
				UnPatchCALL(D2CLIENT::asmCallIGGlobalMessageHandler, D2CLIENT::oldCallIGGlobalMessageHandler);
				UnPatchCALL(D2WIN::asmCallOOGGlobalMessageHandler, D2WIN::oldCallOOGGlobalMessageHandler);
			}
		}

		UInt32 Patcher::PatchCALL(DWORD CALLAddress, DWORD NewTarget)
		{
			DWORD Offset = NewTarget - (CALLAddress + 5);
			DWORD AddressToWrite = CALLAddress+1;
			DWORD OldOffset;// = *(DWORD*)AddressToWrite;

			//DWORD dwOldProtect, dwOldProtect2;

			Patcher::PatchMemory (AddressToWrite, 4, (BYTE *)&Offset, (BYTE *)&OldOffset);

			/*if (VirtualProtect((void*)AddressToWrite, 4, PAGE_READWRITE, &dwOldProtect) == FALSE)
				return 0;
			//Change to memcpy
			CopyMemory((void*)AddressToWrite, &Offset, 4);
			//if (WriteProcessMemory(GetCurrentProcess(), (void*)AddressToWrite, &Offset, 4, NULL) == FALSE)
			//	return false;
			if (VirtualProtect((void*)AddressToWrite, 4, dwOldProtect, &dwOldProtect2) == FALSE)
				return 0;*/
			return OldOffset;
		}

		void Patcher::UnPatchCALL(DWORD CALLAddress, DWORD OldOffset)
		{
			DWORD Offset = OldOffset;
			DWORD AddressToWrite = CALLAddress+1;

			Patcher::PatchMemory (AddressToWrite, 4, (BYTE *)&Offset, NULL);

			/*DWORD dwOldProtect, dwOldProtect2;

			VirtualProtect((void*)AddressToWrite, 4, PAGE_READWRITE, &dwOldProtect);
			CopyMemory((void*)AddressToWrite, &Offset, 4);
			VirtualProtect((void*)AddressToWrite, 4, dwOldProtect, &dwOldProtect2);*/
		}


	}


}