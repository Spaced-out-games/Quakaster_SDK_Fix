#pragma once
#include "../Core.h"
#include <vector>
#include "../qkg/GL/import.h"

//typedef union SDL_Event;


namespace qk {
	// temporary, until we get entt::dispatcher working
	//inline QK_API int status = 0;

	struct QK_API Layer
	{

		Layer();
		virtual ~Layer();
		virtual void render();
		virtual bool on_event(const SDL_Event& evt) = 0;
		virtual void on_attach();
		virtual void on_detach();
	};

	class QK_API LayerStack
	{
		uint8_t m_EmptyCount = 0;
		SDL_Event m_Event;
		std::vector<Layer*> m_Layers;
		public:
			inline [[nodiscard]] uint8_t insert(Layer* layer);
			inline bool remove(uint8_t index);
			inline void render();
			inline void propagate_events();
			~LayerStack();
	};
}