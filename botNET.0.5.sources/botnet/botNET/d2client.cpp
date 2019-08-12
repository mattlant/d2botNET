#include "botnet.h"
#include "d2client.h"
#include "importutils.h"
#include ".\d2cmp.h"

namespace botNET
{
	namespace Imports
	{

		void D2CLIENT::Initialize()
		{
			BaseAddress = Importer::D2Client->BaseAddress.ToInt32();

			D2CLIENT::AutomapLayer = reinterpret_cast<d2_AutomapLayer **> (BaseAddress + 0x11C154);	//1.11b
			D2CLIENT::Area = reinterpret_cast<int*> (BaseAddress + 0x1233F4);						//1.11b
			D2CLIENT::Act = reinterpret_cast<int*> (BaseAddress + 0x11BF2C);						//1.11b
			D2CLIENT::Difficulty = reinterpret_cast<int*> (BaseAddress + 0x11C2A8);					//1.11b
			D2CLIENT::MsgId = reinterpret_cast<DWORD*> (BaseAddress + 0x11B84E);					//1.11b
			D2CLIENT::Ping = reinterpret_cast<DWORD*> (BaseAddress + 0x11A2A4);						//1.11b
			D2CLIENT::AlwaysRun = reinterpret_cast<int*> (BaseAddress + 0x11C304);					//1.11b
			D2CLIENT::SlotsWithPotion = reinterpret_cast<int*> (BaseAddress + 0x11BA30);			//1.11b
			D2CLIENT::CurrentWeaponSlot = reinterpret_cast<int*> (BaseAddress + 0x11BC38);			//1.11b
			D2CLIENT::LastChatMessage = reinterpret_cast<wchar_t*> (BaseAddress + 0x11D590);		//1.11b
			D2CLIENT::LastMessage = reinterpret_cast<wchar_t*> (BaseAddress + 0x11B830);	//CHECK was 0x12E3C2
			D2CLIENT::MessageTimer = reinterpret_cast<DWORD*> (BaseAddress + 0x11BB34);				//1.11b
			D2CLIENT::ClickWpId = reinterpret_cast<DWORD*> (BaseAddress + 0x11B6AD);				//1.11b
			D2CLIENT::NpcMenu = reinterpret_cast<d2_NpcMenu **> (BaseAddress + 0x11C3D4);			//1.11b
			D2CLIENT::NpcMainMenuFunctionTable = reinterpret_cast<d2_NpcMainMenuFunctionTable*> ( BaseAddress + 0xF0AF0 );	//1.11b
			D2CLIENT::NpcMainMenuTableCount = reinterpret_cast<int*> ( BaseAddress + 0xF1240 );		//1.11b
			D2CLIENT::ClickTrade = reinterpret_cast<DWORD*> (BaseAddress + 0x11BE94);				//1.11b
			D2CLIENT::d2MouseXa = reinterpret_cast<DWORD*> (BaseAddress + 0x11B418);				//1.11b
			D2CLIENT::d2MouseYa = reinterpret_cast<DWORD*> (BaseAddress + 0x11B414);				//1.11b
			D2CLIENT::d2MouseXb = reinterpret_cast<DWORD*> (BaseAddress + 0x11388C);
			D2CLIENT::d2MouseYb = reinterpret_cast<DWORD*> (BaseAddress + 0x113894);
			D2CLIENT::PlayerInventoryLayout = reinterpret_cast<d2_InventoryLayout*> (BaseAddress + 0x103708);	//1.11b
			D2CLIENT::StoreInventoryLayout = reinterpret_cast<d2_InventoryLayout*> (BaseAddress + 0x1036D8);	//1.11b
			D2CLIENT::TradeInventoryLayout = reinterpret_cast<d2_InventoryLayout*> (BaseAddress + 0x1035B0);	//1.11b
			D2CLIENT::CubeInventoryLayout = reinterpret_cast<d2_InventoryLayout*> (BaseAddress + 0x113880);	//NOT DWORD in 1.10!!
			D2CLIENT::StashInventoryLayout = reinterpret_cast<d2_InventoryLayout*> (BaseAddress + 0x1035F8);	//1.11b
			D2CLIENT::MouseX = reinterpret_cast<DWORD*> (BaseAddress + 0x11B418);					//1.11b
			D2CLIENT::MouseY = reinterpret_cast<DWORD*> (BaseAddress + 0x11B414);					//1.11b
			D2CLIENT::CursorTableSize = reinterpret_cast<int*> (BaseAddress + 0xF4AF4);				//1.11b
			D2CLIENT::MaxMouseX = reinterpret_cast<DWORD*> (BaseAddress +0xF4FC4);					//1.11b
			D2CLIENT::MaxMouseY = reinterpret_cast<DWORD*> (BaseAddress + 0xF4FC8);					//1.11b
			D2CLIENT::F13Skill = reinterpret_cast<DWORD*> (BaseAddress + 0xFD298);					//1.11b
			D2CLIENT::F13SkillHand = reinterpret_cast<DWORD*> (BaseAddress + 0xFD388);				//1.11b
			D2CLIENT::HasHighlight = reinterpret_cast<bool*> (BaseAddress + 0x11C330);				//1.11b
			D2CLIENT::HighlightUnitType = reinterpret_cast<int*> (BaseAddress + 0x10B9CC);
			D2CLIENT::HighlightUnitId = reinterpret_cast<int*> (BaseAddress + 0x10B9D0);
			D2CLIENT::ghRoom = reinterpret_cast<Room1 **> (BaseAddress + 0x10B9F8);
			D2CLIENT::ScreenYOffset = reinterpret_cast<DWORD*> (BaseAddress + 0x10B9B8);
			D2CLIENT::ScreenXOffset = reinterpret_cast<DWORD*> (BaseAddress + 0x10B9BC);
			D2CLIENT::ClientScreenWidth = reinterpret_cast<int*> (BaseAddress + 0xFA704);
			D2CLIENT::ClientScreenHeight = reinterpret_cast<int*> (BaseAddress + 0xFA700);
			D2CLIENT::SelectedInventoryUnit = reinterpret_cast<UnitAny **> (BaseAddress + 0x1158F0);
			D2CLIENT::LastMessageLogMessage = reinterpret_cast<d2_MessageLogMessage **> (BaseAddress + 0x119ED8);
			D2CLIENT::MessageLogCount = reinterpret_cast<WORD*> (BaseAddress + 0x119EDC);
			//D2CLIENT::FirstHandlerTable = reinterpret_cast<D2HANDLER*> (BaseAddress + 0xD5818);
			//D2CLIENT::SecondHandlerTable = reinterpret_cast<D2HANDLER*> (BaseAddress + 0xD87F0);
			//D2CLIENT::ThirdHandlerTable = reinterpret_cast<D2HANDLER*> (BaseAddress + 0x*/);
			D2CLIENT::IsPaused = reinterpret_cast<bool*> (BaseAddress + 0x11C23C);
			D2CLIENT::IsAutoMapOn = reinterpret_cast<bool*> (BaseAddress + 0x11A754);
			D2CLIENT::FirstRosterPet = reinterpret_cast<RosterPet **> (BaseAddress + 0x10B9A0);
			D2CLIENT::FirstRosterPlayer = reinterpret_cast<Roster **> (BaseAddress + 0x10B994);
			D2CLIENT::PlayerUnit = reinterpret_cast<UnitPlayer **> (BaseAddress + 0x11C200);
			D2CLIENT::UnitTable = reinterpret_cast<UnitAny **> (BaseAddress + 0x11AA00);
			D2CLIENT::FPS = reinterpret_cast<DWORD*> (BaseAddress + 0xFA96C);
			D2CLIENT::Skip = reinterpret_cast<DWORD*> (BaseAddress + 0x107780);
			D2CLIENT::AutoMapDiv = reinterpret_cast<int*> (BaseAddress + 0xD7BC0);
			D2CLIENT::AutoMapXSub = reinterpret_cast<int*> (BaseAddress + 0x1119D8);
			D2CLIENT::AutoMapYSub = reinterpret_cast<int*> (BaseAddress + 0x1119DC);
			D2CLIENT::AutoMapLeftBound = reinterpret_cast<int*> (BaseAddress + 0x111A08);
			D2CLIENT::AutoMapRightBound = reinterpret_cast<int*> (BaseAddress + 0x111A10);
			D2CLIENT::AutoMapTopBound = reinterpret_cast<int*> (BaseAddress + 0x111A0C);
			D2CLIENT::AutoMapBottomBound = reinterpret_cast<int*> (BaseAddress + 0x111A14);
			D2CLIENT::ClickItemCheck = reinterpret_cast<DWORD*> (BaseAddress + 0x115D37);
			D2CLIENT::ItemPriceGameInfoUnk = reinterpret_cast<void **> (BaseAddress + 0x115D13);
			D2CLIENT::ClickEquipmentLocationBase = reinterpret_cast<DWORD **> (BaseAddress + 0xD92AC);
			D2CLIENT::InteractedNPCUniqueID = reinterpret_cast<DWORD*> (BaseAddress + 0x115CF5);
			D2CLIENT::IsInteractedWithNPC = reinterpret_cast<BOOL*> (BaseAddress + 0x115CF9);
			D2CLIENT::InteractedNPCClassID = reinterpret_cast<DWORD*> (BaseAddress + 0x115CFD);
			D2CLIENT::InteractedWPUniqueID = reinterpret_cast<DWORD*> (BaseAddress + 0x11A9B5);
			D2CLIENT::IsNotInteractedWithWP = reinterpret_cast<bool*> (BaseAddress + 0x11A9BD);
			D2CLIENT::ShopCursorMode = reinterpret_cast<DWORD*> (BaseAddress + 0x121AC8);
			D2CLIENT::CursorMode = reinterpret_cast<DWORD*> (BaseAddress + 0x121AD4);
			D2CLIENT::IdentifyingScroll = reinterpret_cast<UnitItem**> (BaseAddress + 0x121AA4);


			D2CLIENT::fptrPrintScreenMessage = reinterpret_cast<void*> (BaseAddress + 0x16780);	//1.11b
			//D2CLIENT::fptrUnloadUIImage = reinterpret_cast<void*> (BaseAddress + 0x1140);		//INLINED!
			D2CLIENT::fptrGetGameStatus = reinterpret_cast<void*> (BaseAddress + 0x9440);
			D2CLIENT::fptrGetGameType = reinterpret_cast<void*> (BaseAddress + 0xC080);
			D2CLIENT::fptrQuitGame = reinterpret_cast<void*> (BaseAddress + 0xC2F0);
			D2CLIENT::fptrTransferGold = reinterpret_cast<void*> (BaseAddress + 0xD9E0);
			D2CLIENT::fptrDropGold = reinterpret_cast<void*> (BaseAddress + 0xDA40);
			D2CLIENT::fptrGetMouseXOffset = reinterpret_cast<void*> (BaseAddress + 0x15890);
			D2CLIENT::fptrGetMouseYOffset = reinterpret_cast<void*> (BaseAddress + 0x158A0);
			D2CLIENT::fptrGetSelectedUnit = reinterpret_cast<void*> (BaseAddress + 0x15A20);
			D2CLIENT::fptrSetSelectedUnit = reinterpret_cast<void*> (BaseAddress + 0x15AE0);
			D2CLIENT::fptrClearSelectedUnit = reinterpret_cast<void*> (BaseAddress + 0x15D40);
			D2CLIENT::fptrChatPressHandler = reinterpret_cast<void*> (BaseAddress + 0x32890);
			D2CLIENT::fptrToggleChatBox = reinterpret_cast<void*> (BaseAddress + 0x337B0);
			D2CLIENT::fptrKeyPressHandler = reinterpret_cast<void*> (BaseAddress + 0x35A00);
			D2CLIENT::fptrWeaponSwitch = reinterpret_cast<void*> (BaseAddress + 0x4D2B0);
			D2CLIENT::fptrusePotion = reinterpret_cast<void*> (BaseAddress + 0x618A0);
			D2CLIENT::fptrPrintChatMessage = reinterpret_cast<void*> (BaseAddress + 0x7C600);
			D2CLIENT::fptrPrintMessage = reinterpret_cast<void*> (BaseAddress + 0x7E120);
			D2CLIENT::fptrLoadUIImage = reinterpret_cast<void*> (BaseAddress + 0x80100);
			D2CLIENT::fptrManipUI = reinterpret_cast<void*> (BaseAddress + 0x83260);
			D2CLIENT::fptrGetUIState = reinterpret_cast<void*> (BaseAddress + 0x83230);
			D2CLIENT::fptrGetUnitFromId = reinterpret_cast<void*> (BaseAddress + 0x869F0);
			D2CLIENT::fptrUnitTestSelect = reinterpret_cast<void*> (BaseAddress + 0x886F0);
			D2CLIENT::fptrClickNpcMenuUI = reinterpret_cast<void*> (BaseAddress + 0x35DC0);
			D2CLIENT::fptrClickScreen = reinterpret_cast<void*> (BaseAddress + 0x46E60);
			D2CLIENT::fptrClickTradeUIdown = reinterpret_cast<void*> (BaseAddress + 0x4A1C0);
			D2CLIENT::fptrClickTradeUIup = reinterpret_cast<void*> (BaseAddress + 0x4A850);
			D2CLIENT::fptrClickStashUIdown = reinterpret_cast<void*> (BaseAddress + 0x4BAD0);
			D2CLIENT::fptrClickStashUIup = reinterpret_cast<void*> (BaseAddress + 0x4C030);
			D2CLIENT::fptrSetSkill = reinterpret_cast<void*> (BaseAddress + 0x7A130);
			D2CLIENT::fptrGetUnit = reinterpret_cast<void*> (BaseAddress + 0x869F0);
			D2CLIENT::fptrUpdatePlayerStruct = reinterpret_cast<void*> (BaseAddress + 0x88390);
			D2CLIENT::fptrGetPlayerUnit = reinterpret_cast<void*> (BaseAddress + 0x883D0);
			D2CLIENT::fptrGetPlayerRoom = reinterpret_cast<void*> (BaseAddress + 0x89370);
			D2CLIENT::fptrGetNameFromUnit = reinterpret_cast<void*> (BaseAddress + 0x897F0);
			D2CLIENT::fptrMouseClick = reinterpret_cast<void*> (BaseAddress + 0xA9920);
			D2CLIENT::fptrMouseClickTest = reinterpret_cast<void*> (BaseAddress + 0xA999F);
			D2CLIENT::fptrExitGame = reinterpret_cast<void*> (BaseAddress + 0xC06B3);
			D2CLIENT::fptrCancelStore = reinterpret_cast<void*> (BaseAddress + 0x59FE0);
			D2CLIENT::fptrCancelStash = reinterpret_cast<void*> (BaseAddress + 0x4C650);
			D2CLIENT::fptrCancelWaypoint = reinterpret_cast<void*> (BaseAddress + 0x862E0);
			D2CLIENT::fptrCancelNPCChat = reinterpret_cast<void*> (BaseAddress + 0x56BC0);
			D2CLIENT::fptrRightClickInventoryItem = reinterpret_cast<void*> (BaseAddress + 0x48C60);
			D2CLIENT::fptrLeftClickInventoryItem = reinterpret_cast<void*> (BaseAddress + 0x475C0);
			D2CLIENT::fptrRightClickTradeItem = reinterpret_cast<void*> (BaseAddress + 0x5A260);
			D2CLIENT::fptrLeftClickBelt = reinterpret_cast<void*> (BaseAddress + 0x612E0);
			D2CLIENT::fptrGetItemStatsString = reinterpret_cast<void*> (BaseAddress + 0x519C0);
			D2CLIENT::fptrGetItemNameString = reinterpret_cast<void*> (BaseAddress + 0x3D360);
			D2CLIENT::fptrLLScreenPrint3 = reinterpret_cast<void*> (BaseAddress + 0x1000);
			D2CLIENT::fptrRevealAutomapRoom = reinterpret_cast<void*> (BaseAddress + 0x2D180);
			D2CLIENT::fptrUseStatPoint = reinterpret_cast<void*> (BaseAddress + 0xD990);
			D2CLIENT::fptrUseSkillPoint = reinterpret_cast<void*> (BaseAddress + 0x78529);
			D2CLIENT::fptrPartyUIButton = reinterpret_cast<void*> (BaseAddress + 0xDB20);
			D2CLIENT::fptrPrePacketOther1 = reinterpret_cast<void*> (BaseAddress + 0xD990);
			D2CLIENT::fptrPrePacket1 = reinterpret_cast<void*> (BaseAddress + 0xDA20);
			D2CLIENT::fptrPrePacket2 = reinterpret_cast<void*> (BaseAddress + 0xDA40);
			D2CLIENT::fptrPrePacket3 = reinterpret_cast<void*> (BaseAddress + 0xDA70);
			D2CLIENT::fptrPrePacket4 = reinterpret_cast<void*> (BaseAddress + 0xDAA0);
			D2CLIENT::fptrCheckDrawUnitToAutoMap = reinterpret_cast<void*> (BaseAddress + 0x2E8F0);
			D2CLIENT::fptrDrawAutoMap = reinterpret_cast<void*> (BaseAddress + 0x2E510);
			D2CLIENT::fptrChatBoxSend = reinterpret_cast<void*> (BaseAddress + 0xDB50);
			D2CLIENT::fptrGameReceivePacketHandlerNew = reinterpret_cast<void*> (BaseAddress + 0x150B0);

			D2CLIENT::fptrDrawPanel = reinterpret_cast<void*> (BaseAddress + 0x5F480);

			D2CLIENT::asmCallDrawAutoMap = (BaseAddress + 0x2E1CA);
			D2CLIENT::asmCallChatBoxSend = (BaseAddress + 0x32C89);
			D2CLIENT::asmCallGameReceivePacketHandler = (BaseAddress + 0x15123);
			D2CLIENT::asmCallGameReceivePacketHandlerNew = (BaseAddress + 0x3346A); //VERIFY: was 0x9E87
			D2CLIENT::asmCallGameSendPacketHandler = (BaseAddress + 0x161760);
			D2CLIENT::asmCallGamePlayerInfoHandler = (BaseAddress + 0x883C4);
			D2CLIENT::asmCallMouseDownHandler = (BaseAddress + 0xD5820);
			D2CLIENT::asmCallRepeatMouseUpHandler = (BaseAddress + 0xD582C);
			D2CLIENT::asmCallMouseUpHandler = (BaseAddress + 0xD588C);
			D2CLIENT::asmUIClickHandler = (BaseAddress + 0xD582C);
			D2CLIENT::asmCallKeyHandler = (BaseAddress + 0xD8C2C);
			D2CLIENT::asmCallChatHandler = (BaseAddress + 0xD82F8);
			D2CLIENT::asmCallGameMessageHandler = (BaseAddress + 0x13890);
			D2CLIENT::asmJoinGame = (BaseAddress + 0xA2CD);
			D2CLIENT::asmLeaveGame = (BaseAddress + 0xA8AD8);
			D2CLIENT::asmCallAddRoomData = (BaseAddress + 0x12303);
			D2CLIENT::asmCallRemoveRoomData = (BaseAddress + 0x12373);
			D2CLIENT::asmCallIGGlobalMessageHandler = (BaseAddress + 0x2597);


			D2CLIENT::asmCallDrawScreen = (BaseAddress + 0x97DE);
			D2CLIENT::asmCallDrawPanel = (BaseAddress + 0x81FF7);
			D2CLIENT::asmScreenPrint3 = (BaseAddress + 0x81ED4);

			D2CLIENT::asmCallActChangePalette = (BaseAddress + 0x845DE);
			D2CLIENT::asmCallD2CMPSetAct = (BaseAddress + 0x845E9);
			D2CLIENT::asmCallEndGameChangePalette = (BaseAddress + 0xA330);

			D2CLIENT::asmCallD2NETGameSend0 = (BaseAddress + 0xD3F2);
			D2CLIENT::asmCallD2NETGameSend1 = (BaseAddress + 0xD910);

		}



	
	
	
		void D2CLIENT::PrintScreenMessage(wchar_t* msg, BYTE color)
		{
			__asm
			{
				xor edx, edx
				mov dl, color
				mov ecx, msg
				mov eax, D2CLIENT::fptrPrintScreenMessage		;7C600
				call eax
			}
		}

		void D2CLIENT::UnloadUIImage(CellFile * UiImage)
		{
			__asm
			{
				//this function was inlined in 1.11b!
				//mov ecx, UiImage
				//mov eax, D2CLIENT::fptrUnloadUIImage		;0x1140
				//call eax
				push UiImage
				call D2CMP::UnloadUIImage
			}
		}

		bool D2CLIENT::GetGameStatus(void)
		{
			bool retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetGameStatus		;0x9440
				call eax
				mov retval, al
			}
			return retval;
		}

		int D2CLIENT::GetGameType(void)
		{
			int retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetGameType		;1 for exp
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::QuitGame(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrQuitGame		;0xC2F0
				call eax
			}
		}

		void D2CLIENT::TransferGold(DWORD unk_4f, DWORD Direction, DWORD AmountHigh, DWORD AmountLow)
		{
			__asm
			{
				push AmountLow
				push AmountHigh
				mov edx, Direction
				mov ecx, unk_4f
				mov eax, D2CLIENT::fptrTransferGold		;0xD9E0
				call eax
			}
		}

		void D2CLIENT::DropGold(DWORD unk_50, DWORD PlayerID, DWORD Amount) //change
		{
			__asm
			{
				push Amount
				mov edx, PlayerID
				mov ecx, unk_50
				mov eax, D2CLIENT::fptrDropGold		;0xDA40
				call eax
			}
		}

		int D2CLIENT::GetMouseXOffset(void)
		{
			int retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetMouseXOffset		;0x15890
				call eax
				mov retval, eax
			}
			return retval;
		}

		int D2CLIENT::GetMouseYOffset(void)
		{
			int retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetMouseYOffset		;0x158A0
				call eax
				mov retval, eax
			}
			return retval;
		}

		UnitAny * D2CLIENT::GetSelectedUnit(void)
		{
			UnitAny * retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetSelectedUnit		;0x15A20
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::SetSelectedUnit(UnitAny * ptSelectedUnit)
		{
			__asm
			{
				mov ecx, ptSelectedUnit
				mov eax, D2CLIENT::fptrSetSelectedUnit		;0x15AE0
				call eax
			}
		}

		void D2CLIENT::ClearSelectedUnit(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrClearSelectedUnit		;0x15D40
				call eax
			}
		}

		void D2CLIENT::ChatPressHandler(D2MSG * ptMsg)
		{
			__asm
			{
				push ptMsg
				mov eax, D2CLIENT::fptrChatPressHandler		;0x32890
				call eax
			}
		}

		void D2CLIENT::ToggleChatBox(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrToggleChatBox		;0x337B0
				call eax
			}
		}

		void D2CLIENT::KeyPressHandler(D2MSG * ptMsg)
		{
			__asm
			{
				push ptMsg
				mov eax, D2CLIENT::fptrKeyPressHandler		;0x35A00
				call eax
			}
		}

		void D2CLIENT::WeaponSwitch(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrWeaponSwitch		;0x4D2B0
				call eax
			}
		}

		void D2CLIENT::usePotion(UnitPlayer *player, d2_Inventory *inv, DWORD MeOrMerc /*0 or 0x8000*/, DWORD slot)
		{
			__asm
			{
				push slot
				push MeOrMerc
				mov edx, inv
				mov ecx, player
				mov eax, D2CLIENT::fptrusePotion		;0x618A0
				call eax
			}
		}

		void D2CLIENT::PrintChatMessage(wchar_t * Message, DWORD color)
		{
			__asm
			{
				mov edx, color
				mov ecx, Message
				mov eax, D2CLIENT::fptrPrintChatMessage		;0x7C600
				call eax
			}
		}

		void D2CLIENT::PrintMessage(ChatMsg * Message)
		{
			__asm
			{
				mov ecx, Message
				mov eax, D2CLIENT::fptrPrintMessage		;0x7E120
				call eax
			}
		}

		CellFile * D2CLIENT::LoadUIImage(char * uiname)
		{
			CellFile * retval;
			__asm
			{
				mov ecx, uiname
				mov eax, D2CLIENT::fptrLoadUIImage		;0x80100
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::ManipUI(int uiNum, int uiState, DWORD _1)
		{
			__asm
			{
				push _1
				mov edx, uiState
				mov ecx, uiNum
				mov eax, D2CLIENT::fptrManipUI		;0x83260
				call eax
			}
		}

		int D2CLIENT::GetUIState(int uiNum)
		{
			int retval;
			__asm
			{
				mov ecx, uiNum
				mov eax, D2CLIENT::fptrGetUIState		;0x83230
				call eax
				mov retval, eax
			}
			return retval;
		}

		UnitAny * D2CLIENT::GetUnitFromId(DWORD unitid, DWORD unittype)
		{
			UnitAny * retval;
			__asm
			{
				mov edx, unittype
				mov ecx, unitid
				mov eax, D2CLIENT::fptrGetUnitFromId		;0x869F0
				call eax
				mov retval, eax
			}
			return retval;
		}

		bool D2CLIENT::UnitTestSelect(UnitAny * ptUnit, DWORD _1, DWORD _2, bool _3)
		{
			bool retval;
			DWORD __3 = (DWORD)_3;
			__asm
			{
				push __3
				push _2
				mov edx, _1
				mov ecx, ptUnit
				mov eax, D2CLIENT::fptrUnitTestSelect		;0x886F0
				call eax
				mov retval, al
			}
			return retval;
		}

		void D2CLIENT::ClickNpcMenuUI(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickNpcMenuUI		;0x35DC0
				call eax
			}
		}

		void D2CLIENT::ClickScreen(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickScreen		;0x46E60
				call eax
			}
		}

		void D2CLIENT::ClickTradeUIdown(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickTradeUIdown		;0x4A1C0
				call eax
			}
		}

		void D2CLIENT::ClickTradeUIup(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickTradeUIup		;0x4A850
				call eax
			}
		}

		void D2CLIENT::ClickStashUIdown(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickStashUIdown		;0x4BAD0
				call eax
			}
		}

		void D2CLIENT::ClickStashUIup(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg)
		{
			__asm
			{
				push ptrClickMsg
				mov edx, UnkAddr
				mov ecx, d2handle
				mov eax, D2CLIENT::fptrClickStashUIup		;0x4C030
				call eax
			}
		}

		void D2CLIENT::SetSkill(DWORD Fkey, DWORD unk)
		{
			__asm
			{
				mov edx, unk
				mov ecx, Fkey
				mov eax, D2CLIENT::fptrSetSkill		;0x7A130
				call eax
			}
		}

		void D2CLIENT::DrawPanel(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrDrawPanel		;0x5F480
				call eax
			}
		}

		UnitAny * D2CLIENT::GetUnit(DWORD id, DWORD ttype)
		{
			UnitAny * retval;
			__asm
			{
				mov edx, ttype
				mov ecx, id
				mov eax, D2CLIENT::fptrGetUnit		;0x869F0
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::UpdatePlayerStruct(UnitPlayer * ptPlayer)
		{
			__asm
			{
				mov ecx, ptPlayer
				mov eax, D2CLIENT::fptrUpdatePlayerStruct		;0x88390
				call eax
			}
		}

		UnitPlayer * D2CLIENT::GetPlayerUnit(void)
		{
			UnitPlayer * retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetPlayerUnit		;0x883D0
				call eax
				mov retval, eax
			}
			return retval;
		}

		Room1 * D2CLIENT::GetPlayerRoom(void)
		{
			Room1 * retval;
			__asm
			{
				mov eax, D2CLIENT::fptrGetPlayerRoom		;0x89370
				call eax
				mov retval, eax
			}
			return retval;
		}

		wchar_t * D2CLIENT::GetNameFromUnit(UnitAny *unit)
		{
			wchar_t * retval;
			__asm
			{
				mov ecx, unit
				mov eax, D2CLIENT::fptrGetNameFromUnit		;0x897F0
				call eax
				mov retval, eax
			}
			return retval;
		}

		int D2CLIENT::MouseClick(int ClickType, unsigned short MouseX, unsigned short MouseY, BYTE ClickFlag)
		{
			int retval;
			DWORD __clickflag = (DWORD)ClickFlag;
			DWORD __mousex = MouseX;
			DWORD __mousey = MouseY;
			__asm
			{
				push __clickflag
				push __mousey
				mov edx, __mousex
				mov ecx, ClickType
				mov eax, D2CLIENT::fptrMouseClick		;0xA9920
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::MouseClickTest(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrMouseClickTest		;0xA999F
				call eax
			}
		}

		void D2CLIENT::ExitGame(DWORD flags)
		{
			__asm
			{
				push flags
				mov eax, D2CLIENT::fptrExitGame		;0xC06B3
				call eax
			}
		}

		void D2CLIENT::CancelStore(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrCancelStore		;0x59FE0
				call eax
			}
		}

		void D2CLIENT::CancelStash(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrCancelStash		;0x4C650
				call eax
			}
		}

		void D2CLIENT::CancelWaypoint(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrCancelWaypoint		;0x862E0
				call eax
			}
		}

		void D2CLIENT::CancelNPCChat(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrCancelNPCChat		;0x56BC0
				call eax
			}
		}

		int D2CLIENT::RightClickInventoryItem(UnitAny * pl, d2_Inventory * i, int x, int y, int invlocation)
		{
			int retval;
			__asm
			{
				push invlocation
				push y
				push x
				mov edx, i
				mov ecx, pl
				mov eax, D2CLIENT::fptrRightClickInventoryItem		;0x48C60
				call eax
				mov retval, eax
			}
			return retval;
		}

		int D2CLIENT::LeftClickInventoryItem(UnitAny * pl, d2_Inventory * i, int x, int y, int clicktype, DWORD address, int invlocation)
		{
			int retval;
			__asm
			{
				push invlocation
				push address
				push clicktype
				push y
				push x
				mov edx, i
				mov ecx, pl
				mov eax, D2CLIENT::fptrLeftClickInventoryItem		;0x475C0
				call eax
				mov retval, eax
			}
			return retval;
		}

		int D2CLIENT::RightClickTradeItem(UnitAny * npc, UnitItem * i, int Unk/*0*/, int x, int y, int clickval, int Unk2/*1*/, int unk3/*0*/)
		{
			int retval;
			__asm
			{
				push unk3/*0*/
				push Unk2/*1*/
				push clickval
				push y
				push x
				push Unk/*0*/
				mov edx, i
				mov ecx, npc
				mov eax, D2CLIENT::fptrRightClickTradeItem		;0x5A260
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::LeftClickBelt(UnitPlayer * pl, d2_Inventory * i, int x, int y)
		{
			__asm
			{
				push y
				push x
				mov edx, i
				mov ecx, pl
				mov eax, D2CLIENT::fptrLeftClickBelt		;0x612E0
				call eax
			}
		}

		void D2CLIENT::GetItemStatsString(UnitItem * ui, wchar_t * cstats, int ilength, int Unk1_1, int Unk2_0, int Unk3_AB, int Unk4_40, int Unk5_1)
		{
			__asm
			{
				push Unk5_1
				push Unk4_40
				push Unk3_AB
				push Unk2_0
				push Unk1_1
				push ilength
				mov edx, cstats
				mov ecx, ui
				mov eax, D2CLIENT::fptrGetItemStatsString		;0x519C0
				call eax
			}
		}

		void D2CLIENT::GetItemNameString(UnitItem * ui, wchar_t * cname, int ilength)
		{
			__asm
			{
				push ilength
				mov edx, cname
				mov ecx, ui
				mov eax, D2CLIENT::fptrGetItemNameString		;0x3D360
				call eax
			}
		}

		void D2CLIENT::LLScreenPrint3()
		{
			__asm
			{
				mov eax, D2CLIENT::fptrLLScreenPrint3		;0x1000
				call eax
			}
		}

		void D2CLIENT::RevealAutomapRoom(Room1 *room1, DWORD clipflag, d2_AutomapLayer *layer)
		{
			__asm
			{
				push layer
				mov edx, clipflag
				mov ecx, room1
				mov eax, D2CLIENT::fptrRevealAutomapRoom		;0x2D180
				call eax
			}
		}

		void D2CLIENT::UseStatPoint(BYTE packetByte, WORD stat)
		{
			__asm
			{
				xor edx, edx
				xor ecx, ecx
				mov dx, stat
				mov cl, packetByte
				mov eax, D2CLIENT::fptrUseStatPoint		;0xD990
				call eax
			}
		}

		void D2CLIENT::UseSkillPoint(BYTE packetByte, WORD skill)
		{
			__asm
			{
				xor edx, edx
				xor ecx, ecx
				mov dx, skill
				mov cl, packetByte
				mov eax, D2CLIENT::fptrUseSkillPoint		;0x78529
				call eax
			}
		}

		void D2CLIENT::PartyUIButton(int itype, int gid)
		{
			__asm
			{
				mov edx, gid
				mov ecx, itype
				mov eax, D2CLIENT::fptrPartyUIButton		;0xDB20
				call eax
			}
		}

		void D2CLIENT::PrePacketOther1(DWORD itype, DWORD p1)
		{
			__asm
			{
				mov edx, p1
				mov ecx, itype
				mov eax, D2CLIENT::fptrPrePacketOther1		;0xD990
				call eax
			}
		}

		void D2CLIENT::PrePacket1(DWORD itype, DWORD p1)
		{
			__asm
			{
				mov edx, p1
				mov ecx, itype
				mov eax, D2CLIENT::fptrPrePacket1		;0xDA20
				call eax
			}
		}

		void D2CLIENT::PrePacket2(DWORD itype, DWORD p1, DWORD p2)
		{
			__asm
			{
				push p2
				mov edx, p1
				mov ecx, itype
				mov eax, D2CLIENT::fptrPrePacket2		;0xDA40
				call eax
			}
		}

		void D2CLIENT::PrePacket3(DWORD itype, DWORD p1, DWORD p2, DWORD p3)
		{
			__asm
			{
				push p3
				push p2
				mov edx, p1
				mov ecx, itype
				mov eax, D2CLIENT::fptrPrePacket3		;0xDA70
				call eax
			}
		}

		void D2CLIENT::PrePacket4(DWORD itype, DWORD p1, DWORD p2, DWORD p3, DWORD p4)
		{
			__asm
			{
				push p4
				push p3
				push p2
				mov edx, p1
				mov ecx, itype
				mov eax, D2CLIENT::fptrPrePacket4		;0xDAA0
				call eax
			}
		}

		DWORD D2CLIENT::CheckDrawUnitToAutoMap(UnitAny * unit, BYTE* col)
		{
			DWORD retval;
			__asm
			{
				mov edx, col
				mov ecx, unit
				mov eax, D2CLIENT::fptrCheckDrawUnitToAutoMap		;0x2E8F0
				call eax
				mov retval, eax
			}
			return retval;
		}

		void D2CLIENT::DrawAutoMap(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrDrawAutoMap		;0x2E510
				call eax
			}
		}

		void D2CLIENT::ChatBoxSend(void)
		{
			__asm
			{
				mov eax, D2CLIENT::fptrChatBoxSend		;0xDB50
				call eax
			}
		}

		void D2CLIENT::GameReceivePacketHandlerNew(BYTE * Packet, DWORD iLength)
		{
			__asm
			{
				mov edx, iLength
				mov ecx, Packet
				mov eax, D2CLIENT::fptrGameReceivePacketHandlerNew		;0x150B0
				call eax
			}
		}

	


}

}


