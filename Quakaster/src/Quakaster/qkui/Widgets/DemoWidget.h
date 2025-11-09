#pragma once
#include "../UIWidget.h"

struct QK_API DemoWidget : qk::ui::UIWidget
{
	void draw(qk::ui::UIContext& owner) override;
	~DemoWidget() override;
};