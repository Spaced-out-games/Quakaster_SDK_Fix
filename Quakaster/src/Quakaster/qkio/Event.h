#pragma once
#include "../Core.h"
#include "EventHeader.h"
#include <string>
#include <stdexcept>


// Makes sure your event type adheres to the IEvent contract
#define QKIO_ASSERT(event_t) \
    static_assert(requires(Event& e) { { event_t::to_string(e) } -> std::same_as<std::string>; }, #event_t " must implement to_string(Event&)"); \
    static_assert(requires(Event& e) { { event_t::is_same_category(e) } -> std::same_as<bool>; }, #event_t " must implement is_same_category(Event&)"); \
    static_assert(requires(Event& e) { { event_t::is_same_type(e) } -> std::same_as<bool>; }, #event_t " must implement is_same_type(Event&)"); \
    static_assert(requires(Event& e) { { event_t::event_cast(e) } -> std::same_as<event_t*>; }, #event_t " must implement event_cast(Event&)");




	namespace qk::io
	{
		class QK_API Event;


		// Contract to enforce that derived types implement some key functions
		template<class event_t>
		concept IEvent = requires(Event & base, event_t & derived)
		{
			{ event_t::to_string(base) } -> std::same_as<std::string>;
			{ event_t::is_same_category(base) } -> std::same_as<bool>;
			{ event_t::is_same_type(base) } -> std::same_as<bool>;
			{ event_t::event_cast(base) } -> std::same_as<event_t*>;
			// { derived.copy() } -> std::same_as<event_t>;
		};
		
		template <IEvent event_t>
		std::string to_string(Event& evt)
		{
			return event_t::to_string(evt);

		}

		template <IEvent event_t>
		bool is_same_category(Event& evt)
		{
			return event_t::is_same_category(evt);
		}
		template <IEvent event_t>
		bool is_same_type(Event& evt)
		{
			return event_t::is_same_type(evt);
		}
		template <IEvent event_t>
		event_t* event_cast(Event& evt)
		{
			return event_t::event_cast(evt);
		}

		







		
		/* Add these to your declarations to abide by the contract. Replace 'event_t' with your event type's name.

			static bool is_same_category(Event& evt);
			static bool is_same_type(Event& evt);
			static std::string to_string(Event& evt);
			static event_t* event_cast(Event& evt);
			operator Event&();
		*/


	


		class QK_API Event
		{
		public:
		
			static std::string to_string(Event& evt);
			static bool is_same_category(Event& evt);
			static bool is_same_type(Event& evt);
			static Event* event_cast(Event& evt);
			operator Event& ();
			protected:
				EventHeader m_Header;
				uint8_t m_Payload[28]{};
				using payload_t = decltype(m_Payload);

				// gives a T& at 'offset' bytes offset in the payload 
				template <class T, size_t offset>
				T& from_payload()
				{
					static_assert(sizeof(T) + offset <= sizeof(m_Payload), "Payload access out of bounds");
					return *reinterpret_cast<T*>(m_Payload + offset);
				}

				// re-casts the event's 'variant' to a T&
				template <class T>
				T& from_variant()
				{
					static_assert(sizeof(T) <= sizeof(EventHeader::variant), "variant access T too ");
					return *reinterpret_cast<T*>(&(m_Header.variant));

				}



			public:
				inline uint16_t& variant_code();
				inline EEventCategory& category();
				inline uint8_t& type_code();

				Event(EEventCategory category, uint8_t type, uint16_t variant = 0) : m_Header{ category, type, variant } {}
				Event() : m_Header{ EEventCategory::NULL_EVENT, 0,0 } {}





			
		};



		//QKIO_ASSERT(Event);


	}