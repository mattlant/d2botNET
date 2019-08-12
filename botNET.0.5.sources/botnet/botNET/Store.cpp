#include "botnet.h"
#include ".\store.h"
#include "item.h"

#include "d2client.h"
#include "d2common.h"



namespace botNET
{

	void Store::Repair()
	{
		if(!*D2CLIENT::IsInteractedWithNPC)
			throw new ApplicationException("You are not interacted with an NPC");

		D2CLIENT::PrePacket4(0x35, *D2CLIENT::InteractedNPCUniqueID, 0, 0, 0x80000000);
	}

	void Store::Repair(botNET::Units::Item * item)
	{
		item->IsValidEx();

		if(!*D2CLIENT::IsInteractedWithNPC)
			throw new ApplicationException("You are not interacted with an NPC");

		UnitItem* it = (UnitItem*)item->unit;
		int loc = 0;

		if(it->ptItemData->Location == 1)
			loc = 1;

		// full durability, dur > maxdur will repair, ignore that
		if(D2COMMON::GetBaseStat(it, 0x48, 0) == D2COMMON::GetBaseStat(it, 0x49, 0))
            return;

		D2CLIENT::PrePacket4(0x35, *D2CLIENT::InteractedNPCUniqueID, it->dwId, loc, D2COMMON::GetBaseStat(it, 0x48, 0));
	}
}
