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
			//qk::status = 1;
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
			// convert to std::string for convenience
			std::string input_string(m_InputBuffer);

			// this will copy input_string but it's actually fine since it's no more than 256 bytes.
			// Plus, we want to preserve these strings even as they go out of scope
			//m_Messages.push_back(ConsoleMessage{ input_string, 0xff0000ff });
			//oss <<
			// run the command
			run(input_string);
			// clear the buffer
			memset(m_InputBuffer, 0, QK_CONSOLE_INPUT_SIZE);


		}

		ImGui::End();


	}

	ConsoleUI::~ConsoleUI()
	{

	}

	void ConsoleUI::clear()
	{
		oss.str("");
	}

	void ConsoleUI::bind_shell(qk::kernel::KShellBase* shell)
	{
		m_Shell = shell;
		shell->clear_impl = [&]() {
			this->clear();
		};
	}


	void ConsoleUI::run(const std::string& command)
	{
		if (m_Shell)
		{
			m_Shell->print_path();
			
			m_Shell->m_Command = command;

			// execute it
			int status = m_Shell->execute();
			m_Shell->m_Command = "";
			// show it
			m_Shell->flush();
		}
	}
}