#include "KernelIdentifierTable.h"
#include <unordered_map>

namespace qk::kernel::id {
    std::unordered_map<entt::id_type, std::string> g_identifier_table;
    static const std::string unknown = "<unknown>";

    entt::id_type add(const std::string& identifier) {
        entt::id_type hash = entt::hashed_string{ identifier.c_str() }.value();
        g_identifier_table.emplace(hash, identifier); // no-op if already there
        return hash;
    }

    void remove(entt::id_type hash) {
        g_identifier_table.erase(hash);
    }

    const std::string& name(entt::id_type hash) {
        auto it = g_identifier_table.find(hash);
        return it != g_identifier_table.end() ? it->second : unknown;
    }

    const std::unordered_map<entt::id_type, std::string>& lut()
    {
        return g_identifier_table;
    }
}
