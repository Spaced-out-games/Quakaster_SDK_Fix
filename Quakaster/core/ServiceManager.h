#pragma once
#include <unordered_map>
#include <string>
#include "IService.h"
#include "../thirdparty/entt/src/entt/entity/registry.hpp" // temp test

namespace qk {

    struct ServiceEntry;
    using ServiceMap = std::unordered_map<std::string, ServiceEntry>;

    struct ServiceEntry {
        IService* service = nullptr;
        void (*dtor)(void* storage, ServiceMap&, const std::string&) = nullptr; // C-style function pointer
    };

    // Type for ServiceManager bookkeeping

    // ----------------------------------------
    // Concept: runtime service storage
    // ----------------------------------------
    template <typename S>
    concept ServiceStorageConcept = requires(S s, ServiceMap& map, const std::string & name) {
        // emplace<T>(name, map, args...) -> returns IService*
        { s.template emplace<int>(name, map) } -> std::same_as<IService*>;

        // get(name, map) -> returns IService*
        { s.get(name, map) } -> std::same_as<IService*>;

        // erase(name, map) -> void
        { s.erase(name, map) } -> std::same_as<void>;
    };

    // ----------------------------------------
    // ServiceManager wraps any storage
    // ----------------------------------------
    template <ServiceStorageConcept Storage>
    struct ServiceManager {
        Storage* storage;
        ServiceMap map;

        template <typename T, typename... Args>
        T* emplace(const std::string& name, Args&&... args) {
            return static_cast<T*>(storage->template emplace<T>(name, map, std::forward<Args>(args)...));
        }

        IService* get(const std::string& name) {
            return storage->get(name, map);
        }

        
        void erase(const std::string& name) {
            storage->erase(name, map);
        }
    };



    struct EnTTContextStorage {
        entt::registry* reg;

        template <typename T, typename... Args>
        IService* emplace(const std::string& name, ServiceMap& map, Args&&... args) {
            T& svc = reg->ctx().emplace<T>(std::forward<Args>(args)...);
            map[name].service = &svc;
            map[name].dtor = [](void* storage, ServiceMap&, const std::string&) {
                entt::registry* registry = (entt::registry*)storage;
                registry->ctx().erase<T>();
            };

            return &svc;
        }

        IService* get(const std::string& name, ServiceMap& map) {
            auto it = map.find(name);
            return it != map.end() ? it->second.service : nullptr;
        }

        
        void erase(const std::string& name, ServiceMap& map) {
            auto it = map.find(name);
            if (it != map.end()) {
                
                it->second.dtor(reg, map, name);
                map.erase(it);         // bookkeeping cleanup
            }
        }
    };


} // namespace qk