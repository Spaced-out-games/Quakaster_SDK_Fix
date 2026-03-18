/// **************************************** QUAKASTER ENGINE **************************************** 
/// core/io/DefaultEvents.h
/// Purpose: Declares event views for easy Event manipulation
/// ************************************************************************************************** 
#pragma once
#include "Event.h"
#include <string>
#include <format>

namespace qk::io {

	struct NullEvent : Event {};

	struct KeyEvent : Event {
		inline int& key() {
			return view<int>(0);
		}
		inline int& scancode() {
			return view<int>(sizeof(int));
		}

		inline int& mods() {
			return view<int>(sizeof(int) * 2);

		}
	};
	// helper wrapper types. 

	struct KeyPressEvent : KeyEvent {};
	struct KeyReleaseEvent : KeyEvent {};
	struct KeyHoldEvent : KeyEvent {};

	struct MouseEvent : Event {
		inline int& button() { return view<int>(0);}
		inline int& mods() { return view<int>(sizeof(int)); }
	};

	struct MousePressEvent: MouseEvent {};
	struct MouseReleaseEvent : MouseEvent {};
	struct MouseHoldEvent : MouseEvent {};




	struct MouseMoveEvent : Event {
		inline float& x() { return view<float>(0); }
		inline float& y() { return view<float>(sizeof(float)); }
	};

	struct MouseEnterEvent : Event {};

	struct MouseExitEvent : Event {};

	struct MouseScrollEvent : Event {
		inline float& dx() { return view<float>(0); }
		inline float& dy() { return view<float>(sizeof(float)); }
	};

	struct WindowResizeEvent : Event {
		inline int& width() { return view<int>(0); }
		inline int& height() { return view<int>(sizeof(int)); }
	};

	struct WindowCloseEvent : Event {};

	struct WindowRefreshEvent: Event {};

	struct WindowGainFocusEvent : Event {};

	struct WindowLoseFocusEvent : Event {};

	struct WindowMinimizeEvent : Event {};

	struct WindowMinimizeRestoreEvent : Event {};

	struct WindowMaximizeEvent: Event {};

	struct WindowMaximizeRestoreEvent : Event {};

	struct WindowFramebufferResizeEvent : Event {
		inline int& width() { return view<int>(0); }
		inline int& height() { return view<int>(sizeof(int)); }
	};

	struct WindowDPIUpdateEvent : Event {
		inline float& xscale() { return view<float>(0); }
		inline float& yscale() { return view<float>(sizeof(float)); }
	};

	struct TextInputEvent : Event {
		inline unsigned int& code() { return view<unsigned int>(0); }
	};

	struct TextInputEventEx : Event {
		inline int& code() { return view<int>(0); }
		inline int& mod() { return view<int>(sizeof(int)); }
	};

	struct DragDropEvent : Event {
		inline int& count() { return view<int>(0); }
		char*& paths() { return view<char*>(sizeof(int)); }
		char* paths(size_t i) { return paths() + (QK_MAX_STRING_SIZE * i); }
	};

	struct JoystickConnectEvent : Event {
		inline int& jid() { return view<int>(0); }
	};

	struct JoystickDisconnectEvent : Event {
		inline int& jid() { return view<int>(0); }
	};
	struct MonitorConnectEvent : Event {};

	struct MonitorDisconnectEvent: Event {};

	struct Error : Event {
		inline char*& description() {
			return view<char*>(0);
		}
	};

	struct PlatformUninitializedError : Error {};
	
	struct PlatformNoContextError : Error {};
	
	struct PlatformOutOfMemoryError: Error {};
	
	struct PlatformInterfaceUnavailableError: Error {};
	
	struct PlatformVersionUnavailableError: Error {};
	
	struct PlatformDriverError: Error {};
	
	struct PlatformFormatError: Error {};
	
	struct PlatformMouseCursorUnavailableError: Error {};

	// Function pointer type to convert custom events to string representations
	using EventExToString_pfn_t = std::string(*)(const Event&);

	// Function pointer to convert custom event to string representation
	inline EventExToString_pfn_t g_EventExToString_pfn = nullptr;

	// Converts any Event to a string
	std::string to_string(const Event& evt) {
		using enum EEventType;
		Event& e = const_cast<Event&>(evt);

		if ((uint32_t)e.m_Type >= CUSTOM_EVENT_BEGIN)
		{
			if (g_EventExToString_pfn)
			{
				std::string s = g_EventExToString_pfn(evt);
				if (!s.empty())
					return s;
			}

			return std::format("Custom Event #{}", (uint32_t)(evt.m_Type) - CUSTOM_EVENT_BEGIN);
		}


		switch (e.m_Type)
		{
			case Null_evt: return "NullEvent";
			case KeyPress_evt:
			{
				auto& ev = (KeyPressEvent&)e;
				return std::format("KeyPressEvent {{ key={}, scancode={}, mods={} }}", ev.key(), ev.scancode(), ev.mods());
			}
			case KeyRelease_evt:
			{
				auto& ev = (KeyReleaseEvent&)e;
				return std::format("KeyReleaseEvent {{ key={}, scancode={}, mods={} }}", ev.key(), ev.scancode(), ev.mods());
			}
			case KeyHold_evt:
			{
				auto& ev = (KeyHoldEvent&)e;
				return std::format("KeyHoldEvent {{ key={}, scancode={}, mods={} }}", ev.key(), ev.scancode(), ev.mods());
			}
			case MousePress_evt:
			{
				auto& ev = (MousePressEvent&)e;
				return std::format("MousePressEvent {{ btn={}, mods={} }}", ev.button(), ev.mods());
			}
			case MouseHold_evt:
			{
				auto& ev = (MouseHoldEvent&)e;
				return std::format("MouseHoldEvent {{ btn={}, mods={} }}", ev.button(), ev.mods());
			}
			case MouseRelease_evt:
			{
				auto& ev = (MouseReleaseEvent&)e;
				return std::format("MouseReleaseEvent {{ btn={}, mods={} }}", ev.button(), ev.mods());
			}
			case MouseMove_evt:
			{
				auto& ev = (MouseMoveEvent&)e;
				return std::format("MouseMoveEvent {{ {}, {} }}", ev.x(), ev.y());
			}
			case MouseScroll_evt:
			{
				auto& ev = (MouseScrollEvent&)e;
				return std::format("MouseScrollEvent {{ {}, {} }}", ev.dx(), ev.dy());
			}
			case MouseEnter_evt: return "MouseEnterEvent";
			case MouseExit_evt: return "MouseExitEvent";
			case WindowResize_evt:
			{
				auto& ev = (WindowResizeEvent&)e;
				return std::format("WindowResizeEvent {{ {}, {} }}", ev.width(), ev.height());
			}
			case FramebufferResize_evt:
			{
				auto& ev = (WindowFramebufferResizeEvent&)e;
				return std::format("FramebufferResizeEvent {{ {}, {} }}", ev.width(), ev.height());
			}
			case WindowDPIUpdate_evt:
			{
				auto& ev = (WindowDPIUpdateEvent&)e;
				return std::format("WindowDPIUpdateEvent {{ {}, {} }}", ev.xscale(), ev.yscale());
			}
			case DragDrop_evt:
			{
				auto& ev = (DragDropEvent&)e;
				std::string s = std::format("DragDropEvent count={} paths: {{\n", ev.count());
				for (int i = 0; i < ev.count(); ++i) s += std::format("\t\"{}\"\n", ev.paths(i));
				s += "}";
				return s;
			}
			case JoystickConnect_evt:
			{
				auto& ev = (JoystickConnectEvent&)e;
				return std::format("JoystickConnectEvent jid={}", ev.jid());
			}
			case JoystickDisconnect_evt:
			{
				auto& ev = (JoystickDisconnectEvent&)e;
				return std::format("JoystickDisconnectEvent jid={}", ev.jid());
			}
			case MonitorConnect_evt: return "MonitorConnectEvent";
			case MonitorDisconnect_evt: return "MonitorDisconnectEvent";
			case PlatformUninitialized_err:
			case PlatformNoContext_err:
			case PlatformInvalidValue_err:
			case PlatformOutOfMemory_err:
			case PlatformInterfaceUnavailable_err:
			case PlatformVersionUnavailable_err:
			case PlatformDriver_err:
			case PlatformFormat_err:
			case PlatformMouseCursorUnavailable_err:
			{
				auto& ev = (Error&)e;
				if (ev.description()) return std::format("PlatformError: {}", ev.description());
				return "PlatformError";
			}
			default:
				return std::format("Unknown Event ({})", static_cast<uint32_t>(evt.m_Type));
		}
	}


}