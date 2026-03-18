/// **************************************** QUAKASTER ENGINE **************************************** 
/// gui/gui.h
/// Purpose: Defines wrapper functions for ImGui calls (for DLL boundary reasons) 
/// **************************************************************************************************
#pragma once
#include "../core.h"
#include "imgui/imgui.h"



namespace qk::gui {

	void QK_API mount(void* window);
	void QK_API dismount();

	void QK_API separator();
	void QK_API same_line(float offset_from_start_x = 0.0f, float spacing = -1.0f);
	void QK_API new_line();
	void QK_API spacing();
	void QK_API dummy(const ImVec2& size);
	void QK_API indent(float indent_w = 0.0f);
	void QK_API unindent(float indent_w = 0.0f);
	void QK_API begin_group();
	void QK_API end_group();

	void QK_API begin_frame();
	void QK_API end_frame();

	bool QK_API begin_child(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
	void QK_API end_child();

	bool QK_API begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
	void QK_API end();


	void QK_API push_style_color(ImGuiCol idx, ImU32 col);
	void QK_API push_style_color(ImGuiCol idx, const ImVec4& col);
	void QK_API pop_style_color(int count = 1);

	void QK_API push_style_var(ImGuiStyleVar idx, float val);
	void QK_API push_style_var(ImGuiStyleVar idx, const ImVec2& val);
	void QK_API pop_style_var(int count = 1);

	void QK_API push_id(const char* str_id);
	void QK_API push_id(const void* ptr_id);
	void QK_API push_id(int int_id);
	void QK_API pop_id();

	void QK_API text(const char* fmt, ...);
	void QK_API text_colored(const ImVec4& col, const char* fmt, ...);
	void QK_API text_wrapped(const char* fmt, ...);
	void QK_API label_text(const char* label, const char* fmt, ...);

	bool QK_API button(const char* label, const ImVec2& size = ImVec2(0, 0));
	bool QK_API small_button(const char* label);
	bool QK_API checkbox(const char* label, bool* v);
	bool QK_API radio_button(const char* label, bool active);
	bool QK_API radio_button(const char* label, int* v, int v_button);
	bool QK_API selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
	void QK_API progress_bar(float fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0), const char* overlay = NULL);

	bool QK_API begin_combo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
	void QK_API end_combo();
	bool QK_API combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);

	bool QK_API input_text(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	bool QK_API input_float(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
	bool QK_API input_int(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);

	bool QK_API slider_float(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool QK_API slider_int(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);

	bool QK_API drag_float(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool QK_API drag_int(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);

	bool QK_API tree_node(const char* label);
	bool QK_API tree_node_ex(const char* label, ImGuiTreeNodeFlags flags = 0);
	void QK_API tree_pop();
	bool QK_API collapsing_header(const char* label, ImGuiTreeNodeFlags flags = 0);

	bool QK_API begin_popup(const char* str_id, ImGuiWindowFlags flags = 0);
	bool QK_API begin_popup_modal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
	void QK_API end_popup();
	void QK_API open_popup(const char* str_id, ImGuiPopupFlags popup_flags = 0);
	void QK_API close_current_popup();

	bool QK_API begin_tab_bar(const char* str_id, ImGuiTabBarFlags flags = 0);
	void QK_API end_tab_bar();
	bool QK_API begin_tab_item(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0);
	void QK_API end_tab_item();

	bool QK_API begin_main_menu_bar();
	void QK_API end_main_menu_bar();
	bool QK_API begin_menu(const char* label, bool enabled = true);
	void QK_API end_menu();
	bool QK_API menu_item(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);

	bool QK_API begin_table(const char* str_id, int columns, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f);
	void QK_API end_table();
	void QK_API table_next_row(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f);
	bool QK_API table_next_column();
	void QK_API table_setup_column(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
	void QK_API table_headers_row();

	bool QK_API begin_tooltip();
	void QK_API end_tooltip();
	void QK_API set_tooltip(const char* fmt, ...);

	QK_API ImDrawList* get_window_draw_list();
	QK_API ImDrawList* get_background_draw_list();
	QK_API ImDrawList* get_foreground_draw_list();

}
