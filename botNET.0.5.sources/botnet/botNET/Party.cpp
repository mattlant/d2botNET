#include "botnet.h"
#include ".\party.h"

#include "rosterplayer.h"
#include "eventargs.h"
#include "game.h"
#include "d2exports.h"
#include "d2client.h"
 

namespace botNET
{
	/*

	// TODO: These do not work!  We need the function that takes a bool to set their on/off state!
	// Generated packet syntax should be: 5d [BYTE Action] [BOOL On/Off] [DWORD PlayerID]
	//								 NOT: 5e [BYTE Action] [DWORD PlayerID] like the non-togglable actions (Leave, ...)
	
	void Party::Loot(botNET::Units::RosterPlayer* Pl, bool EnableLoot)
	{
		//D2CLIENT::PartyUIButton(1,Pl->UniqueID);
	}

	void Party::Mute(botNET::Units::RosterPlayer* Pl, bool EnableMute)
	{
		//D2CLIENT::PartyUIButton(2,Pl->UniqueID);
	}

	void Party::Squelch(botNET::Units::RosterPlayer* Pl, bool EnableSquelch)
	{
		//D2CLIENT::PartyUIButton(3,Pl->UniqueID);
	}

	void Party::Hostile(botNET::Units::RosterPlayer* Pl, bool EnableHostile)
	{
		//D2CLIENT::PartyUIButton(4,Pl->UniqueID);
	}

	void Party::Action0x05(botNET::Units::RosterPlayer* Pl) // TODO: Find party action 5 + determine if toggle type
	{
		//D2CLIENT::PartyUIButton(5,Pl->UniqueID);
	}
	*/

	void Party::Invite(botNET::Units::RosterPlayer* Pl)
	{
		//if(Player->Type != 0) throw new ArgumentException("Only Player units can be passed to Party methods");
		D2CLIENT::PartyUIButton(6,Pl->UniqueID);
	}

	void Party::Cancel(botNET::Units::RosterPlayer* Pl)
	{
		//if(Player->Type != 0) throw new ArgumentException("Only Player units can be passed to Party methods");
		D2CLIENT::PartyUIButton(7,Pl->UniqueID);
	}

	void Party::Accept(botNET::Units::RosterPlayer* Pl)
	{
		//if(Player->Type != 0) throw new ArgumentException("Only Player units can be passed to Party methods");
		D2CLIENT::PartyUIButton(8,Pl->UniqueID);
	}

	void Party::Leave()
	{ 
		D2CLIENT::PartyUIButton(9, (*D2CLIENT::PlayerUnit)->dwId);
	}
}
