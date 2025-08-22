#pragma once
#include "Scene.h"
#include <stdexcept>


namespace qk
{
    class QK_API Entity
    {
        entt::registry& m_Registry;

    public:
        // should not be public, just for testing purposes
        entt::entity m_ID;



        // --- Lifetime ---
        Entity(entt::registry& registry);
        Entity(entt::registry& registry, entt::entity id);
        ~Entity() = default; // more explicit
        inline void destroy();
        inline bool valid() const;


        // --- Queries ---
        template <class... component_Ts>
        inline bool all_of() const {
            if (!valid()) return false;
            return m_Registry.all_of<component_Ts...>(m_ID);
        }

        template <class... component_Ts>
        inline bool any_of() const {
            if (!valid()) return false;
            return m_Registry.any_of<component_Ts...>(m_ID);
        }


        // --- Component management ---
        template <class component_t, class... Arg_Ts>
        inline decltype(auto) emplace(Arg_Ts&&... args) {
            if (!valid()) throw std::runtime_error("Entity::emplace called on invalid entity");
            return m_Registry.emplace<component_t>(m_ID, std::forward<Arg_Ts>(args)...);
        }

        template <class component_t, class... Arg_Ts>
        inline decltype(auto) emplace_or_replace(Arg_Ts&&... args) {
            return m_Registry.emplace_or_replace<component_t>(
                m_ID, std::forward<Arg_Ts>(args)...);
        }

        template <class component_t, class... Arg_Ts>
        inline decltype(auto) get_or_emplace(Arg_Ts&&... args) {
            return m_Registry.get_or_emplace<component_t>(
                m_ID, std::forward<Arg_Ts>(args)...);
        }

        template <class component_t>
        inline decltype(auto) get() {
            return m_Registry.get<component_t>(m_ID);
        }

        template <class component_t>
        inline decltype(auto) try_get() {
            if (!valid()) return nullptr;  // same as registry.try_get
            return m_Registry.try_get<component_t>(m_ID);
        }

        template <class component_t>
        inline void remove() {
            m_Registry.remove<component_t>(m_ID);
        }

        operator bool() const noexcept {
            return valid();
        }

    };
}