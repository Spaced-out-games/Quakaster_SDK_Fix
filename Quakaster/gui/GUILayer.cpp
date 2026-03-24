#include "GUILayer.h"
#include <GLFW/glfw3.h>


namespace qk::gui {

        io::Layer::EBlock GUILayer::on_event(const Event& evt) {
            ImGuiIO& io = ImGui::GetIO();

            switch (evt.m_Type)
            {

            case EEventType::KeyPress_evt:
            case EEventType::KeyRelease_evt:
            case EEventType::KeyHold_evt:
            {
                const KeyEvent& e = (const KeyEvent&)evt;

                ImGuiKey key = GlfwKeyToImGuiKey(e.key());
                bool down = (evt.m_Type != EEventType::KeyRelease_evt);

                if (key != ImGuiKey_None)
                    io.AddKeyEvent(key, down);

                io.AddKeyEvent(ImGuiKey_ModCtrl, (e.mods() & GLFW_MOD_CONTROL) != 0);
                io.AddKeyEvent(ImGuiKey_ModShift, (e.mods() & GLFW_MOD_SHIFT) != 0);
                io.AddKeyEvent(ImGuiKey_ModAlt, (e.mods() & GLFW_MOD_ALT) != 0);
                io.AddKeyEvent(ImGuiKey_ModSuper, (e.mods() & GLFW_MOD_SUPER) != 0);
                break;
            }


            case EEventType::TextInput_evt:
            {
                const TextInputEvent& e = (const TextInputEvent&)evt;
                io.AddInputCharacter(e.code());
                break;
            }


            case EEventType::MousePress_evt:
            case EEventType::MouseRelease_evt:
            case EEventType::MouseHold_evt:
            {
                const MouseEvent& e = (const MouseEvent&)evt;

                int button = e.button();
                bool down = (evt.m_Type != EEventType::MouseRelease_evt);

                io.AddMouseButtonEvent(button, down);
                break;
            }


            case EEventType::MouseMove_evt:
            {
                const MouseMoveEvent& e = (const MouseMoveEvent&)evt;
                io.AddMousePosEvent(e.x(), e.y());
                break;
            }


            case EEventType::MouseScroll_evt:
            {
                const MouseScrollEvent& e = (const MouseScrollEvent&)evt;
                io.AddMouseWheelEvent(e.dx(), e.dy());
                break;
            }


            case EEventType::WindowResize_evt:
            case EEventType::FramebufferResize_evt:
            {
                const WindowFramebufferResizeEvent& e = (const WindowFramebufferResizeEvent&)evt;
                io.DisplaySize = ImVec2((float)e.width(), (float)e.height());
                break;
            }

            default:
                break;
            }


            if (io.WantCaptureKeyboard || io.WantCaptureMouse)
                return EBlock::Block;

            return EBlock::Pass;
        }

        void GUILayer::on_render() {
            bool b;
            gui::begin_frame();
            gui::demo(&b);
            gui::end_frame();
        }

        void GUILayer::on_attach() {
            if (!m_Window) return;
            gui::mount(m_Window->handle());
            subscribe(EEventCategory::cat_kbmouse | EEventCategory::cat_text);
        }

        void GUILayer::on_detach() {

        }

        GUILayer::GUILayer(core::Window* pWindow) {
            m_Window = pWindow;
        }
}