// stdlib
#include <iostream>
#include <stdint.h>
#include <vector>
#include <thread>

// core
#include "entrypoint.h"
#include "core/core/Window.h"
#include "core/io/EventQueue.h"
#include "core/io/DefaultEvents.h"
#include "core/io/LayerStack.h"
#include "core/utility/ServiceManager.h"
#include "core/utility/AcceleratedLinkedList.h"
#include "core/res/Image.h"
#include "services/entt_service_storage.h"


// glm
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

// ECS
#include "entt/entity/view.hpp"
#include "ent/CGraphNode.h"
#include "ent/System.h"
#include "ent/Scene.h"
#include "GL/glew.h"

// graphics
#include "gfx/VertexBufferLayout.h"
#include "gfx/FullscreenBlitter.h"
#include "gfx/ShaderProgram.h"
#include "gfx/CommandBuffer.h"
#include "gfx/CRenderTarget.h"
#include "gfx/VertexBuffer.h"
#include "gfx/IndexBuffer.h"
#include "gfx/VertexArray.h"
#include "gfx/Canvas3D.h"
#include "gfx/Texture.h"
#include "gfx/Shader.h"
#include "gfx/c2d.h"
#include "gfx/gfx.h"

//gui
#include "gui/gui.h"
#include "gui/GUILayer.h"


#include "DebugEventLayer.h"
#include "gfx/Renderer2D.h"
#include "DebugEventLayer.h"
#include "gfx/TextureBuffer.h"


using namespace qk::resource;
using namespace qk::core;
using namespace qk::gfx;
using namespace qk;

using ServiceStorageType = qk::svc::entt_service_storage;
using ServiceManager = util::BasicServiceManager<ServiceStorageType>;




struct MyApp : Application {

	// window
	Window window;

	// queue, stack
	EventQueue queue;
	LayerStack stack;
	ServiceManager* svc_manager = nullptr;

	// ECS
	qk::ent::Scene scene;

	//entt::registry registry;
	std::vector<qk::ent::System> systems;


	// graphics
	gfx::CommandBuffer offscreen_cmdbuff;

	gfx::Renderer2D c2d;
	
	gfx::Texture morty_tex;

	FullscreenBlitter blit;

	gfx::CRenderTarget renderTarget;
	TextureBuffer tb;
	


	void init_core(int argc, char** argv) {
		// ----------------------------------------
		// CORE SETUP
		// ----------------------------------------
		stack.attach_queue(&queue);
		window.set_event_queue(&queue);

		auto& c3d = stack.emplace_layer<gfx::Canvas3D>();
		auto& debug = stack.emplace_layer<DebugEventLayer>();

		scene.add_service<ServiceManager>();
		svc_manager = &scene.get_service<ServiceManager>();
		scene.add_service<ServiceStorageType>();
		svc_manager->storage = &scene.get_service<ServiceStorageType>();

		Application::init(argc, argv);
		qk::init(3, 3);

		window.init(Window::Size{ 1920, 1080 }, "Demo");
		window.make_context_current();


		gfx::init();
		c2d.init();
	}




	void init(int argc, char** argv) override {
		init_core(argc, argv);

		tb.init(GL_STATIC_DRAW, GL_RGBA32F);

		glm::vec4 positions = glm::vec4{1.0,1.0,0.0,0.0};


		tb.upload(&positions, sizeof(positions));
		auto& gui = stack.emplace_layer<gui::GUILayer>(&window);

		

		Image morty("C:/Users/devin/Desktop/goblin scout.jpg");
		morty_tex.init(morty, GL_TEXTURE_2D);


		renderTarget.init(160, 90);



		c2d.begin(&offscreen_cmdbuff);
		c2d.bind_texture(morty_tex, 1);
		c2d.bind_texture(tb.m_Texture, 0);
		c2d.draw_rect({ -1,-1 }, { 2, 2 }, { 1,1,1 });
		c2d.end();

		// ----------------------------------------
		// DRAW OFFSCREEN
		// ----------------------------------------

		auto sz = window.get_size();

		blit.setRenderTarget(renderTarget.m_OffscreenTarget.handle());

		blit.init(sz.w, sz.h);		


    }



	void run() override {

		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();


		// gfx::call(renderTarget.m_OffscreenCommandBuffer);
		 gfx::call(offscreen_cmdbuff);
		// gfx::call(blit.m_CommandBuffer);
		stack.render();

		queue.clear();
		set_status(window.should_close());

	}

	MyApp() = default;

	~MyApp() override {
		window.destroy();
		//gfx::close();
		qk::close();
	}



};

std::unique_ptr<Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

