#pragma once
#include "../UIWidget.h"

#define QK_CONSOLE_INPUT_SIZE 256

struct ConsoleMessage {
	ConsoleMessage(std::string contents, ImU32 color);
	std::string contents;
	ImU32 color;
};



struct QK_API ConsoleUI : qkui::UIWidget
{
	char m_InputBuffer[QK_CONSOLE_INPUT_SIZE]{};
	bool m_JustOpened = true;
	void draw(qkui::UIContext& owner) override;
	~ConsoleUI() override;
	std::vector<ConsoleMessage> m_Messages;
	inline void clear();
	inline void run(const std::string& command);
};