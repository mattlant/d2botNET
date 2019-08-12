#ifndef PARTY_H
#define PARTY_H


using namespace botNET::Units;

namespace botNET
{
	namespace Units
	{

	__gc public class RosterPlayer;

	}


	__gc public class Party
	{

	public:
	
		//static void Party::Loot(botNET::Units::RosterPlayer* Pl, bool EnableLoot);
		//static void Party::Mute(botNET::Units::RosterPlayer* Pl, bool EnableMute);
		//static void Party::Squelch(botNET::Units::RosterPlayer* Pl, bool EnableSquelch);
		//static void Party::Hostile(botNET::Units::RosterPlayer* Pl, bool EnableHostile);
	
		//static void Party::Action0x05(botNET::Units::RosterPlayer* Pl);

		static void Party::Invite(botNET::Units::RosterPlayer* Pl);
		static void Party::Cancel(botNET::Units::RosterPlayer* Pl);
		static void Party::Accept(botNET::Units::RosterPlayer* Pl);
		static void Party::Leave();

	public private:

	};

}

#endif