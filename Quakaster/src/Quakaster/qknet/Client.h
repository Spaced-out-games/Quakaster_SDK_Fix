#pragma once
#include "../Core.h"
#include <enet/enet.h>


namespace qknet
{
	using Channel_ID = enet_uint8;

	__declspec(novtable)
	class QK_API ClientBase
	{
		ENetEvent m_Packet;
		ENetHost* m_Client = nullptr;
		ENetPeer* m_Peer = nullptr;
		ENetAddress m_HostAddress;
		int status = 1;
		uint16_t m_Port;

		public:

			// Construct a client on port 1234
			ClientBase(uint16_t port = 1234);
			
			/// <summary>
			/// Sends a packet over network to the peer
			/// </summary>
			/// <typeparam name="packet_t">The </typeparam>
			/// <param name="packet"></param>
			/// <param name="channel">Which channel (0-255) to send this packet over</param>
			template <class packet_t>
			void send(const T& packet, qknet::Channel_ID channel, enet_uint32 flags = ENET_PACKET_FLAG_RELIABLE)
			{
				if constexpr (std::is_trivially_copyable<packet_t>)
				{
					// it's a trivially copyable type, just memcpy it
					if (!m_Peer) return;
					ENetPacket* net_packet = enet_packet_create(&packet, sizeof(packet_t), flags);
					enet_peer_send(m_Peer, channel, packet);
					enet_host_flush(m_Client);
				}
				else
				{
					static_assert(0, "Implement your own sending logic via template specification. ");

				}

			}

			template <class T>
			void send(const std::vector<T>& packet, qknet::Channel_ID channel, enet_uint32 flags = ENET_PACKET_FLAG_RELIABLE)
			{
				if (!m_Peer) return;

				// Why copy them when a vector is already laid out properly?
				ENetPacket* net_packet = enet_packet_create(packet.data(), sizeof(T) * packet.size(), flags);
				enet_peer_send(m_Peer, channel, net_packet);
				enet_host_flush(m_Client);
			}
	};
}