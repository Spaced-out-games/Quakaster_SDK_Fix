#include "UIContext.h"


namespace qkui
{
	class qkg::GraphicsPipeline;

	UIContext::UIContext()
	{
		m_Target = nullptr;
		m_Context = nullptr;
	}
	void UIContext::init(SDL_GLContext context, SDL_Window* window)
	{
		m_Target = window;
		IMGUI_CHECKVERSION();
		m_Context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplSDL2_InitForOpenGL(m_Target, context);
		ImGui_ImplOpenGL3_Init("#version 330");
	}
	void UIContext::init(qkg::GraphicsPipeline& pipeline, qkg::Window& window)
	{
		init(pipeline.m_GLContext, window.m_Window);

	}

	ImGuiIO& UIContext::IO() { return ImGui::GetIO(); }

	void UIContext::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}


	void UIContext::draw()
	{
		for (UIWidget* widget : m_Widgets)
		{
			if(widget) widget->draw(*this);
		}
		ImGui::Render();
	}


	void UIContext::end()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}



	[[nodiscard]] uint8_t UIContext::add_widget(UIWidget* widget)
	{
		// if we have no empty slots, just append the vector
		if (!m_EmptyCount)
		{
			uint8_t handle = m_Widgets.size();
			m_Widgets.push_back(widget);
			return handle;
		}
		// otherwise, we gotta look for the first empty space
		for (uint8_t i = 0; i < m_Widgets.size(); i++)
		{
			// found an empty slot
			if (m_Widgets[i] == nullptr)
			{
				m_Widgets[i] = widget;
				m_EmptyCount--;
				return i;
			}
		}
		return UINT8_MAX;
	}

	inline bool UIContext::remove_widget(uint8_t handle)
	{
		// make sure it's in range, exit if not
		if (handle >= m_Widgets.size()) return false;
		if (m_Widgets[handle] == nullptr) return false;

		// call the virtual destructor
		delete m_Widgets[handle];

		// mark empty
		m_Widgets[handle] = nullptr;
		
		// also, keep track of how many empty slots we have
		m_EmptyCount++;

		return true;

	}

	UIContext::~UIContext()
	{

	}

}