#ifndef PACKET_H
#define PACKET_H


namespace botNET
{
	namespace Messaging
	{



		[System::Reflection::DefaultMemberAttribute(S"Item")]
		__gc public class Packet : public IEnumerable
		{
		public:
			Packet(int size);
			Packet(BYTE* packet, DWORD length);
			Packet(Byte packet __gc[]);

			//used to help with foreach
			IEnumerator* GetEnumerator();

			//used as indexer
			__property Byte get_Item(int index);

			Byte GetBytes()[];
			Byte GetByte(int index);
			UInt16 GetUInt16(int index);
			UInt32 GetUInt32(int index);
			UInt64 GetUInt64(int index);
			Char GetChar(int index);
			Int16 GetInt16(int index);
			Int32 GetInt32(int index);
			String* GetString(int index);
			String* GetString(int index, int count);
			String* ToString();

			//BNET
			__event static void add_OnBeforeBattleNetReceive(OnPacketHandler* h);
			__event static void remove_OnBeforeBattleNetReceive(OnPacketHandler* h);

			__event static void add_OnAfterBattleNetReceive(OnPacketHandler* h);
			__event static void remove_OnAfterBattleNetReceive(OnPacketHandler* h);

			__event static void add_OnBeforeBattleNetSend(OnPacketHandler* h);
			__event static void remove_OnBeforeBattleNetSend(OnPacketHandler* h);

			__event static void add_OnAfterBattleNetSend(OnPacketHandler* h);
			__event static void remove_OnAfterBattleNetSend(OnPacketHandler* h);

			//REALM
			__event static void add_OnBeforeRealmReceive(OnPacketHandler* h);
			__event static void remove_OnBeforeRealmReceive(OnPacketHandler* h);

			__event static void add_OnAfterRealmReceive(OnPacketHandler* h);
			__event static void remove_OnAfterRealmReceive(OnPacketHandler* h);

			__event static void add_OnBeforeRealmSend(OnPacketHandler* h);
			__event static void remove_OnBeforeRealmSend(OnPacketHandler* h);

			__event static void add_OnAfterRealmSend(OnPacketHandler* h);
			__event static void remove_OnAfterRealmSend(OnPacketHandler* h);

			//GAME
			__event static void add_OnBeforeGameReceive(OnPacketHandler* h);
			__event static void remove_OnBeforeGameReceive(OnPacketHandler* h);

			__event static void add_OnAfterGameReceive(OnPacketHandler* h);
			__event static void remove_OnAfterGameReceive(OnPacketHandler* h);

			__event static void add_OnBeforeGameSend(OnPacketHandler* h);
			__event static void remove_OnBeforeGameSend(OnPacketHandler* h);

			__event static void add_OnAfterGameSend(OnPacketHandler* h);
			__event static void remove_OnAfterGameSend(OnPacketHandler* h);

		private public:
			static OnPacketHandler * OnBeforeBattleNetReceiveInternal;
			static OnPacketHandler * OnAfterBattleNetReceiveInternal;
			static OnPacketHandler * OnBeforeBattleNetSendInternal;
			static OnPacketHandler * OnAfterBattleNetSendInternal;

			static OnPacketHandler * OnBeforeRealmReceiveInternal;
			static OnPacketHandler * OnAfterRealmReceiveInternal;
			static OnPacketHandler * OnBeforeRealmSendInternal;
			static OnPacketHandler * OnAfterRealmSendInternal;

			static OnPacketHandler * OnBeforeGameReceiveInternal;
			static OnPacketHandler * OnAfterGameReceiveInternal;
			static OnPacketHandler * OnBeforeGameSendInternal;
			static OnPacketHandler * OnAfterGameSendInternal;

			__event static void raise_OnBeforeBattleNetReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterBattleNetReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnBeforeBattleNetSend(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterBattleNetSend(Object* sender, PacketEventArgs* e);

			__event static void raise_OnBeforeRealmReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterRealmReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnBeforeRealmSend(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterRealmSend(Object* sender, PacketEventArgs* e);

			__event static void raise_OnBeforeGameReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterGameReceive(Object* sender, PacketEventArgs* e);
			__event static void raise_OnBeforeGameSend(Object* sender, PacketEventArgs* e);
			__event static void raise_OnAfterGameSend(Object* sender, PacketEventArgs* e);

			Byte _packet __gc[];



		};

	}


}

#endif