#include "ConsoleUI.h"



namespace qk::ui
{

	ConsoleMessage::ConsoleMessage(std::string contents, ImU32 color = 0xffffffff) : contents(contents), color(color)
	{

	}



	void ConsoleUI::draw(qk::ui::UIContext& owner)
	{
		ImGui::SetNextWindowSize({ 720, 720 }, false);

		const ImVec2 buttonSize = { 120, 20 };

		if (!ImGui::Begin("Integrated Console"))
		{
			ImGui::End();
			return;
		}
		else
		{
			// respond to failure
		}

		// clear button
		if (ImGui::Button("Clear")) clear();

		// copy button
		ImGui::SameLine();
		bool line_copied = ImGui::Button("Copy");


		// exit button
		ImGui::SameLine();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::SetCursorPosX(windowSize.x - buttonSize.x - 10);
		if (ImGui::Button("Exit Application")) {
			m_Command = "exit";
			run();
		}

		// history / output
		ImGui::Separator();

		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetTextLineHeightWithSpacing() * 2), false, ImGuiWindowFlags_HorizontalScrollbar);

		// placed here so it clips the right text
		if (line_copied)
			ImGui::LogToClipboard();


		ImGui::TextUnformatted(oss.str().c_str());

		ImGui::EndChild();

		// focus the text box when the console opens up
		if (m_JustOpened)
		{
			ImGui::SetKeyboardFocusHere();
			m_JustOpened = false;
		}

		// draw the text box

		if (ImGui::InputText("Input", m_InputBuffer, QK_CONSOLE_INPUT_SIZE, ImGuiInputTextFlags_EnterReturnsTrue))
		{

			m_Command = std::string(m_InputBuffer);
			print(m_Command);
			print("\n");
			run();
			memset(m_InputBuffer, 0, QK_CONSOLE_INPUT_SIZE);


		}

		ImGui::End();


	}

	ConsoleUI::ConsoleUI()
	{

	}

	ConsoleUI::~ConsoleUI()
	{

	}

	void ConsoleUI::clear()
	{
		oss.str("");
	}




	void ConsoleUI::flush()
	{

	}

	void ConsoleUI::run()
	{


		print_path();
			

		// execute it
		int status = execute();
		m_Command = "";
		// show it
		flush();
		// clear the buffer
	}

	void ConsoleUI::get_line()
	{

	}

}