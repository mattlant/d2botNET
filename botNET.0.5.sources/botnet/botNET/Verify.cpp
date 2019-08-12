#include "botnet.h"
#include ".\Verify.h"
#include ".\UnitBase.h"
#include ".\game.h"
#include "ivalid.h"


namespace botNET
{
namespace Utils
{

		void Verify::IsValidArgEx(IValid * unit)
		{
			if(!unit)
				throw new ArgumentNullException("Passed unit is null");
			if(!unit->IsValid())
				throw new ArgumentException("Passed unit is not valid");
			if(!botNET::Game::gIsInGame)
				throw new ApplicationException("Not in game");
				
		}

		bool Verify::IsValid(RosterPlayer * player)
		{
			return !(player == NULL || !player->IsValid());
		}

		bool Verify::IsValid(PresetUnit * presetunit)
		{
			return !(presetunit == NULL);
		}

		bool Verify::IsInvalid(PresetUnit * presetunit)
		{
			return (presetunit == NULL);
		}

		bool Verify::IsInvalid(RosterPlayer * player)
		{
			return (player == NULL || !player->IsValid());
		}
}

}