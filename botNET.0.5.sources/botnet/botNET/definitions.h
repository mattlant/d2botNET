#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <windef.h>

#define D2NET_MAX_MSG_SIZE 512
#define MAX_MSG_SIZE 516

enum { UNIT_PLAYER = 0, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_ROOMTILE };

enum eUIModes { UI_ON = 0, UI_OFF = 1, UI_TOGGLE = 2 };

struct UnitAny;
struct UnitItem;
struct UnitMonster;
struct Act;
struct Room1;
struct RoomOther;
struct Drlg;
struct d2_PresetUnit;
struct DrlgColl;
struct DrlgDS1Pre;
struct PresetType2info;
struct d2_Inventory;
struct D2TextInfo;

struct Res {
	DWORD left;
	DWORD top;
	DWORD right;
	DWORD bottom;
};

struct AMapCol
{
	DWORD * col;
};

struct d2Point {
	short X;
	short Y;
};

struct D2MSG {					// 0x20 bytes long
	HWND hwnd;				// 0x00
	DWORD message;				// 0x04
	WPARAM wParam;				// 0x08
	union {
		LPARAM lParam;
		d2Point pt;
	};						// 0x0C
	DWORD _1;					// 0x10
	DWORD hwnd2;				// 0x14
	DWORD _2;				// 0x18 maybe UnitType
	DWORD _3;				// 0x1C
};

/*struct D2HANDLER {
	DWORD _1;					// 0x00
	DWORD Message;				// 0x04
	DWORD Handler;				// 0x08
};*/
// Third and final piece to the "Handler Table" experiment.  Didn't quite work
// This struct was one of the reasons.  Mainly, I could decide what the _1 was
// and if it should go at the beginning of the struct, or at the end.

struct BnetData
{
	DWORD Id;					//0x00
	DWORD Id2;					//0x04
	DWORD Unk0;					//0x08
	DWORD Unk1;					//0x0C
	DWORD Unk2;					//0x10
	DWORD Id3;					//0x14
	WORD Unk3;					//0x18
	char GameName[22];			//0x1A
	char GameIp[16];			//0x30
	DWORD Unk4[16];				//0x40
	DWORD Id4;					//0x80
	DWORD Unk6;					//0x84
	char AccountName[48];		//0x88
	char PlayerName[24];		//0xB8
	char RealmName[8];			//0xD0
	BYTE Unk7[273];				//0xD8
	BYTE CharType;				//0x1E9 00 - 06
	BYTE CharFlags;				//0x1EA LoD, Ladder, Hc Flags + 4 Unk
	BYTE MaxDifficulty;			//0x1EB
	BYTE Unk8[31];				//0x1EC
 	BYTE Difficulty;			//0x20B Works only when creating, not joining game
	DWORD *pUnk9;				//0x20C
	DWORD Unk10[3];				//0x210
	DWORD Unk11;				//0x21C
	DWORD Unk12;				//0x220
	WORD Unk13;					//0x224
	BYTE Unk14;					//0x226
	char RealmName2[24];		//0x227
	char GamePass[24];			//0x23F
	char GameDesc[256];			//0x257
	WORD Unk15;					//0x348
	BYTE Unk16;					//0x34A
	char CurChannel[32];		//0x34B
};

enum eMessageTypes { CHAT_NORMAL = 1, CHAT_WHISPERFROM, CHAT_3, CHAT_NONAME, CHAT_OVERHEAD, CHAT_WHISPERTO, CHAT_SCROLL };

struct ChatMsg {
   BYTE Identifier;        // 0x00  // should always be 0x26
   BYTE MessageType;       // 0x01  // 01 is standard chat message

                                    // 02 prints in the format "%s whispers: %s" where the first var is Name, and the
                                    // second is Message.

                                    // 04 bypasses the name checks, etc, and prints the message with color specified in
                                    // Color.

                                    // 05 creates an overhead struct and assigns it to the unit with id (UnitId)

                                    // 06 prints the "You whispered to %s:  %s, with the first var being Name, and the second
                                    // being Message.

                                    // 07 prints Message on a recipe scroll background.  Recipe scroll pane opens but lacks
                                    // buttons.
   BYTE Unk1;              // 0x02
   BYTE Style;             // 0x03  // 00 and 01 seem to print without sender, but 00 does some sort of checking, first
                                    // anything else prints as usual.
   DWORD UnitId;           // 0x04
   BYTE Color;             // 0x08
   BYTE Unk2;              // 0x09
   char Name[0x10];        // 0x0A
   char Message[0x100];    // 0x1A
};

struct Msg {
	BYTE Unk0;					//+00
   BYTE _1[3];					//+01
	DWORD Unk1;					//+04
	DWORD Unk2;					//+08
	char Message[0x100];		//+0A //text msg 
};

struct d2_MessageLogMessage {
	wchar_t * Message;					//+00
	DWORD _1[5];
	WORD unk1;
	BYTE MessageType;
};

struct d2_Buffer
{
};

struct Quest
{
	d2_Buffer *ptBuffer;			// 0x00
	DWORD Unk0;				// 0x04 // 60h * 2^3, 768
};

struct Waypoint
{
	BYTE flags;				// 0x00
};

struct PlrMsg
{
};

struct d2_InventoryLayout
{
	BYTE SlotWidth;
	BYTE SlotHeight;
	BYTE unk1;
	BYTE unk2;
	DWORD Left;
	DWORD Right;
	DWORD Top;
	DWORD Bottom;
	BYTE SlotPixelWidth;
	BYTE SlotPixelHeight;
};

enum ePieceTokens {HD = 0, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8}; 

struct ObjectBinData {
   char Name[0x40];				// 0x00
   wchar_t wName[0x40];			// 0x40
   char Token[0x3];				// 0xC0
   BYTE SpawnMax;				// 0xC3
   BYTE Selectable[8];			// 0xC4
   DWORD TrapProb;				// 0xCC
   DWORD SizeX;					// 0xD0
   DWORD SizeY;					// 0xD4
   BYTE _1;						// 0xD8
   DWORD FrameCnt[8];			// 0xD9
   WORD FrameDelta[8];			// 0xF9
   BYTE CycleAnim[8];			// 0x109
   BYTE Lit[7];					// 0x111
   BYTE BlocksLight[8];			// 0x118
   BYTE Collision[8];			// 0x120
   BYTE IsAttackable;			// 0x128
   BYTE Start[8];				// 0x129
   BYTE OrderFlag[8];			// 0x131
   BYTE EnvEffect;				// 0x139
   BYTE IsDoor;					// 0x13A
   BYTE BlocksVis;				// 0x13B
   BYTE Orientation;			// 0x13C
   BYTE Trans;					// 0x13D
   BYTE PreOperate;				// 0x13E
   BYTE Mode[8];				// 0x13F
   short XOffset;				// 0x147
   short YOffset;				// 0x149
   bool Draw;					// 0x14B
   BYTE PieceTokens[0x10];		// 0x14F
   WORD _2;						// 0x15F
   BYTE TotalPieces;			// 0x161
   BYTE XSpace;					// 0x162
   BYTE YSpace;					// 0x163
   BYTE Red;					// 0x164
   BYTE Green;					// 0x165
   BYTE Blue;					// 0x166
   BYTE SubClass;				// 0x167
   long NameOffset;				// 0x168
   BYTE _3;						// 0x16C
   BYTE MonsterOK;				// 0x16D
   BYTE OperateRange;			// 0x16E
   BYTE ShrineFunction;			// 0x16F
   BYTE Act;					// 0x170 //this is a bitmask
   WORD _4;						// 0x171
   BYTE Restore;				// 0x173
   BYTE RestoreVirgins;			// 0x174
   BYTE _5[3];					// 0x175
   long Parm[8];				// 0x178
   /*BYTE Lockable;				// 0x198
   BYTE Gore;					// 0x199
   BYTE Sync;					// 0x19A
   BYTE Beta;					// 0x19B*/ // these don't seem to match as being here, for some reason.
   BYTE nTgtFX;					// 0x198
   BYTE nTgtFY;					// 0x199
   BYTE nTgtBX;					// 0x19A
   BYTE nTgtBY;					// 0x19B
   WORD Damage;					// 0x19C // temp
   WORD CollisionSubst;			// 0x19E // temp
   DWORD Left;					// 0x1A0
   DWORD Top;					// 0x1A4
   DWORD Width;					// 0x1A8
   DWORD Height;				// 0x1AC
   BYTE ClientFn;				// 0x1B0
   BYTE InitFn;					// 0x1B1
   BYTE PopulateFn;				// 0x1B2
   BYTE OperateFn;				// 0x1B3				
   // Leaving the rest undefined for now, until I get some more bin dumps.
};

struct MonsterBinData {
};

struct ItemBinData {
	char flpName[0x20];			//0x00
	char invName[0x20];			//0x20
	char Name2[0x20];
	char Name3[0x20];
	char Codes[0x18];
	BYTE none2[0x77];
	BYTE SizeX;			
	BYTE SizeY;
	BYTE none3[0xD];
	BYTE Type;
};

struct GlobalData {
};


struct PlayerData : GlobalData {
	char PlayerName[0x10];			// 0x000
 	Quest *ptQuestNormal;			// 0x010
 	Quest *ptQuestNightmare;			// 0x014
 	Quest *ptQuestHell;				// 0x018
 	Waypoint *ptWaypointNormal;		// 0x01C
	Waypoint *ptWaypointNightmare;	// 0x020
 	Waypoint *ptWaypointHell;		// 0x024
 	BYTE * Unk0;					// 0x028
	DWORD Unk1;						// 0x02C
 	DWORD Unk2;						// 0x030
 	DWORD *ptAreaUnit;				// 0x034
 	DWORD Unk3[25];					// 0x038
 	PlrMsg *ptPlrMsg;				// 0x09C
	DWORD _1[45];					// 0x0A0
	DWORD MoveMode;					// 0x154 Set to 0x13 if moving to an entity, else 0?
	DWORD TargetType;				// 0x158
	DWORD TargetId;					// 0x15C
};

struct ItemData : GlobalData {
	BYTE Quality1;						// 0x00
	BYTE _unkb3[3];						// 0x00
	DWORD _Unk1;						// 0x04
	DWORD _Unk2;						// 0x08
	DWORD ItemFlags;					// 0x0C  1 == owned by player, 0xFFFFFFFF == not owned
	DWORD _1[0x2];						// 0x10
	DWORD dwFlags;						// 0x18
	DWORD _13[0x3];						// 0x1C
	DWORD Quality2;						// 0x28
	DWORD _14[0x3];						// 0x2C
	WORD Prefix;						// 0x38
	WORD _1a;							// 0x3A
	WORD _1ab;							// 0x3C
	WORD Suffix;						// 0x3E
	DWORD _1ac;							// 0x40
	BYTE EquippedLocation;				// 0X44 (equipped location)
	BYTE Location2;				        // 0X45 (Where?  0 = inventory, 1 = store, 3 = cube, 4 = stash, FF = belt, CC = ground)
	WORD w1;							// 0X46
	DWORD _1b[0x5];						// 0x48
	d2_Inventory * ptOwnerInv;				// 0x5C
	DWORD _2;							// 0x60
	UnitItem * ptNextInvenItem;			// 0x64 
	BYTE Location;						// 0x68 (Where?  0 = Ground, 1 = Equiped, 2 = belt, 3 = inventory, 4 = store(not true), 6 = cube, 7 = stash) if store this holds page number
	BYTE NodePage;					    // 0x69
	WORD Pad1;					        // 0x6A
	DWORD unk3;							// 0x6C
	DWORD unk4;							// 0x70
	DWORD unk5;							// 0x74
	DWORD unk6;							// 0x78
	DWORD unk7;							// 0x7C
	DWORD unk8;							// 0x80
	UnitAny * ptOwner;					// 0x84
	// 0xC4 UnitAny * ptItem
};

struct MonsterData : GlobalData {
   MonsterBinData * ptBinData;				// 0x00
   DWORD _2[0x4];							// 0x04
   WORD monsterTypePre;							// 0x04
   WORD monsterType;							// 0x04
   DWORD unk_3;							// 0x04
   BYTE Enchants[0x10];						// 0x1c
   WORD SuperUniqueNumber;					// 0x26
   DWORD Unk1;								// 0x28
   wchar_t * MonsterName;					// 0x2C
   DWORD _4[0x12];							// 0x30
   BYTE * _5;								// 0x78
   BYTE * _6;								// 0x7C
   DWORD _7[0x9];							// 0x80
   BYTE * _8;								// 0xA4
   DWORD _9[0x7];							// 0xA8
   UnitMonster * ptMonster;					// 0xC4
   BYTE * _10;								// 0xC8
   DWORD _11[0x3];							// 0xCC
   BYTE * _12;								// 0xD8
   DWORD _13[0x5];							// 0xDC

   //DWORD parentID // 0x20C //for summons FFFFFFFF when no parent weird
   //DWORD parentID // 0x03C //for merc
	//ptUnitParent //0x244
};

struct TileData : GlobalData {
};

struct ObjectData : GlobalData {	//0x80 bytes in length
	ObjectBinData * ptBinData;		// 0x00
	BYTE Destination;			// 0x04
	BYTE Flags;				// 0x05
	BYTE _1;				// 0x06
	BYTE _1b;				// 0x07
	DWORD _3;				// 0x08
	DWORD _4;				// 0x0C
	DWORD _5;				// 0x10
	DWORD _6;				// 0x14
	DWORD _7;				// 0x18
	DWORD _8;				// 0x1C
	DWORD _9;				// 0x20
	DWORD _10;				// 0x24
	char parent[16];		// 0x28
	// 0x68 struct which holds parent's ID +0x4
};


struct d2_Stats {
	WORD StatIndex;
	WORD StatID;
	DWORD StatValue;
};

struct StatsList {
	DWORD _1[0x9];			// 0x00
	d2_Stats * ptStats1;	// 0x24
	WORD StatCount1_1;		// 0x28
	WORD StatCount1_2;   	// 0x2A
	DWORD _2[2];			// 0x2C
	BYTE * _3;				// 0x34
	DWORD unk4a;			// 0x38
	StatsList * ptNext;		// 0x3C
	DWORD unk4;				// 0x40
	UnitAny * ptUnitOwner;	// 0x44
	d2_Stats * ptStats2;	// 0x48
	WORD StatCount2_1;		// 0x4C
	WORD StatCount2_2;   	// 0x4E
};

struct DrlgLevel {
   Drlg * pDrlg;					// 0x00
   int LevelNo;						// 0x04
   DWORD unk01;						//0x08
   DWORD unk02;						//0x0c
   DWORD unk03;						//0x10
   DWORD unk04;						//0x14
   DWORD unk05;						//0x18
   DWORD unk06;						//0x1c
   DWORD AreaX;						//20
   DWORD AreaY;						//24
   DWORD unk12;						//0x28
   DWORD unk13;						//0x2C
   RoomOther *pRoomOtherFirst;		//+30
   DWORD _3;						// 0x34
   BYTE * ptMazeDef;				// 0x38
   DrlgDS1Pre *pRoom2FirstDS1Pre;	// 0x3C
   DWORD _5[0x28];					// 0x40
   BYTE * ptLogicalRoomInfo;		// 0xE0
   DWORD _6[0x47];					// 0xE4
   DWORD _7[11];					//+200
   DrlgLevel *pNext;				//0x22c
   DWORD _8[3];						//0x230
   BYTE * pnJungleDefs;			    // 0x214
   // Leaving the rest undefined for now.
};

struct Drlg {
	DrlgLevel * pFirstLevel;       	// 0x00
	DWORD _1[2];					// 0x04
	Act * pAct;						// 0x0C
	int ActNum;						// 0x10
	DWORD _2[248];					//0x14
	DWORD nStaffTombLvl;			//+3f4
	DWORD nBossTombLvl;				//+3f8
	// Leaving the rest undefined for now.		
};

struct d2_PresetUnit {
   DWORD nUnitType; //+00
   DWORD nTxtFileNo; //+04
   DWORD _1[1];
   DWORD xPos; //+0c position in relation to its room
   DWORD yPos; //+10 position in relation to its room
   DWORD _2[2];
   d2_PresetUnit *pNext; //+1c
};

struct RoomTile {
	RoomOther *ptRoomOther;
	DWORD * nNum;
	DWORD _1[3];
	RoomTile *pNext;
};


struct RoomOther {
	DrlgLevel *ptDrlgLevel;       // 0x00
	DWORD xPos;                   // 0x04
	DWORD yPos;                   // 0x08
	DWORD xSize;				// 0x0C
	DWORD ySize;				// 0x10
	BYTE * _2;                    // 0x14
	DWORD _3[0x1];                // 0x18
	DWORD nPresetType;				//+1c   //1 for room1 type 2 for regular room
	PresetType2info * pPresetType2info; //+20
	DWORD _5;                     // 0x24
	BYTE * _6[0x10];              // 0x28
	DWORD _7[0x10];               // 0x68
	BYTE * _8;                    // 0xA8
	DWORD _9[0x3];                // 0xAC
	RoomOther * ptNext;           // 0xB8 //Only appears when DrlgRoom1 appears
	RoomOther * ptPrev;           // 0xBC //these 2 are sometimes rooms, sometimes not a room. Only appears when DrlgRoom1 appears
	RoomOther ** ptList;          // 0xC0 //rooms that are near you  //This all makes more sense now, when they are  close, the above is a linked list
	int nRoomList;                // 0xC4 //the number of rooms near you
	DWORD _10;                    // 0xC8 RoomTile *pRoomTiles; //+c8 Only appears when DrlgRoom1 appears
	d2_PresetUnit *pPresetUnits;	// +cc Only appears when DrlgRoom1 appears //EXTREMELY IMPORTANT
	DWORD _12[0x4];               // 0xD0
	BYTE * _13;                   // 0xE0
	Room1 *pRoom;				// 0xE4 //Pointer to the room1 associated with this room2. Collision data resides in the room1 structure
	RoomOther *pNext;             // 0xE8
};

struct PresetType2info {
	DWORD roomNum;   
	DWORD _5[1];   
	DrlgDS1Pre *pDrlgDS1Pre;
};

struct DrlgDS1Pre {
	DWORD ds1roomNum;
	DWORD ds1used;
	//ds1fileinfo *pds1fileinfo;
	DWORD tmp1;
	//placed here because the actual ds1 file is not important
	DrlgDS1Pre *pNext;
	DWORD posX;
	DWORD posY;
	DWORD sizex;
	DWORD sizey;
	DWORD _1[13];
	DrlgDS1Pre *pPrevious;
};

struct Act {
	int ActNum;			                   // 0x00
	Room1 * ptFirstRoom;		                   // 0x04
	Drlg * ptMisc;			                   // 0x08
	DWORD _1[2];			                   // 0x0C
	BYTE * _2;			                   // 0x14
	//__fastcall int(*pfnRoomCallBack)(DWORD, DWORD);    // 0x18 act callback.
	DWORD pfnActCallBack;                              // 0x18
	DWORD _4[4];                                       // 0x1C
};

struct Coords {
   DWORD BeginXpos;              // 0x00
   DWORD BeginYpos;              // 0x04
   DWORD Xsize;                  // 0x08
   DWORD Ysize;                  // 0x0C
   DWORD _1[2];                  // 0x10
   DWORD _2[2];                  // 0x18
};

struct Room1 : Coords {
	BYTE * _3;                    // 0x20
	Room1 ** ptRoomList;           // 0x24
	int NumRooms;                 // 0x28
	UnitAny * ptFirstUnit;        // 0x2C
	UnitAny * ptOtherUnit;        // 0x30 ?
	DrlgColl *pColl;			// +34 --> discovered by woof
	RoomOther * ptRoomOther;      // 0x38
	DWORD Seed;                   // 0x3C
	DWORD _6[0x3];                // 0x40
	BYTE * _7;                    // 0x4C
	DWORD _8[3];                  // 0x50
	int nPlayerUnits;             // 0x5C
	DWORD _9[6];                  // 0x60
	Act * ptAct;                  // 0x78
	Room1 * ptNext;                // 0x7C
};

struct DrlgColl {
	DWORD nPosGameX;			// 0x00
	DWORD nPosGameY;			// 0x04
	DWORD nSizeGameX;			// 0x08
	DWORD nSizeGameY;			// 0x0C
	DWORD nPosRoomX;			// 0x10
	DWORD nPosRoomY;			// 0x14
	DWORD nSizeRoomX;			// 0x18
	DWORD nSizeRoomY;			// 0x1C
	WORD * pMapStart;			// 0x20
	WORD * pMapEnd;			// 0x24
	/* 0028 end of struct Collision 40 bytes */
};

struct AutomapCell {
	DWORD fSaved; //+00
	WORD nCellNo; //+04
	WORD xPixel; //+06
	WORD yPixel; //+08
	WORD _1[1];
	AutomapCell *pLess; //+0c
	AutomapCell *pMore; //+10
};

struct d2_AutomapLayer {
	DWORD _1[2];
	AutomapCell *pFloors; //+08
	AutomapCell *pWalls; //+0c
	AutomapCell *pObjects; //+10
	AutomapCell *pExtras; //+14
};

struct PathPoint 
{
	WORD X;
	WORD Y;
};

struct d2_Path					// 0x1E0 bytes, I think
{
	WORD PrecisionX;			// 0x000
	WORD XPos;			// 0x000
	WORD PrecisionY;			// 0x000
	WORD YPos;			// 0x000
	//DWORD PrecisionX;			// 0x000
	//DWORD PrecisionY;			// 0x004
	DWORD targetX;				// 0x008
	DWORD targetY;				// 0x00C
	PathPoint sP;				// 0x010
	PathPoint sP2;				// 0x014
	PathPoint sP3;				// 0x018
	Room1 * ptRoom; 			// 0x01C
	Room1 * ptRoom2;			// 0x020
	DWORD _1;					// 0x024
	int nPathPoints;			// 0x028
	DWORD _01;				// 0x02C
	UnitAny * ptUnit;		 	// 0x030
	DWORD flags;				// 0x034
	DWORD _2;					// 0x038
	DWORD PathType;			// 0x03C
	DWORD PrevPathType;			// 0x040
	DWORD UnitSize;			// 0x044
	DWORD CollisionPattern;		// 0x048
	DWORD CollisionType;		// 0x04C
	DWORD _31;				// 0x050
	WORD _32;					// 0x054
	WORD _33;					// 0x056
	UnitAny * ptTarget;			// 0x058
	int TargetType;         		// 0x05C
	DWORD TargetId;         		// 0x060 // not always target id. . .only if a target is specified
	BYTE Direction;			// 0x064
	BYTE NewDirection;			// 0x065
	BYTE DiffDirection;			// 0x066
	BYTE _4;					// 0x067
	BYTE _5[20];				// 0x068 // vector stuff, maybe?, with some collision stuff, too?
	DWORD Velocity;			// 0x07C // Velocity of the unit 
	DWORD _6;					// 0x080 // unknown
	DWORD Velocity2;			// 0x084 // seems to be a repeat of 0x07C
	DWORD _8[2];				// 0x088 // Unknown what these are.
	BYTE bDist;				// 0x090
	BYTE bDistMax;				// 0x091
	BYTE _9;					// 0x092
	BYTE _10;					// 0x093
	int nDist;				// 0x094
	DWORD PathOffset;			// 0x098
	PathPoint PathPoints[7];		// 0x09C // Pathing points.
	DWORD _11[70];				// 0x0BC // All these have been nulls, so far
	bool _12;					// 0x1D4 // I'm assuming this is bool, because its always either 1 or 0
	PathPoint _13;				// 0x1D8 // Values always seem to be slightly off from the ones above.
	// As far as I can tell, this is the end of the struct, but I'll pad it to fill it to an even val, like
	// most structs are.
	DWORD Pad;				// 0x1DC
};

struct ObjPath
{
	Room1 * ptRoom;				// 0x00
	DWORD TargetX;				// 0x04
	DWORD TargetY;				// 0x08
	DWORD Xpos;				// 0x0C
	DWORD Ypos;				// 0x10
	DWORD _2[5];				// 0x14
	BYTE * ptUnk;				// 0x28
	DWORD _3[5];				// 0x2C
};



struct d2_Inventory {
	DWORD Signature;  			// 0x00  always 0x01020304
	BYTE * ptGame1C;              		// 0x04 //will be 0 for client
	UnitAny * ptOwner;			// 0x08
	UnitItem * pFirstItem;			// 0x0C
	UnitItem * pLastItem;			// 0x10
	BYTE * _1;				// 0x14
	DWORD _2;				// 0x18
	DWORD LeftItemUid;			// 0x1C
	UnitItem * CursorItem;			// 0x20
	DWORD OwnerUid;				// 0x24
	int NumItems;				// 0x28
	DWORD _3[0x2];				// 0x2C
	BYTE * _4;				// 0x34
	DWORD _5;					// 0x38
};

struct GfxInfo {
	DWORD Unks[0xF];
};

struct SkillInfo {
	WORD Id;				// 0x00
	BYTE bUnks[0x32];		// 0x02
	DWORD dwUnk;			// 0x34
};

struct Skill {				// 0x40 bytes long
	SkillInfo * pSkillInfo;	// 0x00
	Skill * pNextSkill;		// 0x04
	DWORD dwUnk1;			// 0x08
	DWORD dwUnk2[0x7];		// 0x0C
	DWORD SkillLevel;		// 0x28
	DWORD dwUnk3[2];		// 0x2C
	DWORD Flags;			// 0x34
	DWORD dwUnk5[2];		// 0x38
};

struct d2_SpellCast {				// 0x40 bytes long
	DWORD Unk_E5;			// 0x00
	UnitAny * ptPlayer;	// 0x04
	UnitAny * ptTarget;			// 0x08
	DWORD TargetX;		// 0x0C
	DWORD TargetY;		// 0x28
	DWORD Unk_3;		// 0x28
	DWORD Unk_4;		// 0x28
};

struct d2_Info
{
	BYTE * ptGame_1C;              // 0x00
	Skill * ptFirstSkill;          // 0x04
	Skill * ptlSkill;             // 0x08
	Skill * ptrSkill;             // 0x0C
};

struct d2_Light {
   DWORD _1[0x3];                // 0x00
   int nType;                    // 0x0C
   DWORD _2[0x7];                // 0x10
   DWORD fStaticValid;           // 0x2C
   int * pnStaticMap;            // 0x30

};

struct d2_Game
{
};

struct d2_Packet {
	long nTotal;				// 0x00
	long nUsed;				// 0x04
};

struct Roster {
	char Name[0x10];              // 0x00
	DWORD PlayerId;               // 0x10
	DWORD _1;                     // 0x14
	DWORD _2;					// 0x18
	DWORD ClassId;                // 0x1C
	WORD CharLevel;               // 0x20
	WORD PartyID;                      // 0x22
	DWORD AreaId;                // 0x24
	DWORD Xpos;                   // 0x28
	DWORD Ypos;                   // 0x2C
	DWORD eButton;                // 0x30
	BYTE * _5;                    // 0x34
	DWORD _6[0xB];                // 0x38
	WORD _7;                      // 0x64
	char Name2[0x10];             // 0x66
	WORD _8;                      // 0x76
	DWORD _9[0x2];                // 0x78
	Roster * ptNext;              // 0x80
};

// added needed DWORDS (spread)
struct RosterPet {
	DWORD ClassId;				//0x00
	DWORD PetType;				//0x04
	DWORD Id;					//0x08
	DWORD OwnerId;				//0x0C	Owners PlayerUnitId
	DWORD	_2;					//0x10
	DWORD	_3;					//0x14
	DWORD	_4;					//0x18
	DWORD	HP;					//0x1C  Out of 64
	DWORD	_6;					//0x20
	DWORD	_7;					//0x24
	DWORD	_8;					//0x28
	DWORD	_9;					//0x2C
	RosterPet *PetNext;			//0x30
};

//  Unit_All struct
struct UnitAny
{
	DWORD dwType;					// 0x00
	DWORD dwClassId;				// 0x04
	DWORD dwUnk1;					// 0x08
	DWORD dwId;					// 0x0C
	DWORD dwMode;					// 0x10
	union
	{
		PlayerData *ptPlayerData;
		ItemData *ptItemData;
		MonsterData *ptMonsterData;
		TileData *ptTileData;
		ObjectData * ptObjectData;
	};							// 0x14
	DWORD dwAct;               		// 0x18
	Act * ptAct;					// 0x1C
	DWORD dwSeed[2];				// 0x20
	DWORD dwUnk2;					// 0x28
	union 
	{
		d2_Path * hPath;
		ObjPath *hOPath;
	};								// 0x2C
	void * ptUnk1;					// 0x30
	DWORD dwUnk3[4];				// 0x30
	DWORD dwGfxFrame;				// 0x44
	DWORD FrameRemain;				// 0x48
	WORD FrameRate;           		// 0x4C
	WORD _1;                           // 0x4E
	BYTE * ptGfxUnk;				// 0x50
	GfxInfo * ptGfxInfo;			// 0x54
	DWORD dwUnk5;					// 0x58
	StatsList * ptStatsList;			// 0x5C
	d2_Inventory * ptInventory;			// 0x60
	d2_Light * ptLight;	       		// 0x64
	DWORD dwUnk6;					// 0x68
	bool bBusy;					// 0x6C
	DWORD dwUnk7[4];				// 0x70
	d2_Game *ptGame;					// 0x80
	DWORD dwUnk8[2];				// 0x84
	WORD wX;						// 0x8C
	WORD wY;						// 0x8E
	DWORD dwUnk9;				// 0x90
	DWORD MissleParentType;				// 0x94
	DWORD MissleParentID;				// 0x98
	DWORD dwUnk9b[2];				// 0x9C
	Msg * ptMsg;					// 0xA4
	d2_Info * ptInfo;					// 0xA8
	DWORD dwUnk10[6];				// 0xAC
	DWORD dwFlags;					// 0xC4
	DWORD dwFlags2;					// 0xC8
	DWORD dwUnk11[3];				// 0xCC
	d2_Packet * ptPacket;				// 0xD8
	DWORD dwUnk12;    				// 0xDC
	UnitAny * ptChangedNext;			// 0xE0
	UnitAny * ptRoomNext;			// 0xE4	
	UnitAny * ptListNext;      		// 0xE8
};

struct UnitPlayer : UnitAny
{
};

struct UnitItem : UnitAny
{
};

struct UnitMonster : UnitAny
{
};

struct UnitObject : UnitAny
{
};

struct CellBlockHeader {
	DWORD _1;					// 0x00
	DWORD width;				// 0x04
	DWORD height;				// 0x08
	// All I care about for now.
};

struct CellFile {
	DWORD version;				// 0x00
	DWORD dwFlags;				// 0x04
	DWORD _1;					// 0x08
	DWORD termination;			// 0x0C
	long directions;			// 0x10
	long frames;				// 0x14
	CellBlockHeader * Blocks[100];// 0x18 must realize there aren't going to be this many.  
							//      Its dynamic.  Its really frames*directions
};

struct CellContext {
	void * ptCellFileUnk;					// 0x00
	CellFile * ptCellFile;		// 0x04
	int frame;				// 0x08
	DWORD _3;					// 0x0C
};

struct skill_t {
	char			name[64];
	WORD			skillID;
};

struct d2_WpId {
	int		oldId;
	int		Act;
	int		Wp;
};

// Table to convert oldWpId to Act/Waypoint
static d2_WpId WpId_Tbl[] =
{
	{0x01, 1, 1},{0x03, 1, 2},{0x04, 1, 3},{0x05, 1, 4},{0x06, 1, 5},{0x1b, 1, 6},{0x1d, 1, 7},{0x20, 1, 8},{0x23, 1, 9},
	{0x28, 2, 1},{0x30, 2, 2},{0x2a, 2, 3},{0x39, 2, 4},{0x2b, 2, 5},{0x2c, 2, 6},{0x34, 2, 7},{0x4a, 2, 8},{0x2e, 2, 9},
	{0x4b, 3, 1},{0x4c, 3, 2},{0x4d, 3, 3},{0x4e, 3, 4},{0x4f, 3, 5},{0x50, 3, 6},{0x51, 3, 7},{0x53, 3, 8},{0x65, 3, 9},
	{0x67, 4, 1},{0x6a, 4, 2},{0x6b, 4, 3},
	{0x6d, 5, 1},{0x6f, 5, 2},{0x70, 5, 3},{0x71, 5, 4},{0x73, 5, 5},{0x7b, 5, 6},{0x75, 5, 7},{0x76, 5, 8},{0x81, 5, 9},
};

struct NpcMenuText { // Size 0x110
	DWORD		_1;			//0x00
	DWORD		_2;			//0x04
	wchar_t		text[100];	//0x08-0xCF
	DWORD		_3;			//0xD0
	DWORD		_4;			//0xD4
	DWORD		_5;			//0xD8
	DWORD		_6;			//0xDC
	DWORD		_7;			//0xE0
	DWORD		_8;			//0xE4
	DWORD		_9;			//0xE8
	DWORD		_10;		//0xEC
	DWORD		_11;		//0xF0
	DWORD		_12;		//0xF4
	DWORD		xOffset;	//0xF8
	DWORD		yOffset;	//0xFC
	DWORD		ID;			//0x100
	DWORD		_14;		//0x104
	DWORD		fontType;	//0x108
	DWORD		fontColor;	//0x10C
};

struct d2_NpcMenu {
	DWORD				_1;					//0x00
	DWORD				_2;					//0x04
	DWORD				_3;					//0x08
	DWORD				_4;					//0x0C
    DWORD				clicked;			//0x10
	DWORD				_6;					//0x14
	DWORD				_7;					//0x18
	DWORD				_8;					//0x1C
	DWORD				_9;					//0x20
	DWORD				_10;				//0x24
	DWORD				_11;				//0x28
	DWORD				X;					//0x2C = X
	DWORD				Y;					//0x30 = Y
	DWORD				SizeX;				//0x34 UI window 'box' size X
	DWORD				SizeY;				//0x38 UI window 'box' size Y
	DWORD				_16;				//0x3C
	DWORD				_17;				//0x40
	DWORD				MenuId1;			//0x44
	DWORD				MenuId2;			//0x48
	DWORD				_20;				//0x4C
	DWORD				NumMenuLines;		//0x50 1 based; MenuTitleName is line 1
	DWORD				CurFrame;			//0x54
	DWORD				_23;				//0x58
	DWORD				HighlightStyle;		//0x5C 0x01 Blue highlight, 0x02 Spining pentagrams
	//DWORD				_25;				//0x60 strange crap
	//DWORD				_26;				//0x64 strange crap
	NpcMenuText		menuText[10];		//0x60
	/*
	NpcMenuText		menuText1;			//0x60
	NpcMenuText		menuText2;			//
	NpcMenuText		menuText3;			//
	NpcMenuText		menuText4;			//
	NpcMenuText		menuText5;			//
	NpcMenuText		menuText6;			//
	NpcMenuText		menuText7;			//
	NpcMenuText		menuText8;			//
	NpcMenuText		menuText9;			//
	NpcMenuText		menuText10;			//
	*/
	//wchar_t		MenuTitleName[100];	//0x68 "Warriv", "Decard Cain", "Charsi", "Talk"
};

typedef void NpcMainMenuFunction_t();
struct d2_NpcMainMenuFunctionTable
{
	DWORD NpcId;
	DWORD Count;
	WORD Entries[5];
	void* Functions[5];
	char unknown_0x01;
};

struct ButtonAttrib;


/*********************************************************************************************
// 6F8A5610   81EC 80000000    SUB ESP,80                               ; DrawImage
// 6F8A65A0   81EC 84000000    SUB ESP,84                               ; DrawButton
// 6F8ABD50   83EC 58          SUB ESP,58                               ; DrawImage2
// 6F8B1130   81EC 74080000    SUB ESP,874                              ; DrawTextBox
// 6F8A82D0   81EC D4080000    SUB ESP,8D4                              ; DrawEditBox

**********************************************************************************************/

#ifndef botNETLIBRARY

typedef bool __stdcall ButtonHandler_t (void * pptCallee);
typedef bool __stdcall ButtonHandler2_t (int unk, void * pptCallee);
typedef bool __fastcall DrawHandler_t (ButtonAttrib * pptCallee); 

#else ///clr temp thingy

typedef bool __stdcall ButtonHandler_t (void * pptCallee);
typedef bool __stdcall ButtonHandler2_t (int unk, void * pptCallee);
typedef bool __stdcall DrawHandler_t (ButtonAttrib * pptCallee);  //Temp just so /clr doesnt bitch at me ;)

#endif
enum eButtonType { D2WIN_EDITBOX = 1, D2WIN_IMAGE, D2WIN_IMAGE2, D2WIN_TEXTBOX, D2WIN_SCROLLBAR,  D2WIN_BUTTON,
			    D2WIN_LIST, D2WIN_TIMER, D2WIN_SMACK, D2WIN_PROGRESSBAR, D2WIN_POPUP, D2WIN_ACCOUNTLIST };

struct ButtonAttrib {					// 0x40 bytes
	eButtonType eType;					// 0x00
	BYTE * _1;							// 0x04
	DWORD flags;						// 0x08 first bit is Enabled
	int Xpos;							// 0x0C
	int Ypos;							// 0x10
	int width;							// 0x14
	int height;							// 0x18
	DrawHandler_t * Drawhandler;		// 0x1C //Draw Handler fastcall
	ButtonHandler_t * Handler_1;		// 0x20
	ButtonHandler2_t * OnMouseDown;		// 0x24 //Called on down click
	ButtonHandler2_t * OnMouseUp;		// 0x28	//Called on Up click  these two are prolly just to draw thw button effects
	DWORD _2[2];						// 0x2C
	ButtonHandler_t *  OnClickHandler;	// 0x34 //this is the meat and potatoes
	ButtonHandler_t * Handler_2;		// 0x38 //Seems to appear on images (2)
	ButtonAttrib * ptNext;				// 0x3C	 
};
//number of controls + number of sub controls
//6FA3D0B0  00 00 00 00 00 00 00 00 19 00 00 00 00 00 00 00  ...............
//6FA3CA00

struct D2WIN_EditBox : ButtonAttrib {
	DWORD Unk2[2];						// 0x40
	DWORD MaxLength;					// 0x48
	DWORD Unk3;							// 0x4C
	DWORD Length;						// 0x50 //must be set when writing text, real length - 1, FFFFFFFF when no text
	DWORD CursorLoc;					// 0x54
	DWORD CursorLoc2;					// 0x58
	wchar_t Text[0x100];				// 0x5C
	DWORD Unk4[40];						// 0x15C
	DWORD CursorPosition;				// 0x15C
	DWORD Unk5;							// 0x15C
	void * OnCommit;					// 0x264
	void * OnKeyDown;					// 0x268
	void * OnKeyUp;						// 0x26C

};	

struct D2WIN_Image : ButtonAttrib {		// 0x30 extra bytes for a total of 0x70 bytes in length
	void * ptr;
	DWORD _3[0xB];						// 0x40
};

struct D2WIN_Textbox : ButtonAttrib {	// 0xC0 extra bytes for a total of 0x100 bytes in length
	DWORD UNK1[0x2];					// 0x40
	D2TextInfo * FirstLine;				// 0x48 
	D2TextInfo * LastLine;				// 0x4C	
	D2TextInfo * FirstVisibleLine;		// 0x50	
	DWORD NumberOfLines;				// 0x54
	DWORD FirstVisibleLineIndex;		// 0x58 //possibly scroll bar position
	DWORD Unk2[0xD];					// 0x5C
	ButtonAttrib * ScrollBar;			// 0x90
	//DWORD _3[0x30];					// 0x40
};


struct D2WIN_Button : ButtonAttrib {	// 0x3C0 extra bytes, for a total of 0x400 bytes in length
	DWORD _3[2];						// 0x40
	bool IsClicked;						// 0x48
	DWORD _4[5];						// 0x4C
	DWORD TextFont;						// 0x60
	wchar_t Text[0x100];				// 0x64
};

struct D2WIN_Smack : ButtonAttrib {	
	char tmpfile[0x100];				// 0x40
};

struct D2WIN_ScrollBar : ButtonAttrib {	
	DWORD _3[4];						// 0x40
	ButtonAttrib * Parent;
};

struct D2TextInfo {
	wchar_t * Text;		//hold game name for example
	wchar_t * Text2;  //holds game num players for example
	DWORD Unk1[3];
	DWORD Color;
	DWORD Unk2;
	D2TextInfo * ptNext;
};

//************************ PRE PACKET TYPES ******************
#define pp_Buy								0x32 //4 DWORD npcid, DWORD itemID, DWORD shift, DWORD price
#define pp_Sell								0x33 //4 DWORD npcid, DWORD itemID, DWORD unk_0, DWORD price
#define pp_DropToInventory					0x18 //4 DWORD itemID, DWORD x, DWORD y, DWORD loc
#define pp_PickupFromInventory				0x19 //1 DWORD itemID
#define pp_SwapInventoryItem				0x1F //1 DWORD cursoritemID, DWORD currentitemID, DWORD x, DWORD y
#define pp_Repair							0x35 //4 DWORD npcid, DWORD itemid, DWORD OnBody, DWORD durabor80000000forall
#define pp_UseWaypoint						0x49 //2 DWORD wpid, DWORD dest
#define pp_SetSkill							0x3C //2 DWORD skillID, DWORD unk0xFFFFFFFF
#define pp_RightClickInventory				0x20 //3 DWORD itemuid, DWORD mex, DWORD mey
#define pp_MoveToBelt						0x63 //1 DWORD itemID
#define pp_DropInBelt						0x23 //2 DWORD DWORD cursoritemID, slot
#define pp_SwapBeltItem						0x25 //1 DWORD cursoritemID, DWORD targetID
#define pp_PickupFromBelt					0x24 //1 DWORD itemID
#define pp_RightClickBeltItem				0x26 //3 DWORD itemID, DWORD shift, DWORD unk2_0x0
#define pp_IdentifyItem						0x27 //2 DWORD itemID, DWORD scrollid
#define pp_ClickMerc						0x61 //1 DWORD 0, or slot number




#endif