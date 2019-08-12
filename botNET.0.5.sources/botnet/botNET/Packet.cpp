#include "botnet.h"
#include "packetparsing.h"
#include "packet.h"

#include "game.h"

namespace botNET
{
	namespace Messaging
	{

		Packet::Packet(int size)
		{
			this->_packet = new Byte[size];
		}

		Packet::Packet(BYTE* packet, DWORD length)
		{
			this->_packet = new Byte[length];
			Marshal::Copy(packet, this->_packet, 0, length);
		}

		Packet::Packet(Byte packet __gc[])
		{
			this->_packet = new Byte[packet->Length];
			packet->CopyTo(_packet, 0);
		}

		System::Collections::IEnumerator* Packet::GetEnumerator()
		{
			return this->_packet->GetEnumerator();
		}

		Byte Packet::get_Item(int index)
		{
			return this->_packet[index];
		}

		Byte Packet::GetBytes()[]
		{
			return this->_packet;
		}

		Byte Packet::GetByte(int index)
		{
			return this->_packet[index];
		}

		UInt16 Packet::GetUInt16(int index)
		{
			return BitConverter::ToUInt16(this->_packet, index);
		}

		UInt32 Packet::GetUInt32(int index)
		{
			return BitConverter::ToUInt32(this->_packet, index);
		}

		UInt64 Packet::GetUInt64(int index)
		{
			return BitConverter::ToUInt64(this->_packet, index);
		}

		Char Packet::GetChar(int index)
		{
			return BitConverter::ToChar(this->_packet, index);
		}

		Int16 Packet::GetInt16(int index)
		{
			return BitConverter::ToInt16(this->_packet, index);
		}

		Int32 Packet::GetInt32(int index)
		{
			return BitConverter::ToInt32(this->_packet, index);
		}

		String* Packet::GetString(int index)
		{
			return System::Text::Encoding::ASCII->GetString(this->_packet, index, this->_packet->Length - index);
		}

		String* Packet::GetString(int index, int count)
		{
			return System::Text::Encoding::ASCII->GetString(this->_packet, index, count);
		}

		String* Packet::ToString()
		{
			return BitConverter::ToString(this->_packet);
		}

		//BNET RECV
		void Packet::add_OnBeforeBattleNetReceive(OnPacketHandler* h)
		{
			OnBeforeBattleNetReceiveInternal += h;
		}

		void Packet::remove_OnBeforeBattleNetReceive(OnPacketHandler* h)
		{
			OnBeforeBattleNetReceiveInternal -= h;
		}

		void Packet::raise_OnBeforeBattleNetReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeBattleNetReceiveInternal)
				OnBeforeBattleNetReceiveInternal(sender, e);
		}

		void Packet::add_OnAfterBattleNetReceive(OnPacketHandler* h)
		{
			OnAfterBattleNetReceiveInternal += h;
		}

		void Packet::remove_OnAfterBattleNetReceive(OnPacketHandler* h)
		{
			OnAfterBattleNetReceiveInternal -= h;
		}

		void Packet::raise_OnAfterBattleNetReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterBattleNetReceiveInternal)
				OnAfterBattleNetReceiveInternal(sender, e);
		}

		//BNET SEND
		void Packet::add_OnBeforeBattleNetSend(OnPacketHandler* h)
		{
			OnBeforeBattleNetSendInternal += h;
		}

		void Packet::remove_OnBeforeBattleNetSend(OnPacketHandler* h)
		{
			OnBeforeBattleNetSendInternal -= h;
		}

		void Packet::raise_OnBeforeBattleNetSend(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeBattleNetSendInternal)
				OnBeforeBattleNetSendInternal(sender, e);
		}

		void Packet::add_OnAfterBattleNetSend(OnPacketHandler* h)
		{
			OnAfterBattleNetSendInternal += h;
		}

		void Packet::remove_OnAfterBattleNetSend(OnPacketHandler* h)
		{
			OnAfterBattleNetSendInternal -= h;
		}

		void Packet::raise_OnAfterBattleNetSend(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterBattleNetSendInternal)
				OnAfterBattleNetSendInternal(sender, e);
		}

		//REALM RECV
		void Packet::add_OnBeforeRealmReceive(OnPacketHandler* h)
		{
			OnBeforeRealmReceiveInternal += h;
		}

		void Packet::remove_OnBeforeRealmReceive(OnPacketHandler* h)
		{
			OnBeforeRealmReceiveInternal -= h;
		}

		void Packet::raise_OnBeforeRealmReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeRealmReceiveInternal)
				OnBeforeRealmReceiveInternal(sender, e);
		}

		void Packet::add_OnAfterRealmReceive(OnPacketHandler* h)
		{
			OnAfterRealmReceiveInternal += h;
		}

		void Packet::remove_OnAfterRealmReceive(OnPacketHandler* h)
		{
			OnAfterRealmReceiveInternal -= h;
		}

		void Packet::raise_OnAfterRealmReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterRealmReceiveInternal)
				OnAfterRealmReceiveInternal(sender, e);
		}

		//REALM SEND
		void Packet::add_OnBeforeRealmSend(OnPacketHandler* h)
		{
			OnBeforeRealmSendInternal += h;
		}

		void Packet::remove_OnBeforeRealmSend(OnPacketHandler* h)
		{
			OnBeforeRealmSendInternal -= h;
		}

		void Packet::raise_OnBeforeRealmSend(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeRealmSendInternal)
				OnBeforeRealmSendInternal(sender, e);
		}

		void Packet::add_OnAfterRealmSend(OnPacketHandler* h)
		{
			OnAfterRealmSendInternal += h;
		}

		void Packet::remove_OnAfterRealmSend(OnPacketHandler* h)
		{
			OnAfterRealmSendInternal -= h;
		}

		void Packet::raise_OnAfterRealmSend(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterRealmSendInternal)
				OnAfterRealmSendInternal(sender, e);
		}

		//GAME RECV
		void Packet::add_OnBeforeGameReceive(OnPacketHandler* h)
		{
			OnBeforeGameReceiveInternal += h;
		}

		void Packet::remove_OnBeforeGameReceive(OnPacketHandler* h)
		{
			OnBeforeGameReceiveInternal -= h;
		}

		void Packet::raise_OnBeforeGameReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeGameReceiveInternal)
				OnBeforeGameReceiveInternal(sender, e);
		}

		void Packet::add_OnAfterGameReceive(OnPacketHandler* h)
		{
			OnAfterGameReceiveInternal += h;
		}

		void Packet::remove_OnAfterGameReceive(OnPacketHandler* h)
		{
			OnAfterGameReceiveInternal -= h;
		}

		void Packet::raise_OnAfterGameReceive(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterGameReceiveInternal)
				OnAfterGameReceiveInternal(sender, e);
		}

		//GAME SEND
		void Packet::add_OnBeforeGameSend(OnPacketHandler* h)
		{
			OnBeforeGameSendInternal += h;
		}

		void Packet::remove_OnBeforeGameSend(OnPacketHandler* h)
		{
			OnBeforeGameSendInternal -= h;
		}

		void Packet::raise_OnBeforeGameSend(Object* sender, PacketEventArgs* e)
		{
			if(OnBeforeGameSendInternal)
				OnBeforeGameSendInternal(sender, e);
		}

		void Packet::add_OnAfterGameSend(OnPacketHandler* h)
		{
			OnAfterGameSendInternal += h;
		}

		void Packet::remove_OnAfterGameSend(OnPacketHandler* h)
		{
			OnAfterGameSendInternal -= h;
		}

		void Packet::raise_OnAfterGameSend(Object* sender, PacketEventArgs* e)
		{
			if(OnAfterGameSendInternal)
				OnAfterGameSendInternal(sender, e);
		}

	}
}

