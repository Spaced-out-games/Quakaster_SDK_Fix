#include <iostream>
#include "entrypoint.h"

#include <thread>
#include <stdint.h>
#include "core/core/Window.h"
#include "core/io/EventQueue.h"
#include "core/io/DefaultEvents.h"
#include "core/io/LayerStack.h"
#include "core/utility/ServiceManager.h"
#include "core/res/Image.h"
#include "services/entt_service_storage.h"

#include "gfx/gfx.h"
#include "GL/glew.h"
#include "gui/gui.h"


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "ent/CGraphNode.h"
#include "gfx/VertexBuffer.h"
#include "gfx/VertexBufferLayout.h"
#include "gfx/IndexBuffer.h"
#include "gfx/VertexArray.h"
#include "gfx/ShaderProgram.h"
#include "gfx/Shader.h"
#include "gfx/Texture.h"
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
#include <vector>
#include "entt/entity/view.hpp"
#include "ent/System.h"
#include "vgui/vgui.h"

struct MyApp : qk::Application {

	// window
	qk::Window window;
	// queue, stack, registry, and systems
	std::shared_ptr<qk::EventQueue> queue;
	qk::LayerStack stack;
	entt::registry registry;
	std::vector<qk::ent::System> systems;

	gfx::VertexArray arr;
	gfx::VertexBuffer<texPoint2D> buffer;
	gfx::VertexBufferLayout layout;
	gfx::ShaderProgram program;
	gfx::Texture texture;






	void init(int argc, char** argv) override {






		/*
		qk::ent::GraphNodeService svc(registry);

		entt::entity root = svc.new_root();

		auto a = svc.add_child(root);
		auto b = svc.add_child(root);
		auto c = svc.add_child(root);
		auto d = svc.add_child(root);
		svc.add_child(b);
		svc.add_child(b);
		svc.add_child(b);

		svc.print_tree(root);

		spdlog::info("------------------------------------------------------------------------------");

		svc.detach_child(root, b);
		svc.print_tree(root);
		spdlog::info("------------------------------------------------------------------------------");
		svc.print_tree(b);

		std::vector<entt::entity> dirty;
		get_dirty_entities(dirty);

		spdlog::info("------------------------------------------------------------------------------");

		std::cout << "Dirty:";
		for (auto e : dirty) {
			std::cout << (uint32_t)e << " ";
		}*/


		queue = std::make_shared<qk::EventQueue>();

		//auto pLayer = std::make_unique<qk::DebugEventLayer>();

		//stack.insert_layer(std::move(pLayer));

		// Set up the application
		Application::init(argc, argv);
		qk::init(3,3);

		// Set up queues, services, stacks, and systems
		//auto& SvcMgr = registry.ctx().emplace<qk::ServiceManager<qk::integrations::entt_service_storage>>();
		//auto& SvcStg = registry.ctx().emplace<qk::integrations::entt_service_storage>(&registry);
		//SvcMgr.storage = &SvcStg;
		//auto& evt_queue = registry.ctx().emplace<qk::EventQueue>();
		//stack.attach_queue(&evt_queue);




		// Window initialization
		window.init(qk::Window::Size{ 480, 480 }, "Demo");
		window.make_context_current();
		window.set_event_queue(queue.get());

		// initialize gui and gfx
		gui::mount(window.handle());

		gfx::init();
		
		qk::Image img("C:/Users/devin/Desktop/morty.jpg");

		texture.init(img, GL_TEXTURE_2D);
		/*
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
		program.bind();
		*/

		vgui::Layer2D* raw = new vgui::Layer2D(65536);

		std::unique_ptr<qk::ILayer> layer(raw);

		stack.insert_layer(std::move(layer));

		stack.attach_queue(queue.get());
		auto& canvas = *((vgui::Layer2D*)stack[0]);
		canvas.m_Persist = true;
		vgui::draw_triangle(canvas, { 0.0, 0.0 }, { 1.0,0.0 }, { 1.0,1.0 }, { 0.0, 0.0, 1.0, 1.0 });



	}



	void run() override {
		
		//auto& SvcMgr = registry.ctx().get<qk::ServiceManager<qk::integrations::entt_service_storage>>();
		/*
		arr.bind();
		program.bind();
		gui::begin_frame();

		gui::begin("hello");
		gui::text("hello world");
		gui::end();

		gui::end_frame();


		gfx::drawArrays(GL_TRIANGLE_STRIP, 0, buffer.count());
		*/
		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();


		stack.render();
		queue->clear();
		set_status(window.should_close());
		
	}

	MyApp() = default;

	~MyApp() override {
		window.destroy();
		gfx::close();
		qk::close();
	}



};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

