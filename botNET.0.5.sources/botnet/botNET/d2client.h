#ifndef D2CLIENT_H
#define D2CLIENT_H

#include "definitions.h"

namespace botNET 
{
	namespace Imports
	{
		__nogc struct D2CLIENT
		{
		public:

			static void Initialize();

			static UInt32					BaseAddress;

			static d2_AutomapLayer ** AutomapLayer;
			static int* Area;
			static int* Act;
			static int* Difficulty;
			static DWORD* MsgId;
			static DWORD* Ping;
			static int* AlwaysRun;
			static int* SlotsWithPotion;
			static int* CurrentWeaponSlot;
			static wchar_t* LastChatMessage;
			static wchar_t* LastMessage;
			static DWORD* MessageTimer;
			static DWORD* ClickWpId;
			static d2_NpcMenu ** NpcMenu;
			static d2_NpcMainMenuFunctionTable* NpcMainMenuFunctionTable;
			static int* NpcMainMenuTableCount;
			static DWORD* ClickTrade;
			static DWORD* d2MouseXa;
			static DWORD* d2MouseYa;
			static DWORD* d2MouseXb;
			static DWORD* d2MouseYb;
			static d2_InventoryLayout* PlayerInventoryLayout;
			static d2_InventoryLayout* StoreInventoryLayout;
			static d2_InventoryLayout* TradeInventoryLayout;
			static d2_InventoryLayout* CubeInventoryLayout;
			static d2_InventoryLayout* StashInventoryLayout;
			static DWORD* MouseX;
			static DWORD* MouseY;
			static int* CursorTableSize;
			static DWORD* MaxMouseX;
			static DWORD* MaxMouseY;
			static DWORD* F13Skill;
			static DWORD* F13SkillHand;
			static bool* HasHighlight;
			static int* HighlightUnitType;
			static int* HighlightUnitId;
			static Room1 ** ghRoom;
			static DWORD* ScreenYOffset;
			static DWORD* ScreenXOffset;
			static int* ClientScreenWidth;
			static int* ClientScreenHeight;
			static UnitAny ** SelectedInventoryUnit;
			static d2_MessageLogMessage ** LastMessageLogMessage;
			static WORD* MessageLogCount;
			//static D2HANDLER* FirstHandlerTable;
			//static D2HANDLER* SecondHandlerTable;
			//static D2HANDLER* ThirdHandlerTable;
			static bool* IsPaused;
			static bool* IsAutoMapOn;
			static RosterPet ** FirstRosterPet;
			static Roster ** FirstRosterPlayer;
			static UnitPlayer ** PlayerUnit;
			static UnitAny ** UnitTable;
			static DWORD* FPS;
			static DWORD* Skip;
			static int* AutoMapDiv;
			static int* AutoMapXSub;
			static int* AutoMapYSub;
			static int* AutoMapLeftBound;
			static int* AutoMapRightBound;
			static int* AutoMapTopBound;
			static int* AutoMapBottomBound;
			static DWORD* ClickItemCheck;
			static void ** ItemPriceGameInfoUnk;
			static DWORD ** ClickEquipmentLocationBase;
			static DWORD* InteractedNPCUniqueID;
			static BOOL* IsInteractedWithNPC;
			static DWORD* InteractedNPCClassID;
			static DWORD* InteractedWPUniqueID;
			static bool* IsNotInteractedWithWP;
			static DWORD* ShopCursorMode;
			static DWORD* CursorMode;
			static UnitItem** IdentifyingScroll;

			static void PrintScreenMessage(wchar_t* msg, BYTE color);
			static void* fptrPrintScreenMessage; //0x7C600

			static void UnloadUIImage(CellFile * UiImage);
			static void* fptrUnloadUIImage; //0x1140

			static bool GetGameStatus(void);
			static void* fptrGetGameStatus; //0x9440

			static int GetGameType(void);
			static void* fptrGetGameType; //0xC080

			static void QuitGame(void);
			static void* fptrQuitGame; //0xC2F0

			static void TransferGold(DWORD unk_4f, DWORD Direction, DWORD AmountHigh, DWORD AmountLow);
			static void* fptrTransferGold; //0xD9E0

			static void DropGold(DWORD unk_50, DWORD PlayerID, DWORD Amount);
			static void* fptrDropGold; //0xDA40

			static int GetMouseXOffset(void);
			static void* fptrGetMouseXOffset; //0x15890

			static int GetMouseYOffset(void);
			static void* fptrGetMouseYOffset; //0x158A0

			static UnitAny * GetSelectedUnit(void);
			static void* fptrGetSelectedUnit; //0x15A20

			static void SetSelectedUnit(UnitAny * ptSelectedUnit);
			static void* fptrSetSelectedUnit; //0x15AE0

			static void ClearSelectedUnit(void);
			static void* fptrClearSelectedUnit; //0x15D40

			static void ChatPressHandler(D2MSG * ptMsg);
			static void* fptrChatPressHandler; //0x32890

			static void ToggleChatBox(void);
			static void* fptrToggleChatBox; //0x337B0

			static void KeyPressHandler(D2MSG * ptMsg);
			static void* fptrKeyPressHandler; //0x35A00

			static void WeaponSwitch(void);
			static void* fptrWeaponSwitch; //0x4D2B0

			static void usePotion(UnitPlayer *player, d2_Inventory *inv, DWORD MeOrMerc /*0 or 0x8000*/, DWORD slot);
			static void* fptrusePotion; //0x618A0

			static void PrintChatMessage(wchar_t * Message, DWORD color);
			static void* fptrPrintChatMessage; //0x7C600

			static void PrintMessage(ChatMsg * Message);
			static void* fptrPrintMessage; //0x7E120

			static CellFile * LoadUIImage(char * uiname);
			static void* fptrLoadUIImage; //0x80100

			static void ManipUI(int uiNum, int uiState, DWORD _1);
			static void* fptrManipUI; //0x83260

			static int GetUIState(int uiNum);
			static void* fptrGetUIState; //0x83230

			static UnitAny * GetUnitFromId(DWORD unitid, DWORD unittype);
			static void* fptrGetUnitFromId; //0x869F0

			static bool UnitTestSelect(UnitAny * ptUnit, DWORD _1, DWORD _2, bool _3);
			static void* fptrUnitTestSelect; //0x886F0

			static void ClickNpcMenuUI(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);
			static void* fptrClickNpcMenuUI; //0x35DC0

			static void ClickScreen(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);  // arg 2 seems to be some type of GDI context
			static void* fptrClickScreen; //0x46E60

			static void ClickTradeUIdown(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);
			static void* fptrClickTradeUIdown; //0x4A1C0

			static void ClickTradeUIup(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);
			static void* fptrClickTradeUIup; //0x4A850

			static void ClickStashUIdown(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);
			static void* fptrClickStashUIdown; //0x4BAD0

			static void ClickStashUIup(DWORD d2handle, DWORD UnkAddr, DWORD ptrClickMsg);
			static void* fptrClickStashUIup; //0x4C030

			static void SetSkill(DWORD Fkey, DWORD unk);
			static void* fptrSetSkill; //0x7A130

			static UnitAny * GetUnit(DWORD id, DWORD type);
			static void* fptrGetUnit; //0x869F0

			static void UpdatePlayerStruct(UnitPlayer * ptPlayer);
			static void* fptrUpdatePlayerStruct; //0x88390

			static UnitPlayer * GetPlayerUnit(void);
			static void* fptrGetPlayerUnit; //0x883D0

			static Room1 * GetPlayerRoom(void);
			static void* fptrGetPlayerRoom; //0x89370

			static wchar_t * GetNameFromUnit(UnitAny *unit);
			static void* fptrGetNameFromUnit; //0x897F0

			static int MouseClick(int ClickType, unsigned short MouseX, unsigned short MouseY, BYTE ClickFlag);
			static void* fptrMouseClick; //0xA9920

			static void MouseClickTest(void);
			static void* fptrMouseClickTest; //0xA999F

			static void ExitGame(DWORD flags);
			static void* fptrExitGame; //0xC06B3

			static void CancelStore(void);
			static void* fptrCancelStore; //0x59FE0

			static void CancelStash(void);
			static void* fptrCancelStash; //0x4C650

			static void CancelWaypoint(void);
			static void* fptrCancelWaypoint; //0x862E0

			static void CancelNPCChat(void);
			static void* fptrCancelNPCChat; //0x56BC0

			static int RightClickInventoryItem(UnitAny * pl, d2_Inventory * i, int x, int y, int invlocation);
			static void* fptrRightClickInventoryItem; //0x48C60

			static int LeftClickInventoryItem(UnitAny * pl, d2_Inventory * i, int x, int y, int clicktype, DWORD address, int invlocation);
			static void* fptrLeftClickInventoryItem; //0x475C0

			static int RightClickTradeItem(UnitAny * npc, UnitItem * i, int Unk/*0*/, int x, int y, int clickval, int Unk2/*1*/, int unk3/*0*/);
			static void* fptrRightClickTradeItem; //0x5A260

			static void LeftClickBelt(UnitPlayer * pl, d2_Inventory * i, int x, int y);
			static void* fptrLeftClickBelt; //0x612E0

			static void GetItemStatsString(UnitItem * i, wchar_t * stats, int length, int Unk1_1, int Unk2_0, int Unk3_AB, int Unk4_40, int Unk5_1);
			static void* fptrGetItemStatsString; //0x519C0

			static void GetItemNameString(UnitItem * i, wchar_t * name, int length);
			static void* fptrGetItemNameString; //0x3D360

			static void LLScreenPrint3(void);
			static void* fptrLLScreenPrint3; //0x1000

			static void RevealAutomapRoom(Room1 *room1, DWORD clipflag, d2_AutomapLayer *layer);
			static void* fptrRevealAutomapRoom; //0x2D180

			static void UseStatPoint(BYTE packetByte, WORD stat);
			static void* fptrUseStatPoint; //0xD990

			static void UseSkillPoint(BYTE packetByte, WORD skill);
			static void* fptrUseSkillPoint; //0x78529

			static void PartyUIButton(int type, int gid);
			static void* fptrPartyUIButton; //0xDB20

			static void PrePacketOther1(DWORD type, DWORD p1);
			static void* fptrPrePacketOther1; //0xD990

			static void PrePacket1(DWORD type, DWORD p1);
			static void* fptrPrePacket1; //0xDA20

			static void PrePacket2(DWORD type, DWORD p1, DWORD p2);
			static void* fptrPrePacket2; //0xDA40

			static void PrePacket3(DWORD type, DWORD p1, DWORD p2, DWORD p3);
			static void* fptrPrePacket3; //0xDA70

			static void PrePacket4(DWORD type, DWORD p1, DWORD p2, DWORD p3, DWORD p4);
			static void* fptrPrePacket4; //0xDAA0

			static DWORD CheckDrawUnitToAutoMap(UnitAny * unit, BYTE* col);
			static void* fptrCheckDrawUnitToAutoMap; //0x2E8F0

			static void DrawAutoMap(void);
			static void* fptrDrawAutoMap; //0x2E510

			static void ChatBoxSend(void);
			static void* fptrChatBoxSend; //0xDB50

			static void GameReceivePacketHandlerNew(BYTE * Packet, DWORD Length);
			static void* fptrGameReceivePacketHandlerNew; //0x150B0

			static void DrawPanel(void);
			static void* fptrDrawPanel; //0x5F480

			static DWORD asmCallDrawAutoMap;
			static DWORD asmCallChatBoxSend;
			static DWORD asmCallGameReceivePacketHandler;
			static DWORD asmCallGameReceivePacketHandlerNew;
			static DWORD asmCallGameSendPacketHandler;
			static DWORD asmScreenPrint3;
			static DWORD asmCallGamePlayerInfoHandler;
			static DWORD asmCallMouseDownHandler;
			static DWORD asmCallRepeatMouseUpHandler;
			static DWORD asmCallMouseUpHandler;
			static DWORD asmUIClickHandler;
			static DWORD asmCallKeyHandler;
			static DWORD asmCallChatHandler;
			static DWORD asmCallGameMessageHandler;
			static DWORD asmJoinGame;
			static DWORD asmLeaveGame;
			static DWORD asmCallAddRoomData;
			static DWORD asmCallRemoveRoomData;
			static DWORD asmCallIGGlobalMessageHandler;
			static DWORD asmCallDrawScreen; //0x97DE regular above all screenhooks. (i think)
			static DWORD asmCallDrawPanel;

			static DWORD asmCallActChangePalette;
			static DWORD asmCallD2CMPSetAct;
			static DWORD asmCallEndGameChangePalette;

			static DWORD asmCallD2NETGameSend0;
			static DWORD asmCallD2NETGameSend1;

			static DWORD oldCallDrawAutoMap;
			static DWORD oldCallChatBoxSend;
			static DWORD oldCallGameReceivePacketHandler;
			static DWORD oldCallGameReceivePacketHandlerNew;
			static DWORD oldCallGameSendPacketHandler;
			static DWORD oldScreenPrint3;
			static DWORD oldCallGamePlayerInfoHandler;
			static DWORD oldCallMouseDownHandler;
			static DWORD oldCallRepeatMouseUpHandler;
			static DWORD oldCallMouseUpHandler;
			static DWORD oldUIClickHandler;
			static DWORD oldCallKeyHandler;
			static DWORD oldCallChatHandler;
			static DWORD oldCallGameMessageHandler;
			static DWORD oldJoinGame;
			static DWORD oldLeaveGame;
			static DWORD oldCallAddRoomData;
			static DWORD oldCallRemoveRoomData;
			static DWORD oldCallIGGlobalMessageHandler;
			static DWORD oldCallDrawScreen; //0x97DE regular above all screenhooks. (i think)
			static DWORD oldCallDrawPanel;

			static DWORD oldCallActChangePalette;
			static DWORD oldCallD2CMPSetAct;
			static DWORD oldCallEndGameChangePalette;

			static DWORD oldCallD2NETGameSend0;
			static DWORD oldCallD2NETGameSend1;

			static BYTE	oldMouseMove1[5];
			static BYTE	oldMouseMove2[5];
			static BYTE	oldMouseMove3[5];
			static BYTE	oldMouseMove4[5];
		};
		
	}
}

using namespace botNET::Imports;

#endif

