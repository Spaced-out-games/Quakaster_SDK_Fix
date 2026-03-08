#include "MeshService.h"
#include "GL\glew.h"
#include <iostream>

namespace gfx {




    MeshGroup* MeshService::GetMeshGroup(entt::hashed_string id) {
        return nullptr;
        //auto it = m_GroupLUT.find(id.value());
        //return (it != m_GroupLUT.end()) ? m_Groups.data() + it->second : nullptr;
    }

    MeshService::~MeshService() {

    }

    MeshService::MeshService() {

    }
}