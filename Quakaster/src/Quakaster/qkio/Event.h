#pragma once
#include "../Core.h"
#include "EventHeader.h"
#include <string>
#include <stdexcept>


namespace qk::io
{
	class QK_API Event;




	class QK_API Event
	{
	public:
		


		protected:
			EventHeader m_Header;
			uint8_t m_Payload[12]{};
			static constexpr size_t variant_size = sizeof(decltype(m_Header.variant));
			using payload_t = decltype(m_Payload);

			template <class T, size_t offset>
			T& from_payload()
			{
				static_assert(sizeof(T) + offset <= sizeof(m_Payload), "Payload access out of bounds");
				return *reinterpret_cast<T*>(m_Payload + offset);
			}

			template <class T>
			T& from_variant()
			{
				static_assert(sizeof(T) <= variant_size, "variant access T too ");
				return *reinterpret_cast<T*>(&(m_Header.variant));

			}



		public:
			const EventHeader& header() const { return m_Header; }

			inline const EEventCategory category() const;
			static Event* try_cast_impl(Event& evt);
			static bool is_impl(Event& evt);
			static std::string to_string_impl(Event& evt);
			inline const uint8_t type();

			Event(EEventCategory category, uint8_t type, uint16_t variant = 0) : m_Header{ category, type, variant } {}
			Event() : m_Header{ EEventCategory::NULL_EVENT, 0,0 } {}

			

			// Attempts to upcast to an evt_t
			template<class evt_t>
			evt_t* try_cast() {
				return evt_t::try_cast_impl(*this);
			}

			template <class evt_t>
			std::string to_string()
			{
				return evt_t::to_string_impl(*this);
			}

			template <class evt_t>
			bool is()
			{
				return evt_t::is_impl(*this);
			}





			
	};


}