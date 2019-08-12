#include "botnet.h"
#include ".\room.h"
#include "d2client.h"
#include "d2common.h"
#include "presetunit.h"
#include ".\log.h"

using namespace System;
using namespace botNET::Units;


CRITICAL_SECTION RoomCritSect;

namespace botNET {

	namespace Mapping{

		Room::Room(RoomOther * r)
		{
			room = r;
			internalx = r->xPos;
			internaly = r->yPos;  
			this->mPresetUnits = NULL;
		}

		//The following 3 Get functions get rooms based on the Parameters
		//Gets all rooms on teh current level
		Room * Room::Get()[]
		{
			return FindRooms(NULL, NULL, NULL);
		}

		//Gets all rooms on the given level
		Room * Room::Get(AreaLevel Area)[]
		{
			return FindRooms(Area, NULL, NULL);
		}

		//gets the room on the given level that bounds the given x, y
		Room * Room::Get(AreaLevel Area, int x, int y)[]
		{
			return FindRooms(Area, x, y);
		}
		
		//Returns the room teh player is standing in
		Mapping::Room * Room::GetCurrent()
		{
			//get a room freom the player unit and then return as a ARoom object
			::Room1 * rm = (*D2CLIENT::PlayerUnit)->hPath->ptRoom;
			if (!rm) throw new ApplicationException("Room.GetRoom -> Room was not found for the Room you are in (Internal Framework Error?)");
			RoomOther * r2 = rm->ptRoomOther;
			return new Mapping::Room(r2);
		}

		/*
		AreaLevel Room::GetAreaFromXY(int x, int y)
		{
			UnitPlayer *player = GetPlayerUnit();
			if (!player) throw new ApplicationException("Room.GetRoom -> Player Unit was not found");
			//get a room freom the player unit and then return as a ARoom object
			RoomOther * r = player->hPath->ptRoom->ptRoomOther->ptDrlgLevel->pRoomOtherFirst;
			if (!r) throw new ApplicationException("Room.GetRoom -> Room was not found for the Room you are in (Internal Framework Error?)");
			
			DrlgLevel * level = r->ptDrlgLevel->pDrlg->pFirstLevel;
			do {
				if(x > level->LevelX && y > level->LevelY)
				return level->LevelNo;
			} while(level = level->pNext);

			return NULL;

		}*/

		Room * Room::FindRooms(int area, int x, int y)[]
		{	
			RoomOther * r = (*D2CLIENT::PlayerUnit)->hPath->ptRoom->ptRoomOther->ptDrlgLevel->pRoomOtherFirst;
			if(!r) throw new ApplicationException("Could net get initial room");
			::Room1 * rm = (*D2CLIENT::PlayerUnit)->hPath->ptRoom;

			if(area != NULL) {
				if(area < 1 || area > 133) throw new ArgumentException("ARoom.GetRoom -> Level Provided is not valid");
				DrlgLevel * level = (*D2CLIENT::PlayerUnit)->ptAct->ptMisc->pFirstLevel;
						
				//DrlgLevel * level = r->ptDrlgLevel->pDrlg->pFirstLevel;
				//DrlgLevel * level = rm->ptAct->ptMisc->pFirstLevel;
				do {
					if(level->LevelNo == area) break;
				} while(level = level->pNext);

				if(level) r = level->pRoomOtherFirst;
				else throw new ApplicationException("ARoom.GetRoom -> Could not find the given Level. Possibly not in this act");
				if(!r)
					throw new ApplicationException("Could not get the first room of needed level");
			}

			ArrayList * ar = new ArrayList();
			do {
				if(x != NULL && y != NULL) {
					//Is this coord set in this room, if so return just one room
				}
				ar->Add(new Mapping::Room(r));
			}while(r = r->pNext);

			Room * temprooms __gc[] = new Room * [ar->Count];
			ar->CopyTo(temprooms);
			return temprooms;
		}

		//only returns for initialized rooms
		UInt16 Room::get_CollisionDataLowByte(void)[,]
		{
			this->IsValidEx(); 

			bool hasopened = false;
			DrlgColl * collmap;
			WORD * currentloc;
			DWORD x, y;
			UInt16 coll __gc[,];

			Act* act = room->ptDrlgLevel->pDrlg->pAct;
			int levelnum = room->ptDrlgLevel->LevelNo;

			try
			{
				if(!room->pRoom) {
					EnterCriticalSection(&RoomCritSect);
					hasopened = true;
					try
					{
						D2COMMON::AddRoomData(act, levelnum, room->xPos, room->yPos, *D2CLIENT::PlayerUnit);
					}
					catch (...)
					{
						LeaveCriticalSection (&RoomCritSect);
						botNET::Diagnostics::Log::WriteLine ("Exception in get_CollisionDataLowByte -> AddRoomData");
						throw;
					}
				}
				
				collmap = room->pRoom->pColl;
				if(!collmap) throw new ApplicationException("Room.CollisionData -> room pointer no longer valid");

				currentloc = collmap->pMapStart;

				//Setup a multi dim array
				coll = new UInt16 [collmap->nSizeGameX, collmap->nSizeGameY];

				//cycle thru the collision data moving to array
				for(y=0; y < collmap->nSizeGameY; y++) {   
					for(x=0; x < collmap->nSizeGameX; x++) {
						coll[x, y] = *(BYTE*)currentloc;
						currentloc++;
					}
				}
			}
			__finally
			{
				if(hasopened) 
				{
					D2COMMON::RemoveRoomData(act, levelnum, room->xPos, room->yPos, *D2CLIENT::PlayerUnit);
					LeaveCriticalSection(&RoomCritSect);
					hasopened = false;
				}

			}
			return coll;
		}

		UInt16 Room::get_CollisionData(void)[,]
		{
			UInt16 coll __gc[,] = new UInt16 [this->Size.Width, this->Size.Height];

			if(!this->IsInitialized || !this->IsValid()) return coll;

			DrlgColl * collmap = room->pRoom->pColl;
			WORD * currentloc = collmap->pMapStart;
			DWORD x, y;

			//cycle thru the collision data moving to array
			for(y=0; y < collmap->nSizeGameY; y++) {   
				for(x=0; x < collmap->nSizeGameX; x++) {
					Byte cl = *(BYTE*)currentloc;
					coll[x, y] = cl;
					currentloc++;
				}
			}
			return coll;

		}

		bool Room::IsValid()
		{
			return (room && room->xPos == internalx && room->yPos == internaly);
		}

		void Room::IsValidEx()
		{
			if(!(room && room->xPos == internalx && room->yPos == internaly))
				throw new ApplicationException("Room is not valid");
		}

		int Room::get_Number(void)
		{
			return room->pPresetType2info->roomNum;
		}

		System::Drawing::Point Room::get_AreaLocation(void)
		{
			return System::Drawing::Point(room->ptDrlgLevel->AreaX*5, room->ptDrlgLevel->AreaY*5);
		}

		System::Drawing::Point Room::get_AreaOffsetLocation(void)
		{
			return System::Drawing::Point(room->xPos*5 - room->ptDrlgLevel->AreaX*5, room->yPos*5 - room->ptDrlgLevel->AreaY*5);
		}

		AreaLevel Room::get_Area(void)
		{
			return (AreaLevel)room->ptDrlgLevel->LevelNo;
		}

		/////////////////////////////////////////////////////////////////////
		// Property: get_PointerAddress
		/////////////////////////////////////////////////////////////////////
		System::IntPtr Room::get_Pointer() 
		{	
			return IntPtr(room);
		}

		bool Room::get_IsInitialized() 
		{	
			return room->pRoom > 0;
		}

		System::Drawing::Point Room::get_Position() 
		{	
			return System::Drawing::Point(room->xPos*5, room->yPos*5);
		}

		int Room::get_X()
		{
			return room->xPos*5;
		}

		int Room::get_Y()
		{
			return room->yPos*5;
		}

		System::Drawing::Rectangle Room::get_Bounds() 
		{	
			return System::Drawing::Rectangle(room->xPos*5, room->yPos*5, room->xSize*5, room->ySize*5);
		}

		System::Drawing::Size Room::get_Size() 
		{	
			return System::Drawing::Size(room->xSize*5, room->ySize*5);
		}
	}

}
