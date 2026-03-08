#pragma once
#include <stdint.h>
#include "../core.h"

namespace qk {




	// To-do: translate to C-style bitfeild with union with uint32_t for masks.
	enum class EEventCategory : uint32_t {
		cat_null		= 0 << 0,
		cat_os			= 1 << 0,
		cat_file		= 1 << 1,
		cat_memory		= 1 << 2,
		cat_engine		= 1 << 3,
		cat_application = 1 << 4,
		cat_window		= 1 << 5,
		cat_graphics	= 1 << 6,
		cat_sound		= 1 << 7,
		cat_physics		= 1 << 8,
		cat_network		= 1 << 9,
		cat_keyboard	= 1 << 10,
		cat_mouse		= 1 << 11,
		cat_continuous  = 1 << 12,
		cat_error		= 1 << 13,
		cat_custom		= 1u << 31,

		cat_kbmouse = cat_mouse | cat_keyboard,

		cat_input = cat_kbmouse, // for now!
		cat_foundational = cat_os | cat_file | cat_memory,
		cat_media = cat_graphics | cat_sound,
		cat_core = cat_engine | cat_application | cat_window,

		cat_all = 0xFFFFFFFF
	};

	
	inline EEventCategory operator|(EEventCategory a, EEventCategory b) {
		return static_cast<EEventCategory>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
	}

	inline EEventCategory operator&(EEventCategory a, EEventCategory b) {
		return static_cast<EEventCategory>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
	}

	inline bool operator==(EEventCategory a, EEventCategory b) {
		return static_cast<uint32_t>(a) == static_cast<uint32_t>(b);
	}

	inline bool operator!=(EEventCategory a, EEventCategory b) {
		return static_cast<uint32_t>(a) != static_cast<uint32_t>(b);
	}
	inline bool operator!(EEventCategory cat) {
		return cat == EEventCategory::cat_null;
	}

	inline EEventCategory& operator|=(EEventCategory& a, EEventCategory b) {
		a = a | b;
		return a;
	}

	inline EEventCategory& operator&=(EEventCategory& a, EEventCategory b) {
		a = a & b;
		return a;
	}

	inline EEventCategory operator~(EEventCategory a) {
		return static_cast<EEventCategory>(~static_cast<uint32_t>(a));
	}

	
	enum class EEventType : uint32_t {
		Null_evt, // Primarily for default construction
		KeyPress_evt,
		KeyHold_evt,
		KeyRelease_evt,

		MousePress_evt,
		MouseMove_evt,
		MouseEnter_evt,
		MouseExit_evt,
		MouseScroll_evt,

		WindowResize_evt,
		WindowGainFocus_evt,
		WindowLoseFocus_evt,
		WindowOpen_evt,
		WindowClose_evt,
		WindowRefresh_evt,
		WindowMinimize_evt,
		WindowMaximize_evt,

		FramebufferResize_evt,
		WindowDPIUpdate_evt,
		TextInput_evt,
		TextInputEx_evt,
		DragDrop_evt,
		JoystickConnect_evt,
		JoystickDisconnect_evt,
		MonitorConnect_evt,
		MonitorDisconnect_evt,

		PlatformUninitialized_err,
		PlatformNoContext_err,
		PlatformInvalidValue_err,
		PlatformOutOfMemory_err,
		PlatformInterfaceUnavailable_err,
		PlatformVersionUnavailable_err,
		PlatformDriver_err,
		PlatformFormat_err,
		PlatformMouseCursorUnavailable_err



	};

	static constexpr uint32_t CUSTOM_EVENT_BEGIN = 1u << 31;

	

	struct Event {
		// Denotes the type ID that begins the first custom event
		// If you create your own custom events and an enum on top
		static constexpr uint32_t custom_begin = 1u << 31;
		Event() = default;
		~Event();

		EEventCategory m_Category = {};
		EEventType m_Type = {};
		uint64_t timestamp = 0;
		// starts at 128 bit boundary
		uint8_t m_Payload[16];


	};

	using EventEx_dtor_pfn_t = void(*)(Event&);

	void QK_API SetEventExDtor_fn(EventEx_dtor_pfn_t dtor);




}