#include "DemoWidget.h"

void DemoWidget::draw(qk::ui::UIContext& owner)
{
	ImGui::Begin("Example Window");
	ImGui::Text("Hello, world!");
	ImGui::End();
}
DemoWidget::~DemoWidget()
{
	// nothing needed
}