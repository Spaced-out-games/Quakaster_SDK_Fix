

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
#include "core/res/Image.h"
#include "services/entt_service_storage.h"


// glm
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

// ECS
#include "ent/System.h"
#include "ent/CGraphNode.h"
#include "entt/entity/view.hpp"
#include "ent/Scene.h"

// graphics
#include "gfx/gfx.h"
#include "gfx/VertexBuffer.h"
#include "gfx/VertexBufferLayout.h"
#include "gfx/IndexBuffer.h"
#include "gfx/VertexArray.h"
#include "gfx/ShaderProgram.h"
#include "gfx/CommandBuffer.h"
#include "gfx/Shader.h"
#include "gfx/Texture.h"
#include "gfx/Canvas3D.h"
#include "GL/glew.h"
#include "gfx/c2d.h"
#include "vgui/Canvas2D.h"
//gui
#include "gui/gui.h"


#include "DebugEventLayer.h"
#include "vgui/Canvas2D.h"
#include "DebugEventLayer.h"


struct texPoint2D {
	glm::vec2 position;
	glm::vec2 uv;
};


const std::vector<glm::vec2> points = {
	{-1.0f, -1.0f},
	{-1.0f,  1.0f},
	{ 1.0f, -1.0f},
	{ 1.0f,  1.0f}
};





using namespace qk::resource;
using namespace qk::core;
using namespace qk::gfx;
using namespace qk;

using ServiceStorageType = qk::svc::entt_service_storage;
using ServiceManager = util::BasicServiceManager<ServiceStorageType>;


const std::string onscreen_vert_src = R"(
	#version 330 core
	layout(location = 0) in vec2 aPos;
	out vec2 aTexCoord;
	void main() {
		gl_Position.xy = aPos;
		gl_Position.zw = vec2(0,1);
		aTexCoord = aPos * 0.5 + 0.5; // maps NDC [-1,1] → [0,1]
    }
)";

const std::string onscreen_frag_src = R"(
	#version 330 core

	in vec2 aTexCoord;

	out vec4 FragColor;

	uniform sampler2D texture1;

	void main() {
		FragColor = texture(texture1, aTexCoord);
	}

)";


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
	gfx::FrameBuffer   offscreen;
	gfx::Texture	   offscreen_tex;
	// don't need the shader, vao, vbo, shader, and texture, since it's handled by c2d

	gfx::Texture	   onscreen_tex;
	gfx::ShaderProgram onscreen_shader;
	gfx::VertexArray   onscreen_vao;
	gfx::VertexBuffer<glm::vec2>  onscreen_vbo;
	gfx::Canvas2D c2d;
	
	gfx::Texture morty_tex;




	void init(int argc, char** argv) override {

		// ----------------------------------------
		// CORE SETUP
		// ----------------------------------------
		stack.attach_queue(&queue);
		window.set_event_queue(&queue);

		auto& debug = stack.emplace_layer<DebugEventLayer>();
		auto& c3d = stack.emplace_layer<gfx::Canvas3D>();

		scene.add_service<ServiceManager>();
		svc_manager = &scene.get_service<ServiceManager>();
		scene.add_service<ServiceStorageType>();
		svc_manager->storage = &scene.get_service<ServiceStorageType>();

		Application::init(argc, argv);
		qk::init(3, 3);

		window.init(Window::Size{ 1920, 1080 }, "Demo");
		window.make_context_current();

		gui::mount(window.handle());
		gfx::init();
		c2d.init();

		// ----------------------------------------
		// onscreen initializations
		// ----------------------------------------
		
		// shader
		gfx::Shader onscreen_vert(onscreen_vert_src, GL_VERTEX_SHADER);
		gfx::Shader onscreen_frag(onscreen_frag_src, GL_FRAGMENT_SHADER);
		onscreen_shader.init(onscreen_frag.compile(), onscreen_vert.compile());

		// VartexArray
		onscreen_vao.init();
		onscreen_vao.bind();

		// Vertex Buffer
		onscreen_vbo.init();
		onscreen_vbo.upload(points.data(), points.size(), GL_STATIC_DRAW);
		gfx::VertexBufferLayout onscreen_layout;
		onscreen_layout.push<float>(2);
		onscreen_vao.apply(onscreen_vbo, onscreen_layout);

		Image morty("C:/Users/devin/Desktop/goblin scout.jpg");
		morty_tex.init(morty, GL_TEXTURE_2D);



		// ----------------------------------------
		// FrameBuffer initializations
		// ----------------------------------------
		Image offscreen_img(240, 240, 3);
		offscreen_tex.init(offscreen_img, GL_TEXTURE_2D);
		offscreen.init();
		if (!offscreen.attach(offscreen_tex, 0)) {
			spdlog::error("INCOMPLETE FRAMEBUFFER!");
		}






		// bind the offscreen image



		// ----------------------------------------
		// DRAW
		// ----------------------------------------
		// bypass c2d so we inject the offscreen framebuffer bind
		//offscreen_cmdbuff.bindFramebuffer(offscreen);


		offscreen_cmdbuff.bindFramebuffer(offscreen);
		offscreen_cmdbuff.setViewport(0, 0, offscreen_img.width(), offscreen_img.height());
		offscreen_cmdbuff.clear(GL_COLOR_BUFFER_BIT, 0, 0, 0, 1);

		c2d.begin(&offscreen_cmdbuff);
		c2d.bind_texture(morty_tex);
		//offscreen_cmdbuff.bindTexture(morty_tex.handle(), GL_TEXTURE_2D, 0);
		c2d.draw_rect({ -1,-1 }, { 2, 2 }, { 1,1,1 });
		c2d.end();


		auto sz = window.get_size();

		offscreen_cmdbuff.bindFramebuffer(0);
		offscreen_cmdbuff.setViewport(0, 0, sz.w, sz.h); // REQUIRED
		offscreen_cmdbuff.bindVertexArray(onscreen_vao);
		offscreen_cmdbuff.bindShaderProgram(onscreen_shader);
		offscreen_cmdbuff.bindTexture(offscreen_tex.handle(), GL_TEXTURE_2D, 0);
		offscreen_cmdbuff.setUniformi(onscreen_shader.uniform("texture1"), 0);

		offscreen_cmdbuff.drawVertexArray(GL_TRIANGLE_STRIP, 0, 4);


		


    }



	void run() override {

		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();


		stack.render();
		gfx::call(offscreen_cmdbuff);
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

