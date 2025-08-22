#pragma once
#include <Quakaster/Core.h>
#include <Quakaster/qk/Layer.h>
#include <Quakaster/qkui/UIContext.h>
#include <Quakaster/qkecs/Scene.h>

#include <Quakaster/qkio/TController.h>



namespace qk
{

	
	struct InputLayer : qk::Layer
	{
		using game_event_t = qk::TGameEvent<EGameEvent_FPS>;
		using controller_t = TController<game_event_t>;
		using emitter_t = TGameEvent_Emitter<SDL_Event, game_event_t>;

		entt::registry& m_Registry;
		
		public:

			InputLayer(entt::registry& registry);
			bool on_event(const SDL_Event& evt) override;
			void on_attach() override;
			void on_detach() override;
			void render() override;
	};

}

