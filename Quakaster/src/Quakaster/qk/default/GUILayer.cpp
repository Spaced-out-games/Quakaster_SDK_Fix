#include "GUILayer.h"
#include <sstream>

namespace qk
{

    GUILayer::GUILayer(qkui::UIContext* UIContext) : m_UIContext(UIContext)
    {
        if (!UIContext)
        {
            // exit the application
            __debugbreak();

        }
        if (!UIContext->m_Context)
        {
            __debugbreak();

        }

        ImGui::SetCurrentContext(UIContext->m_Context);

    }

    void GUILayer::on_attach()
    {

    }

    bool GUILayer::on_event(const SDL_Event& evt)
    {
        ImGui_ImplSDL2_ProcessEvent(&evt); // always feed ImGui

        ImGuiIO& io = ImGui::GetIO();

        //return ImGui::IsAnyItemActive() && io.WantCaptureKeyboard;

        switch (evt.type)
        {
        case SDL_MOUSEBUTTONDOWN:

        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
            return ImGui::IsAnyItemActive() && io.WantCaptureMouse;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        case SDL_TEXTINPUT:
            return ImGui::IsAnyItemActive() && io.WantCaptureKeyboard;

        default:
            return false;
        }

    }

    void GUILayer::on_detach()
    {
        // TODO
    }

    void GUILayer::render()
    {
        m_UIContext->begin();
        m_UIContext->draw();
        m_UIContext->end();
    }

}