#ifndef MESSAGINGENUMERATIONS_H
#define MESSAGINGENUMERATIONS_H

namespace botNET
{

	namespace Messaging
	{
		__value	public enum	SystemMessageType
		{
			JoinGame = 2,
			LeaveGame =	3,
			Party =	7,
			SOJCount = 0x11,
			Walks =	0x12,
		};

		__value	public enum	BattleNetMessageType
		{
			ShowUser = 0x01,
			Join = 0x02,
			Leave =	0x03,
			Whisper	= 0x04,
			Talk = 0x05,
			Broadcast =	0x06,
			ChannelInfo	= 0x07,
			UserFlags =	0x09,
			WhisperSent	= 0x0A,
			ChannelFull	= 0x0D,
			ChannelDoesNotExist	= 0x0E,
			ChannelRestricted =	0x0F,
			Info = 0x12,
			Error =	0x13,
			Emote =	0x17
		};

		__value	public enum	ChatType
		{
			Unk0 = 0,
			Normal = 1,
			Whisper	= 2,
			Unk3 = 3,
			Unk4 = 4,
			Overhead = 5
		};

		__value	public enum	ChatOrigin
		{
			Game = 0,
			BattleNet = 1,
			ChatLine = 2
		};

		__value	public enum	PartyMessageType
		{
			Unk0 = 0,
			Unk1 = 1,
			Unk2 = 2,
			Hostile	= 3,
			Unhostile =	4,
			JoinRequest	= 5,
			InvitationCancelled = 6,
			PlayerAcceptParty =	7,
			AcceptedJoinRequest	= 8,
			PlayerLeaveParty = 9
		};

		__value	public enum	PacketOrigin
		{
			BeforeRealmReceive = 0,
			AfterRealmReceive = 1,
			BeforeBattleNetReceive = 2,
			AfterBattleNetReceive = 3,
			BeforeGameReceive = 4,
			AfterGameReceive = 5,

			BeforeRealmSend = 6,
			AfterRealmSend = 7,
			BeforeBattleNetSend = 8,
			AfterBattleNetSend = 9,
			BeforeGameSend = 10,
			AfterGameSend = 11
		};

		__value	public enum	MessageType
		{
			PartyMessage = 0,
			SystemMessage = 1,
			ChatMessage = 2,
			ChatLineMessage = 3
		};
	}

}

#endif
