#pragma once
#include "../../Core.h"
#include <unordered_map>

namespace qkg {
    template <class vertex_t>
    class MeshConfiguration;

    struct MeshRegistryEntry
    {
        func_ptr_t<void, void> m_ConfigurationLambda;
    };


    struct MeshRegistry {

        MeshRegistry() = default;
        ~MeshRegistry() = default;

        std::unordered_map<size_t, MeshRegistryEntry> m_ConfigMap;

        template <class vertex_t>
        void register_configuration(const MeshConfiguration<vertex_t>& configuration);
    };
}

#include "MeshRegistry.inl"