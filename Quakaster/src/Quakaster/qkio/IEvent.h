#pragma once
#include "../Core.h"
#include "EventHeader.h"
#include "EEventCategory.h"
#include "EEventType.h"
#include <string>


#define QK_EVENT_SIZE 32

namespace qk::io
{


	alignas(QK_EVENT_SIZE) struct QK_API IEvent
	{

		// void* is for the vptr
		static constexpr size_t payload_size = QK_EVENT_SIZE - (sizeof(void*) + sizeof(EventHeader));
		EventHeader				m_Header;
		uint8_t					m_Payload[payload_size];


		virtual std::string		to_string() = 0;

		uint64_t hash()
		{
			// ccccccccccccccccttttttttttttttttvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			uint64_t result = 0;
			result |= (uint64_t)category()	<< 48;
			result |= (uint64_t)type()		<< 32;
			result |= (uint64_t)m_Variant;


			return result;
		}


		template <class T>
		T& variant()
		{
			return *reinterpret_cast<T*>(&m_Variant);
		}

		template <class T, size_t offset>
		T& payload()
		{
			static_assert(sizeof(T) + offset <= sizeof(m_Payload), "Payload access out of bounds");
			return *reinterpret_cast<T*>(m_Payload + offset);
		}
		IEvent(const EEventCategory category, const EEventType type, const uint32_t variant);
	};


	static_assert(sizeof(IEvent) == QK_EVENT_SIZE);
}