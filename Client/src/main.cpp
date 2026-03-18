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

//gui
#include "gui/gui.h"


#include "DebugEventLayer.h"
#include "vgui/Canvas2D.h"
#include "DebugEventLayer.h"


struct texPoint2D {
	glm::vec2 position;
	glm::vec2 uv;
};


const std::vector<texPoint2D> points = {
	{{0.0, 0.0}, {0.0,1.0}},
	{{0.0, 1.0}, {0.0,0.0}},
	{{1.0, 0.0}, {1.0,1.0}},
	{{1.0, 1.0}, {1.0,0.0}}
};

const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
	TexCoord = aTexCoord;
}
)";

const char* fragShaderSrc = R"frag(
	#version 330 core
	out vec4 FragColor;
	in vec2 TexCoord;
	uniform sampler2D texture1;

	void main() {
		FragColor = texture(texture1, TexCoord);
	}
)frag";



using namespace qk::resource;
using namespace qk::core;
using namespace qk::gfx;
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
	gfx::CommandBuffer commands;
	gfx::VertexArray arr;
	gfx::VertexBuffer<texPoint2D> buffer;
	gfx::VertexBufferLayout layout;
	gfx::ShaderProgram program;
	gfx::Texture texture;


	



	void init(int argc, char** argv) override {

		// hook up the event queue
		stack.attach_queue(&queue);
		window.set_event_queue(&queue);


		// add layers
		auto& debug = stack.emplace_layer<DebugEventLayer>();
		auto& c3d = stack.emplace_layer<gfx::Canvas3D>();




		// init services
		scene.add_service<ServiceManager>();
		svc_manager = &scene.get_service<ServiceManager>();

		scene.add_service<ServiceStorageType>();
		svc_manager->storage = &scene.get_service<ServiceStorageType>();


			
		// init systems



		//auto pLayer = std::make_unique<qk::DebugEventLayer>();

		//stack.insert_layer(std::move(pLayer));

		// Set up the application
		Application::init(argc, argv);
		qk::init(3,3);

		// Window initialization
		window.init(Window::Size{ 480, 480 }, "Demo");
		window.make_context_current();

		// initialize gui and gfx
		gui::mount(window.handle());
		gfx::init();
		
		// Unfortunately, this has to go here until we deal with the ctor
		auto& c2d = stack.emplace_layer<vgui::Canvas2D>(256);


		Image img("C:/Users/devin/Desktop/morty.jpg");

		texture.init(img, GL_TEXTURE_2D);
		///*
		layout.push<float>(2, false);
		layout.push<float>(2, false);


		arr.init();
		arr.bind();

		buffer.init();
		buffer.upload(points.data(), points.size(), GL_STATIC_DRAW);
		buffer.bind();

		arr.apply(buffer, layout);


		gfx::Shader frag(fragShaderSrc, GL_FRAGMENT_SHADER);
		gfx::Shader vert(vertexShaderSrc, GL_VERTEX_SHADER);


		gfx::Handle hFrag = frag.compile();
		gfx::Handle hVert = vert.compile();

		program.init(hFrag, hVert);
		
		//*/





		commands.bindVertexArray(arr);
		commands.bindTexture(texture);
		commands.bindShaderProgram(program);
		commands.drawVertexArray(GL_TRIANGLE_STRIP, 0, buffer.count());
		c3d.m_CommandBuffer = &commands;

		
		c2d.m_Persist = true;




		/*
		canvas.draw_triangle(
			{ 0.0f, 0.0f },
			{ 0.0f, 1920.0f },
			{ 1080.0f, 1920.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		);

		canvas.draw_triangle(
			{ 0.0f, 0.0f },
			{ 1080.0f, 0.0f },
			{ 1080.0f, 1920.0f },
			{ 0.0f, 1.0f, 1.0f, 1.0f }
		);

		canvas.draw_rect(
			{ 270.0f, 0.0f },
			{ 540.0f, 1920.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f }
		);

		canvas.draw_image(
			texture.handle(),
			{ 0.0f, 960.0f },
			{ 480.0f, 480.0f }
		);

		*/

	}



	void run() override {
		
		//auto& SvcMgr = registry.ctx().get<qk::ServiceManager<qk::integrations::entt_service_storage>>();
		///*
		//gui::begin_frame();

		//gui::begin("hello");
		//gui::text("hello world");
		//gui::end();

		//gui::end_frame();

		//*/
		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();


		stack.render();
		queue.clear();
		set_status(window.should_close());
		
	}

	MyApp() = default;

	~MyApp() override {
		window.destroy();
		gfx::close();
		qk::close();
	}



};

std::unique_ptr<Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

