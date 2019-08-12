#include "botnet.h"
#include ".\automap.h"

#include "room.h"
#include "UnitBase.h"
#include "presetunit.h"
#include "d2client.h"
#include "d2common.h"


namespace botNET
{
	namespace Mapping
	{
		void AutoMap::RevealRoom(Mapping::Room * RoomToReveal)
		{
			if(RoomToReveal->room->pRoom) 
				D2CLIENT::RevealAutomapRoom(RoomToReveal->room->pRoom, 1, *D2CLIENT::AutomapLayer);
			else
			{
				D2COMMON::AddRoomData(RoomToReveal->room->ptDrlgLevel->pDrlg->pAct, RoomToReveal->room->ptDrlgLevel->LevelNo, 
					RoomToReveal->room->xPos, RoomToReveal->room->yPos, *D2CLIENT::PlayerUnit);

				D2CLIENT::RevealAutomapRoom(RoomToReveal->room->pRoom, 1, *D2CLIENT::AutomapLayer);

				D2COMMON::RemoveRoomData(RoomToReveal->room->ptDrlgLevel->pDrlg->pAct, RoomToReveal->room->ptDrlgLevel->LevelNo, 
					RoomToReveal->room->xPos, RoomToReveal->room->yPos, *D2CLIENT::PlayerUnit);
			}
		}

		bool AutoMap::ConvertCoords(UnitBase * uUnit, int * X, int * Y)
		{
			int x = D2COMMON::AutoMap1(uUnit->unit);
			int y = D2COMMON::AutoMap2(uUnit->unit);


			x = x / *D2CLIENT::AutoMapDiv - *D2CLIENT::AutoMapXSub + 8;
			y = y / *D2CLIENT::AutoMapDiv - *D2CLIENT::AutoMapYSub - 8;

			if(x < *D2CLIENT::AutoMapLeftBound || x > *D2CLIENT::AutoMapRightBound)
				return false;
			if(y < *D2CLIENT::AutoMapTopBound || y > *D2CLIENT::AutoMapBottomBound)
				return false;

			*X = x;
			*Y = y;
			
			return true;
		}

		bool AutoMap::ConvertCoords(int * X, int * Y)
		{
			int x = *X;
			int y = *Y;

			D2COMMON::MapToAutomapCoords(&x, &y);

			x = x / *D2CLIENT::AutoMapDiv - *D2CLIENT::AutoMapXSub + 8;
			y = y / *D2CLIENT::AutoMapDiv - *D2CLIENT::AutoMapYSub - 8;

			if(x < *D2CLIENT::AutoMapLeftBound || x > *D2CLIENT::AutoMapRightBound)
				return false;
			if(y < *D2CLIENT::AutoMapTopBound || y > *D2CLIENT::AutoMapBottomBound)
				return false;

			*X = x;
			*Y = y;
			
			return true;
		}

		bool AutoMap::get_Visible()
		{
			return *D2CLIENT::IsAutoMapOn;
		}

		void AutoMap::DrawItems()
		{
			OnDrawItems(NULL, NULL);
		}




	}

}
