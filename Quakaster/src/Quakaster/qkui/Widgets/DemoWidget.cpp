#include "DemoWidget.h"

void DemoWidget::draw(qkui::UIContext& owner)
{
	ImGui::Begin("Example Window");
	ImGui::Text("Hello, world!");
	ImGui::End();
}
DemoWidget::~DemoWidget()
{
	// nothing needed
}