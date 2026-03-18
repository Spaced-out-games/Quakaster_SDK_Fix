#pragma once
#include "entt/entity/registry.hpp"
#include "../core.h"
namespace qk::ent {

	struct Scene {
		entt::registry registry;

		Scene() = default;
		~Scene() = default;

		// service related things
		template <class T, typename... Args>
		T& add_service(Args&&... args) {
			if (registry.ctx().contains<T>()) return registry.ctx().get<T>();

			return registry.ctx().emplace<T>(std::forward<Args>(args)...);
		}

		template <class T>
		T& get_service() {
			return registry.ctx().get<T>();
		}

		template <class T>
		bool has_service() const {
			return registry.ctx().contains<T>();
		}


		// entity component queries
		template <class T, typename... Args>
		T& add_component(entt::entity e, Args&&... args) {
			return registry.emplace<T>(e, std::forward<Args>(args)...);
		}

		template <class T>
		bool has_component(entt::entity target) {
			return registry.all_of<T>(target);
		}

		template <class T>
		T& get_component(entt::entity target) {
			return registry.get<T>(target);
		}

		template <class T>
		T* try_get_component(entt::entity target) {
			return registry.try_get<T>(target);
		}

		template <class T>
		const T& get_component(entt::entity target) const {
			return registry.get<T>(target);
		}

		template <class... Components>
		auto view() {
			return registry.view<Components...>();
		}

		template <class T>
		void remove_component(entt::entity e) {
			registry.remove<T>(e);
		}

		entt::entity create() {
			return registry.create();
		}

		void destroy(entt::entity target) {
			registry.destroy(target);
		}

		template <class T>
		bool has_component(entt::entity target) const {
			return registry.all_of<T>(target);
		}

		template <class T>
		T* try_get_component(entt::entity target) const {
			return registry.try_get<T>(target);
		}

		template <class... Components>
		auto view() const {
			return registry.view<Components...>();
		}


		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		Scene(Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;

		explicit operator entt::registry& () {
			return registry;
		}

		explicit operator const entt::registry& () const {
			return registry;
		}

	};


}