#pragma once
#include "../Core.h"
#include <vector>
#include <SDL.h>
//#include "../qkio/Event.h"

//typedef union SDL_Event;


namespace qk {




	struct QK_API Layer
	{
		// Input & rendering layer.
		Layer();
		virtual ~Layer();

		/// <summary>
		///  Defines how to render this layer. See GUILayer for more details
		/// </summary>
		virtual void render();

		/// <summary>
		/// Defines what the layer should do  when it receives an SDLEvent. Returns 1 if the input is consumed by this layer
		/// </summary>
		/// <param name="evt">The SDLEvent we get from polling</param>
		/// <returns>true if the event is consumed by this layer</returns>
		virtual bool on_event(const SDL_Event& evt) = 0;

		//virtual bool on_event(const qk::io::Event evt) = 0;

		/// <summary>
		/// What to do when the layer attaches to the LayerStack
		/// </summary>
		virtual void on_attach();

		/// <summary>
		/// What to do when the layer detached from the LayerStack
		/// </summary>
		virtual void on_detach();
	};


	#pragma warning(push)
	#pragma warning(disable: 4251)
	class QK_API LayerStack
	{
		private:
			uint8_t m_EmptyCount = 0;
			SDL_Event m_Event{};
			std::vector<Layer*> m_Layers{};
		public:

			/// <summary>
			/// Inserts a layer into the LayerStack
			/// </summary>
			/// <param name="layer">The layer to insert</param>
			/// <returns>a handle to the layer's index for later deletion, or SIZE_MAX on failure </returns>
			inline [[nodiscard]] size_t insert(Layer* layer);

			/// <summary>
			/// Attempts to delete the 
			/// </summary>
			/// <param name="index"></param>
			/// <returns></returns>
			inline bool remove(size_t index);
			inline void render();
			inline void propagate_events();
			~LayerStack();
	};
}