#pragma once
#include "../UIWidget.h"
#include "../../Core.h"
#include <string>
#include "../../qkkernel/KShellBase.h"
#include <sstream>
#define QK_CONSOLE_INPUT_SIZE 256




namespace qk::ui
{


	struct ConsoleMessage {
		ConsoleMessage(std::string contents, ImU32 color);
		std::string contents;
		ImU32 color;
	};



	struct QK_API ConsoleUI : qk::ui::UIWidget, qk::kernel::KShellBase
	{
		std::ostringstream oss;
		//qk::kernel::KShellBase* m_Shell = nullptr;
		char m_InputBuffer[QK_CONSOLE_INPUT_SIZE]{};
		bool m_JustOpened = true;
		void draw(qk::ui::UIContext& owner) override;
		ConsoleUI();
		~ConsoleUI() override;
		//std::vector<ConsoleMessage> m_Messages;
		inline void run();

		// Awaits a command, assigns m_Command
		void get_line() override;

		void flush() override;

		// Can be overridden by the console.
		void clear() override;
	};

}