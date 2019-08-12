#include "botnet.h"
#include "d2common.h"
#include "importutils.h"

namespace botNET
{
	namespace Imports
	{

		void D2COMMON::Initialize()
		{
			BaseAddress = Importer::D2Common->BaseAddress.ToInt32();

			D2COMMON::fptrGetRoomOtherFromRoom =		Importer::GetFunctionAddress(Importer::D2Common, 10007).ToPointer();
			D2COMMON::fptrGetCellNum =					Importer::GetFunctionAddress(Importer::D2Common, 10011).ToPointer();
			D2COMMON::fptrGetRoomsList =				Importer::GetFunctionAddress(Importer::D2Common, 10035).ToPointer();
			D2COMMON::fptrGetUnitSkill =				Importer::GetFunctionAddress(Importer::D2Common, 10949).ToPointer();
		}

		RoomOther* D2COMMON::GetRoomOtherFromRoom(Room1* ptRoom)
		{
			RoomOther* retval;
			__asm
			{
				mov ecx, ptRoom
				mov eax, D2COMMON::fptrGetRoomOtherFromRoom
				call eax
				mov retval, eax
			}
			return retval;
		}

		int D2COMMON::GetCellNum(int unk, TileData * ptTileData, int ActNum, Act * ptAct)
		{
			int retval;
			__asm
			{
				push ptAct
				push ActNum
				mov edx, ptTileData
				mov ecx, unk
				mov eax, D2COMMON::fptrGetCellNum
				call eax
				mov retval, eax
			}
			return retval;
		}

		void * D2COMMON::GetRoomsList(Room1 * ptRoom, Room1 *** RoomsList, int * RoomCount)
		{
			void* retval;
			__asm
			{
				push RoomCount
				mov edx, RoomsList
				mov ecx, ptRoom
				mov eax, D2COMMON::fptrGetRoomsList
				call eax
				mov retval, eax
			}
			return retval;
		}

		Skill * D2COMMON::GetUnitSkill(UnitPlayer * ptPlayer, DWORD SkillId, DWORD Flags)
		{
			Skill* retval;
			__asm
			{
				push Flags
				mov edx, SkillId
				mov ecx, ptPlayer
				mov eax, D2COMMON::fptrGetUnitSkill
				call eax
				mov retval, eax
			}
			return retval;
		}

	}

}





