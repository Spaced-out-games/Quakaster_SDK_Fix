#pragma once
#include "../Core.h"
#include "Entity.h"
#include "Scene.h"
#include <limits>

namespace qk
{
	// Stable actor-child handle.
	using child_handle_t = uint32_t;


	

	/// <summary>
	/// Represents an object in the scene. Implicitly forms a pseudo-scene graph.
	/// Ideally used as a base class, so long as no state is added to the derivative directly, instead utilizing
	/// the root of the actor to store per-actor state. This lets us cast back and forth without memory
	/// alignments being an issue. Derivatives *can* add methods, but those should ideally be component-focused
	/// inlined helper functions (eg, APlayer::move() updating the root's Transform, and every child's mat4).
	/// 
	/// 
	/// </summary>
	class QK_API AActor
	{

		Entity m_Root;
		child_handle_t m_NextChildIndex = 0;

		// unordered map so that insertions and removals are O(1) and handles are stable after deletions
		std::unordered_map<child_handle_t, Entity> m_Children;

		public:

			AActor();
			AActor(Scene& scene);

			/// <summary>
			/// removes the children from the actor, and clears the root. This will make APIs ineffectual unless you add them back. Should be used to explicitly destroy an Actor, but can also be recycled
			/// </summary>
			/// <param name="scene"></param>
			inline void destroy(Scene& scene);

			/// <summary>
			/// Removes the children from the actor
			/// </summary>
			/// <param name="scene"></param>
			inline void destroy_children(Scene& scene);
			

			


			/// <summary>
			/// Use the root child to attach one-per-actor components and form your own APIs.
			/// The engine, under the hood uses this for ticking CThinkScripts, relaying level logic 
			/// via logic::CRelay, transform propagation via CTransform and CMat4x4.
			/// </summary>
			/// <returns> the root entity of this Actor</returns>
			inline Entity& root();

			/// <summary>
			/// Children represent intermediate component groups.
			/// For example, a rendering system might rely on {CCamera, CRenderTarget, CMatrix4x4, CTransform} for its logic
			/// </summary>
			/// <returns>the child entity the handle refers to</returns>
			inline Entity& child(child_handle_t handle);


			/// <summary>
			/// Adds a child to the Actor.
			/// </summary>
			/// <param name="scene">the qk::Scene this actor is in</param>
			/// <returns>a handle to the newly-created child</returns>
			inline child_handle_t add_child(Scene& scene);


			/// <summary>
			/// Deletes a child entity from the actor
			/// </summary>
			/// <param name="scene">The scene this actor is a part of</param>
			/// <param name="handle">The handle to the target child entity</param>
			inline void delete_child(Scene& scene, child_handle_t handle);

	};



}