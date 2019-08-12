#ifndef D2COMMON_H
#define D2COMMON_H


#include "definitions.h"


using namespace System::Runtime::InteropServices;


namespace botNET 
{
	namespace Imports
	{
		__nogc class D2COMMON
		{
		public:
			static void Initialize();

			static UInt32				BaseAddress;

			[DllImport("d2common", EntryPoint="#10001", CallingConvention=CallingConvention::StdCall)]
			static int GetActFromLevelId(int LevelId);

			//[DllImport("d2common", EntryPoint="#10007", CallingConvention=CallingConvention::FastCall)]
			static RoomOther* GetRoomOtherFromRoom(Room1 * ptRoom);
			static void* fptrGetRoomOtherFromRoom;

			//[DllImport("d2common", EntryPoint="#10011", CallingConvention=CallingConvention::FastCall)]
			static int GetCellNum(int unk, TileData * ptTileData, int ActNum, Act * ptAct);
			static void* fptrGetCellNum;

			[DllImport("d2common", EntryPoint="#10118", CallingConvention=CallingConvention::StdCall)]
			static void XOREAX();

			[DllImport("d2common", EntryPoint="#10029", CallingConvention=CallingConvention::StdCall)]
			static UnitAny * GetFirstRoomUnit(Room1 * ptRoom);

			[DllImport("d2common", EntryPoint="#10034", CallingConvention=CallingConvention::StdCall)]
			static void GetRoomCoords(Room1 * ptRoom, Coords * ptCoords);

			//[DllImport("d2common", EntryPoint="#10035", CallingConvention=CallingConvention::FastCall)]
			static void* GetRoomsList(Room1 * ptRoom, Room1 *** RoomsList, int * RoomCount);
			static void* fptrGetRoomsList;

			[DllImport("d2common", EntryPoint="#10056 ", CallingConvention=CallingConvention::StdCall)]
			static Room1 * GetFirstActRoom(Act * ptAct);

			[DllImport("d2common", EntryPoint="#10057", CallingConvention=CallingConvention::StdCall)]
			static int GetLevelIdFromRoom(Room1 * hRoom);

			[DllImport("d2common", EntryPoint="#10063", CallingConvention=CallingConvention::StdCall)]
			static void AddRoomData(Act * ptAct, int LevelId, int Xpos, int Ypos, UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10064", CallingConvention=CallingConvention::StdCall)]
			static void RemoveRoomData(Act * ptAct, int LevelId, int Xpos, int Ypos, UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10082", CallingConvention=CallingConvention::StdCall)]
			static bool IsInTown(Room1 * ptRoom);

			[DllImport("d2common", EntryPoint="#10085", CallingConvention=CallingConvention::StdCall)]
			static int GetTownLevelId(int Act);

			[DllImport("d2common", EntryPoint="#10086", CallingConvention=CallingConvention::StdCall)]
			static bool IsTownLevel(int LevelId);

			[DllImport("d2common", EntryPoint="#10088", CallingConvention=CallingConvention::StdCall)]
			static Drlg * GetMiscFromAct(Act * ptAct);

			[DllImport("d2common", EntryPoint="#10108", CallingConvention=CallingConvention::StdCall)]
			static void AbsScreenToMapCoords(long * ptAbsMouseX, long * ptAbsMouseY);

			[DllImport("d2common", EntryPoint="#10110", CallingConvention=CallingConvention::StdCall)]
			static void MapToAutomapCoords(int * ptXpos, int * ptYPos);

			[DllImport("d2common", EntryPoint="#10111", CallingConvention=CallingConvention::StdCall)]
			static void MapToAbsScreenCoords(long * ptXpos, long * ptYpos);

			[DllImport("d2common", EntryPoint="#10118", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision118(Room1* room, int x, int y, int bitmask);

			[DllImport("d2common", EntryPoint="#10119", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision119(Room1* room, int x, int y, int pattern, int bitmask);

			[DllImport("d2common", EntryPoint="#10122", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision122(Room1* room, int x, int y, int pattern, int bitmask);

			[DllImport("d2common", EntryPoint="#10124", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision124(Room1* room, int x, int y, int pattern, int bitmask);

			[DllImport("d2common", EntryPoint="#10126", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision126(Room1* room, int x, int y, int pattern, int bitmask);

			[DllImport("d2common", EntryPoint="#10127", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision127(Room1* room, int x, int y, int bitmask);

			[DllImport("d2common", EntryPoint="#10128", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision128(Room1* room, int x, int y, int pattern, int bitmask);

			[DllImport("d2common", EntryPoint="#10130", CallingConvention=CallingConvention::StdCall)]
			static bool CheckCollision130(Room1* room, int x, int y, int pattern, int bitmask);
/*
			[DllImport("d2common", EntryPoint="#10131", CallingConvention=CallingConvention::FastCall)]
			static bool CheckCollision131(Room1* room, int x1, int y1, int x2, int y2, int pattern, int bitmask1, int bitmaskline);

			[DllImport("d2common", EntryPoint="#10132", CallingConvention=CallingConvention::FastCall)]
			static bool CheckCollision132(Room1* room, int x1, int y1, int x2, int y2, int pattern, int bitmask1, int bitmaskline);

			[DllImport("d2common", EntryPoint="#10132", CallingConvention=CallingConvention::FastCall)]
			static void Set?CheckCollision132(Room1* room, int x1, int y1, Room1 room*, int x2, int y2, int pattern, int bitmask);
*/
			[DllImport("d2common", EntryPoint="#10146", CallingConvention=CallingConvention::StdCall)]
			static void PathSetVelocity(Path * hPath, DWORD newVelocity, char * file, int line);

			[DllImport("d2common", EntryPoint="#10147", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetVelocity(Path * hPath);

			[DllImport("d2common", EntryPoint="#10156", CallingConvention=CallingConvention::StdCall)]
			static bool PathDestroyPath(Path * hPath, void * Mempool);

			[DllImport("d2common", EntryPoint="#10157", CallingConvention=CallingConvention::StdCall)]
			static int PathGetPoints(Path * hPath, PathPoint ** pptPoint);

			[DllImport("d2common", EntryPoint="#10158", CallingConvention=CallingConvention::StdCall)]
			static BYTE PathGetDirection(Path * hPath);

			[DllImport("d2common", EntryPoint="#10159", CallingConvention=CallingConvention::StdCall)]
			static BYTE PathGetNewDirection(Path * hPath);

			[DllImport("d2common", EntryPoint="#10160", CallingConvention=CallingConvention::StdCall)]
			static void PathUpdateDirection(Path * hPath, BYTE bDir);

			[DllImport("d2common", EntryPoint="#10161", CallingConvention=CallingConvention::StdCall)]
			static void PathSetDirection(Path * hPath, BYTE bDir);

			[DllImport("d2common", EntryPoint="#10162", CallingConvention=CallingConvention::StdCall)]
			static int PathGetX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10163", CallingConvention=CallingConvention::StdCall)]
			static int PathGetY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10166", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetTargetX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10165", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetTargetY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10166", CallingConvention=CallingConvention::StdCall)]
			static Room1 * PathGetRoom(Path * hPath);

			[DllImport("d2common", EntryPoint="#10167", CallingConvention=CallingConvention::StdCall)]
			static void PathSetRoom(Path * hPath, Room1 * ptRoom);

			[DllImport("d2common", EntryPoint="#10168", CallingConvention=CallingConvention::StdCall)]
			static Room1 * PathGetRoom2(Path * hPath);

			[DllImport("d2common", EntryPoint="#10169", CallingConvention=CallingConvention::StdCall)]
			static void PathClearRoom2(Path * hPath);

			[DllImport("d2common", EntryPoint="#10170", CallingConvention=CallingConvention::StdCall)]
			static Path * PathSetTargetPos(Path * hPath, int PosX, int PosY);

			[DllImport("d2common", EntryPoint="#10171", CallingConvention=CallingConvention::StdCall)]
			static void PathGetTarget(Path * hPath, int * TargetType, DWORD * UnitId);

			[DllImport("d2common", EntryPoint="#10175", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetFirstPointX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10176", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetFirstPointY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10177", CallingConvention=CallingConvention::StdCall)]
			static WORD PathGetLastPointX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10178", CallingConvention=CallingConvention::StdCall)]
			static WORD PathGetLastPointY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10179", CallingConvention=CallingConvention::StdCall)]
			static void PathSetTargetUnit(Path * hPath, UnitAny * hTarget);

			[DllImport("d2common", EntryPoint="#10180", CallingConvention=CallingConvention::StdCall)]
			static UnitAny * PathGetTargetUnit(Path * hPath);

			[DllImport("d2common", EntryPoint="#10181", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetCollisionType(Path * hPath);

			[DllImport("d2common", EntryPoint="#10182", CallingConvention=CallingConvention::StdCall)]
			static void PathSetCollisionType(Path * hPath, DWORD Type);

			[DllImport("d2common", EntryPoint="#10185", CallingConvention=CallingConvention::StdCall)]
			static void PathSetType(Path * hPath, int eType);

			[DllImport("d2common", EntryPoint="#10186", CallingConvention=CallingConvention::StdCall)]
			static void PathSetAsLastType(Path * hPath);

			[DllImport("d2common", EntryPoint="#10187", CallingConvention=CallingConvention::StdCall)]
			static int PathGetType(Path * hPath);

			[DllImport("d2common", EntryPoint="#10188", CallingConvention=CallingConvention::StdCall)]
			static void PathSetNewDistance(Path * hPath, BYTE NewDist);

			[DllImport("d2common", EntryPoint="#10189", CallingConvention=CallingConvention::StdCall)]
			static BYTE PathGetMaxDistance(Path * hPath);

			[DllImport("d2common", EntryPoint="#10190", CallingConvention=CallingConvention::StdCall)]
			static void PathSetDistance(Path * hPath, BYTE Dist);

			[DllImport("d2common", EntryPoint="#10191", CallingConvention=CallingConvention::StdCall)]
			static BYTE PathGetDistance(Path * hPath);

			[DllImport("d2common", EntryPoint="#10192", CallingConvention=CallingConvention::StdCall)]
			static void PathSetIDAMax(Path * hPath, BYTE NewDist);

			[DllImport("d2common", EntryPoint="#10193", CallingConvention=CallingConvention::StdCall)]
			static void PathAdjustDirection(Path * hPath);

			[DllImport("d2common", EntryPoint="#10194", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetPrecisionX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10195", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetPrecisionY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10196", CallingConvention=CallingConvention::StdCall)]
			static void PathSetPrecisionX(Path * hPath, DWORD NewX);

			[DllImport("d2common", EntryPoint="#10197", CallingConvention=CallingConvention::StdCall)]
			static void PathSetPrecitionY(Path * hPath, DWORD NewY);

			[DllImport("d2common", EntryPoint="#10198", CallingConvention=CallingConvention::StdCall)]
			static bool PathGetSaveStep(Path * hPath, PathPoint ** StepPoint);

			[DllImport("d2common", EntryPoint="#10199", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetSaveX(Path * hPath);

			[DllImport("d2common", EntryPoint="#10200", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetSaveY(Path * hPath);

			[DllImport("d2common", EntryPoint="#10203", CallingConvention=CallingConvention::StdCall)]
			static void PathSetRotateFlag(Path * hPath, bool Rotate);

			[DllImport("d2common", EntryPoint="#10204", CallingConvention=CallingConvention::StdCall)]
			static void PathClearPoint2(Path * hPath);

			[DllImport("d2common", EntryPoint="#10205", CallingConvention=CallingConvention::StdCall)]
			static void PathSetStepNum(Path * hPath, BYTE bStep);

			[DllImport("d2common", EntryPoint="#10206", CallingConvention=CallingConvention::StdCall)]
			static BYTE PathGetStepNum(Path * hPath);

			[DllImport("d2common", EntryPoint="#10208", CallingConvention=CallingConvention::StdCall)]
			static void PathSetPathingFlag(Path * hPath, bool val);

			[DllImport("d2common", EntryPoint="#10209", CallingConvention=CallingConvention::StdCall)]
			static void PathGetPathingFlag(Path * hPath);

			[DllImport("d2common", EntryPoint="#10210", CallingConvention=CallingConvention::StdCall)]
			static DWORD PathGetUnitCollisionPattern(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10211", CallingConvention=CallingConvention::StdCall)]
			static void PathSetUnitCollisionPattern(UnitAny * ptUnit, DWORD newCol);

			[DllImport("d2common", EntryPoint="#10212", CallingConvention=CallingConvention::StdCall)]
			static void PathSetMoveFlags(UnitAny * ptUnit, bool moving);

			[DllImport("d2common", EntryPoint="#10231", CallingConvention=CallingConvention::StdCall)]
			static void PathUnkSetSomething(Path* p, UnitAny* u, Room1* r, int x, int y);


			[DllImport("d2common", EntryPoint="#10243", CallingConvention=CallingConvention::StdCall)]
			static bool InventoryItem(d2_Inventory * ptInventory, UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10245", CallingConvention=CallingConvention::StdCall)]
			static bool CheckPageForRoom(d2_Inventory * ptInventory, UnitItem * ptItem, int unk, BYTE * ptX, BYTE * ptY, int page);

			[DllImport("d2common", EntryPoint="#10252", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetItemAtXY(d2_Inventory* inv, int x, int y, int * xpix, int * ypix, DWORD val10409, int loc);

			[DllImport("d2common", EntryPoint="#10257", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetEquippedItem(d2_Inventory * ptInventory, int spot);

			[DllImport("d2common", EntryPoint="#10262", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetCursorItem(d2_Inventory * ptInventory);

			[DllImport("d2common", EntryPoint="#10271 - mattlant ", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetBeltItem(d2_Inventory * ptInventory, int beltspot/*0-F*/);

			[DllImport("d2common", EntryPoint="#10277", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetFirstInventoryItem(d2_Inventory * ptInventory);

			[DllImport("d2common", EntryPoint="#10304", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * GetNextInventoryItem(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10305", CallingConvention=CallingConvention::StdCall)]
			static UnitItem * IsItem(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10306", CallingConvention=CallingConvention::StdCall)]
			static DWORD GetItemId(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10307", CallingConvention=CallingConvention::StdCall)]
			static int GetItemNodePage(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10314", CallingConvention=CallingConvention::StdCall)]
			static Skill * GetNextSkill(Skill * ptSkill);

			[DllImport("d2common", EntryPoint="#10320", CallingConvention=CallingConvention::StdCall)]
			static Skill * GetStartSkill(UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10321", CallingConvention=CallingConvention::StdCall)]
			static Skill * GetLeftSkill(UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10322", CallingConvention=CallingConvention::StdCall)]
			static Skill * GetRightSkill(UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10323", CallingConvention=CallingConvention::StdCall)]
			static Skill * GetCurrentSkill(UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10333", CallingConvention=CallingConvention::StdCall)]
			static DWORD AutoMap1(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10334", CallingConvention=CallingConvention::StdCall)]
			static DWORD AutoMap2(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10338", CallingConvention=CallingConvention::StdCall)]
			static int GetCollisionPatternFromUnit(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10338", CallingConvention=CallingConvention::StdCall)]
			static int GetCollisionBitsFromUnit(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10339", CallingConvention=CallingConvention::StdCall)]
			static int GetStashGoldLimit(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10342", CallingConvention=CallingConvention::StdCall)]
			static Room1 * GetRoomFromUnit(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10389", CallingConvention=CallingConvention::StdCall)]
			static bool IsUnitInRoom(Room1 * ptRoom, UnitAny * hUnit);

			[DllImport("d2common", EntryPoint="#10392", CallingConvention=CallingConvention::StdCall)]
			static bool IsUnitObjectDoor(UnitObject * ptUnit);

			[DllImport("d2common", EntryPoint="#10394", CallingConvention=CallingConvention::StdCall)]
			static ObjectBinData * GetObjectBinData(UnitObject * ptObject);

			[DllImport("d2common", EntryPoint="#10402", CallingConvention=CallingConvention::StdCall)]
			static DWORD GetArgForGetItemAtXY(UnitAny * ptUnit, int loc_page, int gametype);

			[DllImport("d2common", EntryPoint="#10424", CallingConvention=CallingConvention::StdCall)]
			static PlayerData * GetPlayerData(UnitPlayer * ptUnit);

			[DllImport("d2common", EntryPoint="#10487", CallingConvention=CallingConvention::StdCall)]
			static BOOL GetUnitState(UnitAny *ptUnit, DWORD stateno);

			[DllImport("d2common", EntryPoint="#10519", CallingConvention=CallingConvention::StdCall)]
			static int GetBaseStat(UnitAny * ptUnit, int StatId, int StatTblIndex);

			[DllImport("d2common", EntryPoint="#10520", CallingConvention=CallingConvention::StdCall)]
			static int GetAddedStat(UnitAny * ptUnit, int StatId, int StatTblIndex);

			[DllImport("d2common", EntryPoint="#10521", CallingConvention=CallingConvention::StdCall)]
			static int GetStatValue3(UnitAny * ptUnit, int StatId, int StatTblIndex);

			[DllImport("d2common", EntryPoint="#10535", CallingConvention=CallingConvention::StdCall)]
			static UnitAny * UnitGetParent(UnitAny *child, DWORD *unk);

			[DllImport("d2common", EntryPoint="#10564", CallingConvention=CallingConvention::StdCall)]
			static int GetMaxHealth(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10565", CallingConvention=CallingConvention::StdCall)]
			static int GetMaxMana(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10566", CallingConvention=CallingConvention::StdCall)]
			static int GetMaxStamina(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10600", CallingConvention=CallingConvention::StdCall)]
			static ItemBinData * GetItemBinFromClass(int itemclsid);

			[DllImport("d2common", EntryPoint="#10602", CallingConvention=CallingConvention::StdCall)]
			static int * GetItemIdFromCode(char itemcode);

			[DllImport("d2common", EntryPoint="#10604", CallingConvention=CallingConvention::StdCall)]
			static char * GetItemMagicalMods(int modnum);

			[DllImport("d2common", EntryPoint="#10614", CallingConvention=CallingConvention::StdCall)]
			static char * GetItemQualityString(int qualnum);

			[DllImport("d2common", EntryPoint="#10616", CallingConvention=CallingConvention::StdCall)]
			static char * GetItemGemMods(int indexnum);

			[DllImport("d2common", EntryPoint="#10628", CallingConvention=CallingConvention::StdCall)]
			static int GetExperienceForLevel(int PlayerClass, int TargetLevel);

			[DllImport("d2common", EntryPoint="#10695", CallingConvention=CallingConvention::StdCall)]
			static int GetItemQuality(UnitAny * ptUnit);

			[DllImport("d2common", EntryPoint="#10719", CallingConvention=CallingConvention::StdCall)]
			static int GetItemPage(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10751", CallingConvention=CallingConvention::StdCall)]
			static int GetItemType(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10757", CallingConvention=CallingConvention::StdCall)]
			static int GetItemRequiredLevel(UnitPlayer * ptPlayer, UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10765", CallingConvention=CallingConvention::StdCall)]
			static bool TwoHandedItemCheck(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10775", CallingConvention=CallingConvention::StdCall)]
			static int GetUnitPrice(UnitPlayer * pl, UnitItem * item, int Unk /*0*/, void * somestruct, int NPCID, int buysell);

			[DllImport("d2common", EntryPoint="#10776", CallingConvention=CallingConvention::StdCall)]
			static int GetNumberOfUnidItems(UnitPlayer * ptPlayer);

			[DllImport("d2common", EntryPoint="#10795", CallingConvention=CallingConvention::StdCall)]
			static int GetMaxItemQuantity(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10815", CallingConvention=CallingConvention::StdCall)]
			static int GetMaxItemSockets(UnitItem * ptItem);

			[DllImport("d2common", EntryPoint="#10892", CallingConvention=CallingConvention::StdCall)]
			static Msg * PrintOverhead(DWORD Unk/*always 0*/ , char * Message,  DWORD dwMsgId);

			//[DllImport("d2common", EntryPoint="#10949", CallingConvention=CallingConvention::FastCall)]
			static Skill * GetUnitSkill(UnitPlayer * ptPlayer, DWORD SkillId, DWORD Flags);
			static void* fptrGetUnitSkill;

			[DllImport("d2common", EntryPoint="#10957", CallingConvention=CallingConvention::StdCall)]
			static DWORD * GetSkillFlags(Skill * hSkill);

			[DllImport("d2common", EntryPoint="#10963", CallingConvention=CallingConvention::StdCall)]
			static short GetSkillType(Skill * ptSkill);

			[DllImport("d2common", EntryPoint="#11152", CallingConvention=CallingConvention::StdCall)]
			static bool HasWaypoint(int WaypointArea);
		};


	}


	
}

using namespace botNET::Imports;

#endif
