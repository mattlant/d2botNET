#ifndef PLAYER_H
#define PLAYER_H

#include "definitions.h"
#include "ientity.h"

namespace botNET
{
namespace Units
{

	///<summary>
	/// A class used to retreive information on players in the game
	///</summary>
	///<remarks>
	/// RosterPlayer objects and Unit objects are not interchangable. To get a Unit object from a player object, use Unit.Get(RosterPlayer);
	///</remarks>
	__gc public class RosterPlayer : public botNET::Units::IEntity, public botNET::IValid
	{
	public:

		///<summary>
		/// Returns a RosterPlayer array of all players in the current game.
		///</summary>
		///<returns> An array of RosterPlayer objects. </returns>
		static RosterPlayer * Get()[];

		///<summary>
		/// Returns a RosterPlayer object representing the player with the given name.
		///</summary>
		///<param name="Name"> The name of the player to search for. </param>
		///<returns> A RosterPlayer object representing the player with the given name. </returns>
		static RosterPlayer * Get(String * Name);

		///<summary>
		/// Returns a RosterPlayer object representing the player with the given ID.
		///</summary>
		///<param name="UniqueID"> The Unique ID of the player to search for. </param>
		///<returns> A RosterPlayer object representing the player with the given ID. </returns>
		static RosterPlayer * Get(UInt32 UniqueID);

		bool IsValid();

		void IsValidEx();

		///<summary>
		/// Gets the Name of the RosterPlayer.
		///</summary>
		__property String * get_Name(void);

		///<summary>
		/// Gets the ClassID of the RosterPlayer
		///</summary>
		__property int get_ClassID(void);

		__property UnitType get_Type();

		///<summary>
		/// Gets the AreaLevel the RosterPlayer is on.
		///</summary>
		///<remarks>
		/// This property is only valid if the RosterPlayer is in your party.
		///</remarks>
		__property AreaLevel get_Area(void);

		///<summary>
		/// Gets the X coordinate of the RosterPlayer.
		///</summary>
		///<remarks>
		/// This property is only valid if the RosterPlayer is in your party.
		///</remarks>
		__property int get_X(void);

		///<summary>
		/// Gets the Y coordinate of the RosterPlayer.
		///</summary>
		///<remarks>
		/// This property is only valid if the RosterPlayer is in your party.
		///</remarks>
		__property int get_Y(void);

		__property System::Drawing::Point get_Position();

		///<summary>
		/// Gets the Unique ID of the RosterPlayer.
		///</summary>
		__property UInt32 get_UniqueID(void);

		///<summary>
		/// Gets the Unique ID of the RosterPlayer.
		///</summary>
		__property UInt16 get_PartyID(void);

		///<summary>
		/// Gets the Unique ID of the RosterPlayer.
		///</summary>
		__property UInt16 get_CharacterLevel(void);

		///<summary>
		/// Property: true if a Unit is available to provide synchronized player position data; false otherwise.
		///</summary>		
		__property bool RosterPlayer::get_IsSynchronized();
		
		///<summary>
		/// Property: true if the X, Y, and Area properties contain valid values; false otherwise.		
		///</summary>		
		__property bool RosterPlayer::get_IsValidData();


	public private:
		RosterPlayer(Roster * ros);

		DWORD id;
		Roster * r;
	};
}
}

#endif