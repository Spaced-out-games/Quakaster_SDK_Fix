#include "gui.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace qk::gui {

    // In a real implementation, just use qk::Window&
    void mount(void* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, false);
        ImGui_ImplOpenGL3_Init("#version 330");
    }




    void begin_frame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


    }

    void end_frame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool begin(const char* name, bool* p_open, ImGuiWindowFlags flags)
    {
        return ImGui::Begin(name, p_open, flags);
    }

    void end()
    {
        ImGui::End();
    }

    bool begin_child(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
    {
        return ImGui::BeginChild(str_id, size, border, flags);
    }

    void end_child()
    {
        ImGui::EndChild();
    }

    void dismount()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool begin_tooltip()
    {
        return ImGui::BeginTooltip();
    }

    void end_tooltip()
    {
        ImGui::EndTooltip();
    }

    void set_tooltip(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::SetTooltipV(fmt, args);
        va_end(args);
    }

    void separator() { ImGui::Separator(); }
    void same_line(float offset_from_start_x, float spacing) { ImGui::SameLine(offset_from_start_x, spacing); }
    void new_line() { ImGui::NewLine(); }
    void spacing() { ImGui::Spacing(); }
    void dummy(const ImVec2& size) { ImGui::Dummy(size); }
    void indent(float indent_w) { ImGui::Indent(indent_w); }
    void unindent(float indent_w) { ImGui::Unindent(indent_w); }
    void begin_group() { ImGui::BeginGroup(); }
    void end_group() { ImGui::EndGroup(); }







    void push_style_color(ImGuiCol idx, ImU32 col) { ImGui::PushStyleColor(idx, col); }
    void push_style_color(ImGuiCol idx, const ImVec4& col) { ImGui::PushStyleColor(idx, col); }
    void pop_style_color(int count) { ImGui::PopStyleColor(count); }

    void push_style_var(ImGuiStyleVar idx, float val) { ImGui::PushStyleVar(idx, val); }
    void push_style_var(ImGuiStyleVar idx, const ImVec2& val) { ImGui::PushStyleVar(idx, val); }
    void pop_style_var(int count) { ImGui::PopStyleVar(count); }

    void push_id(const char* str_id) { ImGui::PushID(str_id); }
    void push_id(const void* ptr_id) { ImGui::PushID(ptr_id); }
    void push_id(int int_id) { ImGui::PushID(int_id); }
    void pop_id() { ImGui::PopID(); }

    void text(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::TextV(fmt, args);
        va_end(args);
    }

    void text_colored(const ImVec4& col, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::TextColoredV(col, fmt, args);
        va_end(args);
    }

    void text_wrapped(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::TextWrappedV(fmt, args);
        va_end(args);
    }

    void label_text(const char* label, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::LabelTextV(label, fmt, args);
        va_end(args);
    }

    bool button(const char* label, const ImVec2& size)
    {
        return ImGui::Button(label, size);
    }

    bool small_button(const char* label)
    {
        return ImGui::SmallButton(label);
    }

    bool checkbox(const char* label, bool* v)
    {
        return ImGui::Checkbox(label, v);
    }

    bool radio_button(const char* label, bool active)
    {
        return ImGui::RadioButton(label, active);
    }

    bool radio_button(const char* label, int* v, int v_button)
    {
        return ImGui::RadioButton(label, v, v_button);
    }

    bool selectable(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size)
    {
        return ImGui::Selectable(label, selected, flags, size);
    }

    void progress_bar(float fraction, const ImVec2& size_arg, const char* overlay)
    {
        ImGui::ProgressBar(fraction, size_arg, overlay);
    }

    bool begin_combo(const char* label, const char* preview_value, ImGuiComboFlags flags)
    {
        return ImGui::BeginCombo(label, preview_value, flags);
    }

    void end_combo()
    {
        ImGui::EndCombo();
    }

    bool combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items)
    {
        return ImGui::Combo(label, current_item, items, items_count, popup_max_height_in_items);
    }

    bool input_text(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
    {
        return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
    }

    bool input_float(const char* label, float* v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags)
    {
        return ImGui::InputFloat(label, v, step, step_fast, format, flags);
    }

    bool input_int(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags flags)
    {
        return ImGui::InputInt(label, v, step, step_fast, flags);
    }

    bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
    }

    bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return ImGui::SliderInt(label, v, v_min, v_max, format, flags);
    }

    bool drag_float(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags);
    }

    bool drag_int(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return ImGui::DragInt(label, v, v_speed, v_min, v_max, format, flags);
    }

    bool tree_node(const char* label)
    {
        return ImGui::TreeNode(label);
    }

    bool tree_node_ex(const char* label, ImGuiTreeNodeFlags flags)
    {
        return ImGui::TreeNodeEx(label, flags);
    }

    void tree_pop()
    {
        ImGui::TreePop();
    }

    bool collapsing_header(const char* label, ImGuiTreeNodeFlags flags)
    {
        return ImGui::CollapsingHeader(label, flags);
    }

    bool begin_popup(const char* str_id, ImGuiWindowFlags flags)
    {
        return ImGui::BeginPopup(str_id, flags);
    }

    bool begin_popup_modal(const char* name, bool* p_open, ImGuiWindowFlags flags)
    {
        return ImGui::BeginPopupModal(name, p_open, flags);
    }

    void end_popup()
    {
        ImGui::EndPopup();
    }

    void open_popup(const char* str_id, ImGuiPopupFlags popup_flags)
    {
        ImGui::OpenPopup(str_id, popup_flags);
    }

    void close_current_popup()
    {
        ImGui::CloseCurrentPopup();
    }

    bool begin_tab_bar(const char* str_id, ImGuiTabBarFlags flags)
    {
        return ImGui::BeginTabBar(str_id, flags);
    }

    void end_tab_bar()
    {
        ImGui::EndTabBar();
    }

    bool begin_tab_item(const char* label, bool* p_open, ImGuiTabItemFlags flags)
    {
        return ImGui::BeginTabItem(label, p_open, flags);
    }

    void end_tab_item()
    {
        ImGui::EndTabItem();
    }

    bool begin_main_menu_bar()
    {
        return ImGui::BeginMainMenuBar();
    }

    void end_main_menu_bar()
    {
        ImGui::EndMainMenuBar();
    }

    bool begin_menu(const char* label, bool enabled)
    {
        return ImGui::BeginMenu(label, enabled);
    }

    void end_menu()
    {
        ImGui::EndMenu();
    }

    bool menu_item(const char* label, const char* shortcut, bool selected, bool enabled)
    {
        return ImGui::MenuItem(label, shortcut, selected, enabled);
    }

    bool begin_table(const char* str_id, int columns, ImGuiTableFlags flags, const ImVec2& outer_size, float inner_width)
    {
        return ImGui::BeginTable(str_id, columns, flags, outer_size, inner_width);
    }

    void end_table()
    {
        ImGui::EndTable();
    }

    void table_next_row(ImGuiTableRowFlags row_flags, float min_row_height)
    {
        ImGui::TableNextRow(row_flags, min_row_height);
    }

    bool table_next_column()
    {
        return ImGui::TableNextColumn();
    }

    void table_setup_column(const char* label, ImGuiTableColumnFlags flags, float init_width_or_weight, ImGuiID user_id)
    {
        ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id);
    }

    void table_headers_row()
    {
        ImGui::TableHeadersRow();
    }

    ImDrawList* get_window_draw_list()
    {
        return ImGui::GetWindowDrawList();
        
    }

    ImDrawList* get_background_draw_list()
    {
        return ImGui::GetBackgroundDrawList();
    }

    ImDrawList* get_foreground_draw_list()
    {
        return ImGui::GetForegroundDrawList();
    }

    void demo(bool* pOpen) {
        ImGui::ShowDemoWindow();
    }

    ImGuiKey GlfwKeyToImGuiKey(int key)
    {
        switch (key)
        {
        case GLFW_KEY_TAB: return ImGuiKey_Tab;
        case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
        case GLFW_KEY_UP: return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
        case GLFW_KEY_HOME: return ImGuiKey_Home;
        case GLFW_KEY_END: return ImGuiKey_End;
        case GLFW_KEY_INSERT: return ImGuiKey_Insert;
        case GLFW_KEY_DELETE: return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE: return ImGuiKey_Space;
        case GLFW_KEY_ENTER: return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;

        case GLFW_KEY_A: return ImGuiKey_A;
        case GLFW_KEY_C: return ImGuiKey_C;
        case GLFW_KEY_V: return ImGuiKey_V;
        case GLFW_KEY_X: return ImGuiKey_X;
        case GLFW_KEY_Y: return ImGuiKey_Y;
        case GLFW_KEY_Z: return ImGuiKey_Z;

        default: return ImGuiKey_None;
        }
    }
}
