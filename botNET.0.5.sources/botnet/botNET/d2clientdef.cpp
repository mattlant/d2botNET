#include "botnet.h"
#include "d2client.h"


namespace botNET
{
	namespace Imports
	{


		UInt32 D2CLIENT::BaseAddress = 0;

		d2_AutomapLayer ** D2CLIENT::AutomapLayer = 0; //0x1119A4
		int* D2CLIENT::Area = 0; //0x115EF0
		int* D2CLIENT::Act = 0; //0x11A77C
		int* D2CLIENT::Difficulty = 0; //0x10795C
		DWORD* D2CLIENT::MsgId = 0; //0x119EF6
		DWORD* D2CLIENT::Ping = 0; //0x107774
		int* D2CLIENT::AlwaysRun = 0; //0x1079B8
		int* D2CLIENT::SlotsWithPotion = 0; //0x115EBC
		int* D2CLIENT::CurrentWeaponSlot = 0; //0x11594C
		wchar_t* D2CLIENT::LastChatMessage = 0; //0x111A58
		wchar_t* D2CLIENT::LastMessage = 0; //0x12E3C2
		DWORD* D2CLIENT::MessageTimer = 0; //0x112D08
		DWORD* D2CLIENT::ClickWpId = 0; //0x11A9A5
		d2_NpcMenu ** D2CLIENT::NpcMenu = 0; //0x113644
		d2_NpcMainMenuFunctionTable* D2CLIENT::NpcMainMenuFunctionTable = 0; //0xDBD70
		int* D2CLIENT::NpcMainMenuTableCount = 0; //0xDC4C0
		DWORD* D2CLIENT::ClickTrade = 0; //0x115BA8
		DWORD* D2CLIENT::d2MouseXa = 0; //0x121AE4
		DWORD* D2CLIENT::d2MouseYa = 0; //0x121AE8
		DWORD* D2CLIENT::d2MouseXb = 0; //0x11388C
		DWORD* D2CLIENT::d2MouseYb = 0; //0x113894
		d2_InventoryLayout* D2CLIENT::PlayerInventoryLayout = 0; //0x113710
		d2_InventoryLayout* D2CLIENT::StoreInventoryLayout = 0; //0x113898
		d2_InventoryLayout* D2CLIENT::TradeInventoryLayout = 0; //0x113838
		d2_InventoryLayout* D2CLIENT::CubeInventoryLayout = 0; //0x113880
		d2_InventoryLayout* D2CLIENT::StashInventoryLayout = 0; //0x113760
		DWORD* D2CLIENT::MouseX = 0; //0x121AE4
		DWORD* D2CLIENT::MouseY = 0; //0x121AE8
		int* D2CLIENT::CursorTableSize = 0; //0xF6C1C
		DWORD* D2CLIENT::MaxMouseX = 0; //0xD40EC
		DWORD* D2CLIENT::MaxMouseY = 0; //0xD40F0
		DWORD* D2CLIENT::F13Skill = 0; //0x119D20
		DWORD* D2CLIENT::F13SkillHand = 0; //0x119888
		bool* D2CLIENT::HasHighlight = 0; //0x10B9E8
		int* D2CLIENT::HighlightUnitType = 0; //0x10B9CC
		int* D2CLIENT::HighlightUnitId = 0; //0x10B9D0
		Room1 ** D2CLIENT::ghRoom = 0; //0x10B9F8
		DWORD* D2CLIENT::ScreenYOffset = 0; //0x10B9B8
		DWORD* D2CLIENT::ScreenXOffset = 0; //0x10B9BC
		int* D2CLIENT::ClientScreenWidth = 0; //0xFA704
		int* D2CLIENT::ClientScreenHeight = 0; //0xFA700
		UnitAny ** D2CLIENT::SelectedInventoryUnit = 0; //0x1158F0
		d2_MessageLogMessage ** D2CLIENT::LastMessageLogMessage = 0; //0x119ED8
		WORD* D2CLIENT::MessageLogCount = 0; //0x119EDC
		//D2HANDLER* D2CLIENT::FirstHandlerTable = 0; //0xD5818
		//D2HANDLER* D2CLIENT::SecondHandlerTable = 0; //0xD87F0
		//D2HANDLER* D2CLIENT::ThirdHandlerTable = 0; //0x*/
		bool* D2CLIENT::IsPaused = 0; //0x11C23C
		bool* D2CLIENT::IsAutoMapOn = 0; //0x11A754
		RosterPet ** D2CLIENT::FirstRosterPet = 0; //0x10B9A0
		Roster ** D2CLIENT::FirstRosterPlayer = 0; //0x10B994
		UnitPlayer ** D2CLIENT::PlayerUnit = 0; //0x11C200
		UnitAny ** D2CLIENT::UnitTable = 0; //0x11AA00
		DWORD* D2CLIENT::FPS = 0; //0xFA96C
		DWORD* D2CLIENT::Skip = 0; //0x107780
		int* D2CLIENT::AutoMapDiv = 0; //0xD7BC0
		int* D2CLIENT::AutoMapXSub = 0; //0x1119D8
		int* D2CLIENT::AutoMapYSub = 0; //0x1119DC
		int* D2CLIENT::AutoMapLeftBound = 0; //0x111A08
		int* D2CLIENT::AutoMapRightBound = 0; //0x111A10
		int* D2CLIENT::AutoMapTopBound = 0; //0x111A0C
		int* D2CLIENT::AutoMapBottomBound = 0; //0x111A14
		DWORD* D2CLIENT::ClickItemCheck = 0; //0x115D37
		void ** D2CLIENT::ItemPriceGameInfoUnk = 0; //0x115D13
		DWORD ** D2CLIENT::ClickEquipmentLocationBase = 0; //0xD92AC
		DWORD* D2CLIENT::InteractedNPCUniqueID = 0; //0x115CF5
		BOOL* D2CLIENT::IsInteractedWithNPC = 0; //0x115CF9
		DWORD* D2CLIENT::InteractedNPCClassID = 0; //0x115CFD
		DWORD* D2CLIENT::InteractedWPUniqueID = 0; //0x11A9B5
		bool* D2CLIENT::IsNotInteractedWithWP = 0; //0x11A9BD
		DWORD* D2CLIENT::ShopCursorMode = 0; //0x121AC8
		DWORD* D2CLIENT::CursorMode = 0; //0x121AD4
		UnitItem** D2CLIENT::IdentifyingScroll = 0; //0x121AA4


		void* D2CLIENT::fptrPrintScreenMessage = 0; //0x7C600
		void* D2CLIENT::fptrUnloadUIImage = 0; //0x1140
		void* D2CLIENT::fptrGetGameStatus = 0; //0x9440
		void* D2CLIENT::fptrGetGameType = 0; //1 for exp
		void* D2CLIENT::fptrQuitGame = 0; //0xC2F0
		void* D2CLIENT::fptrTransferGold = 0; //0xD9E0
		void* D2CLIENT::fptrDropGold = 0; //0xDA40
		void* D2CLIENT::fptrGetMouseXOffset = 0; //0x15890
		void* D2CLIENT::fptrGetMouseYOffset = 0; //0x158A0
		void* D2CLIENT::fptrGetSelectedUnit = 0; //0x15A20
		void* D2CLIENT::fptrSetSelectedUnit = 0; //0x15AE0
		void* D2CLIENT::fptrClearSelectedUnit = 0; //0x15D40
		void* D2CLIENT::fptrChatPressHandler = 0; //0x32890
		void* D2CLIENT::fptrToggleChatBox = 0; //0x337B0
		void* D2CLIENT::fptrKeyPressHandler = 0; //0x35A00
		void* D2CLIENT::fptrWeaponSwitch = 0; //0x4D2B0
		void* D2CLIENT::fptrusePotion = 0; //0x618A0
		void* D2CLIENT::fptrPrintChatMessage = 0; //0x7C600
		void* D2CLIENT::fptrPrintMessage = 0; //0x7E120
		void* D2CLIENT::fptrLoadUIImage = 0; //0x80100
		void* D2CLIENT::fptrManipUI = 0; //0x83260
		void* D2CLIENT::fptrGetUIState = 0; //0x83230
		void* D2CLIENT::fptrGetUnitFromId = 0; //0x869F0
		void* D2CLIENT::fptrUnitTestSelect = 0; //0x886F0
		void* D2CLIENT::fptrClickNpcMenuUI = 0; //0x35DC0
		void* D2CLIENT::fptrClickScreen = 0; //0x46E60
		void* D2CLIENT::fptrClickTradeUIdown = 0; //0x4A1C0
		void* D2CLIENT::fptrClickTradeUIup = 0; //0x4A850
		void* D2CLIENT::fptrClickStashUIdown = 0; //0x4BAD0
		void* D2CLIENT::fptrClickStashUIup = 0; //0x4C030
		void* D2CLIENT::fptrSetSkill = 0; //0x7A130
		void* D2CLIENT::fptrGetUnit = 0; //0x869F0
		void* D2CLIENT::fptrUpdatePlayerStruct = 0; //0x88390
		void* D2CLIENT::fptrGetPlayerUnit = 0; //0x883D0
		void* D2CLIENT::fptrGetPlayerRoom = 0; //0x89370
		void* D2CLIENT::fptrGetNameFromUnit = 0; //0x897F0
		void* D2CLIENT::fptrMouseClick = 0; //0xA9920
		void* D2CLIENT::fptrMouseClickTest = 0; //0xA999F
		void* D2CLIENT::fptrExitGame = 0; //0xC06B3
		void* D2CLIENT::fptrCancelStore = 0; //0x59FE0
		void* D2CLIENT::fptrCancelStash = 0; //0x4C650
		void* D2CLIENT::fptrCancelWaypoint = 0; //0x862E0
		void* D2CLIENT::fptrCancelNPCChat = 0; //0x56BC0
		void* D2CLIENT::fptrRightClickInventoryItem = 0; //0x48C60
		void* D2CLIENT::fptrLeftClickInventoryItem = 0; //0x475C0
		void* D2CLIENT::fptrRightClickTradeItem = 0; //0x5A260
		void* D2CLIENT::fptrLeftClickBelt = 0; //0x612E0
		void* D2CLIENT::fptrGetItemStatsString = 0; //0x519C0
		void* D2CLIENT::fptrGetItemNameString = 0; //0x3D360
		void* D2CLIENT::fptrLLScreenPrint3 = 0; //0x1000
		void* D2CLIENT::fptrRevealAutomapRoom = 0; //0x2D180
		void* D2CLIENT::fptrUseStatPoint = 0; //0xD990
		void* D2CLIENT::fptrUseSkillPoint = 0; //0x78529
		void* D2CLIENT::fptrPartyUIButton = 0; //0xDB20
		void* D2CLIENT::fptrPrePacketOther1 = 0; //0xD990
		void* D2CLIENT::fptrPrePacket1 = 0; //0xDA20
		void* D2CLIENT::fptrPrePacket2 = 0; //0xDA40
		void* D2CLIENT::fptrPrePacket3 = 0; //0xDA70
		void* D2CLIENT::fptrPrePacket4 = 0; //0xDAA0
		void* D2CLIENT::fptrCheckDrawUnitToAutoMap = 0; //0x2E8F0
		void* D2CLIENT::fptrDrawAutoMap = 0; //0x2E510
		void* D2CLIENT::fptrChatBoxSend = 0; //0xDB50
		void* D2CLIENT::fptrGameReceivePacketHandlerNew = 0; //0x150B0
		void* D2CLIENT::fptrDrawPanel = 0; //0x5F480

		DWORD D2CLIENT::asmCallDrawAutoMap = 0; //0x2E1CA
		DWORD D2CLIENT::asmCallChatBoxSend = 0; //0x32C89
		DWORD D2CLIENT::asmCallGameReceivePacketHandler = 0; //0x15123
		DWORD D2CLIENT::asmCallGameReceivePacketHandlerNew = 0; //0x9E87
		DWORD D2CLIENT::asmCallGameSendPacketHandler = 0; //0x161760
		DWORD D2CLIENT::asmCallGamePlayerInfoHandler = 0; //0x883C4
		DWORD D2CLIENT::asmCallMouseDownHandler = 0; //0xD5820
		DWORD D2CLIENT::asmCallRepeatMouseUpHandler = 0; //0xD582C
		DWORD D2CLIENT::asmCallMouseUpHandler = 0; //0xD588C
		DWORD D2CLIENT::asmUIClickHandler = 0; //0xD582C
		DWORD D2CLIENT::asmCallKeyHandler = 0; //0xD8C2C
		DWORD D2CLIENT::asmCallChatHandler = 0; //0xD82F8
		DWORD D2CLIENT::asmCallGameMessageHandler = 0; //0x13890
		DWORD D2CLIENT::asmJoinGame = 0; //0xA2CD
		DWORD D2CLIENT::asmLeaveGame = 0; //0xA8AD8
		DWORD D2CLIENT::asmCallAddRoomData = 0; //0x12303
		DWORD D2CLIENT::asmCallRemoveRoomData = 0; //0x12373
		DWORD D2CLIENT::asmCallIGGlobalMessageHandler = 0; //0x2597

		DWORD D2CLIENT::asmCallDrawScreen = 0; //0x97DE regular above all screenhooks. (i think)
		DWORD D2CLIENT::asmCallDrawPanel = 0; //0x81FF7
		DWORD D2CLIENT::asmScreenPrint3 = 0; //0x81ED4

		DWORD D2CLIENT::asmCallActChangePalette = 0; //0x845DE
		DWORD D2CLIENT::asmCallD2CMPSetAct = 0; //0x845E9
		DWORD D2CLIENT::asmCallEndGameChangePalette = 0; //0xA330

		DWORD D2CLIENT::asmCallD2NETGameSend0 = 0; //0xD3F2
		DWORD D2CLIENT::asmCallD2NETGameSend1 = 0; //0xD910

		DWORD D2CLIENT::oldCallDrawAutoMap = 0; //0x2E1CA
		DWORD D2CLIENT::oldCallChatBoxSend = 0; //0x32C89
		DWORD D2CLIENT::oldCallGameReceivePacketHandler = 0; //0x15123
		DWORD D2CLIENT::oldCallGameReceivePacketHandlerNew = 0; //0x9E87
		DWORD D2CLIENT::oldCallGameSendPacketHandler = 0; //0x161760
		DWORD D2CLIENT::oldCallGamePlayerInfoHandler = 0; //0x883C4
		DWORD D2CLIENT::oldCallMouseDownHandler = 0; //0xD5820
		DWORD D2CLIENT::oldCallRepeatMouseUpHandler = 0; //0xD582C
		DWORD D2CLIENT::oldCallMouseUpHandler = 0; //0xD588C
		DWORD D2CLIENT::oldUIClickHandler = 0; //0xD582C
		DWORD D2CLIENT::oldCallKeyHandler = 0; //0xD8C2C
		DWORD D2CLIENT::oldCallChatHandler = 0; //0xD82F8
		DWORD D2CLIENT::oldCallGameMessageHandler = 0; //0x13890
		DWORD D2CLIENT::oldJoinGame = 0; //0xA2CD
		DWORD D2CLIENT::oldLeaveGame = 0; //0xA8AD8
		DWORD D2CLIENT::oldCallAddRoomData = 0; //0x12303
		DWORD D2CLIENT::oldCallRemoveRoomData = 0; //0x12373
		DWORD D2CLIENT::oldCallIGGlobalMessageHandler = 0; //0x2597

		DWORD D2CLIENT::oldCallDrawScreen = 0; //0x97DE regular above all screenhooks. (i think)
		DWORD D2CLIENT::oldCallDrawPanel = 0; //0x81FF7
		DWORD D2CLIENT::oldScreenPrint3 = 0; //0x81ED4

		DWORD D2CLIENT::oldCallActChangePalette = 0; //0x845DE
		DWORD D2CLIENT::oldCallD2CMPSetAct = 0; //0x845E9
		DWORD D2CLIENT::oldCallEndGameChangePalette = 0; //0xA330

		DWORD D2CLIENT::oldCallD2NETGameSend0 = 0; //0xD3F2
		DWORD D2CLIENT::oldCallD2NETGameSend1 = 0; //0xD910

		BYTE D2CLIENT::oldMouseMove1[5];
		BYTE D2CLIENT::oldMouseMove2[5];
		BYTE D2CLIENT::oldMouseMove3[5];
		BYTE D2CLIENT::oldMouseMove4[5];
	}

}
