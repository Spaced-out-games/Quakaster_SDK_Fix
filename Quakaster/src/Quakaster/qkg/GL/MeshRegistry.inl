#pragma once

#include "MeshConfiguration.h"  // Include only here

namespace qkg {

    template <class vertex_t>
    void MeshRegistry::register_configuration(const MeshConfiguration<vertex_t>& configuration) {
        size_t vertex_t_hash = typeid(vertex_t).hash_code();
        m_ConfigMap[vertex_t_hash].m_ConfigurationLambda = configuration.m_VertexAttributePointerLambda;
    }

} // namespace qkg
