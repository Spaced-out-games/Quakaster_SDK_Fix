#include "ServiceManager.h"

namespace qk {
    void ServiceManager::remove_service(const std::string& name) {
        auto it = m_Services.find(name);
        if (it != m_Services.end()) {
            if (it->second.dtor && registry) it->second.dtor(registry);
            m_Services.erase(it);
        }
    }

    IService* ServiceManager::get_service(const std::string& name) {
        auto it = m_Services.find(name);
        if (it != m_Services.end()) {
            return it->second.svc; // return stored pointer
        }
        return nullptr; // service not found
    }
}