#pragma once
#include "../UIWidget.h"

struct QK_API DemoWidget : qkui::UIWidget
{
	void draw(qkui::UIContext& owner) override;
	~DemoWidget() override;
};