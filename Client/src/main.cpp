#include <iostream>
#include "entrypoint.h"

#include <thread>
#include <stdint.h>
#include "core/Window.h"
#include "core/EventQueue.h"
#include "core/DefaultEvents.h"
#include "core/LayerStack.h"
#include "core/ServiceManager.h"
#include "core/ISystem.h"
#include "integrations/entt_service_storage.h"

#include "gfx/gfx.h"
#include "GL/glew.h"
#include "gui/GUIService.h"


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "entity/CHeirarchy.h"
#include "gfx/VertexBuffer.h"
#include "gfx/VertexBufferLayout.h"
#include "gfx/IndexBuffer.h"
#include "gfx/VertexArray.h"
#include "gfx/ShaderProgram.h"
#include "gfx/Shader.h"


const std::vector<glm::vec2> points = {
	glm::vec2{0.0, 0.0},
	glm::vec2{0.0, 1.0},
	glm::vec2{1.0, 0.0}
};

const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragShaderSrc = R"frag(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(0.5);
}
)frag";
#include <vector>
#include "entt/entity/view.hpp"

struct MyApp : qk::Application {

	// window
	qk::Window window;
	// queue, stack, registry, and systems
	std::shared_ptr<qk::EventQueue> queue;
	qk::LayerStack stack;
	entt::registry registry;
	qk::SystemStack systems;

	gfx::VertexArray arr;
	gfx::VertexBuffer<glm::vec2> buffer;
	gfx::VertexBufferLayout layout;
	gfx::ShaderProgram program;



	void get_dirty_entities(std::vector<entt::entity>& out) {

		auto view = registry.view<qk::entity::CHeirarchy::DirtyFlag>();

		for (auto entity : view) {
			out.push_back(entity);
		}

	}



	void init(int argc, char** argv) override {






		/*
		qk::entity::CHeirarchyService svc(registry);

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
		//window.set_event_queue(&evt_queue);

		// initialize gui and gfx
		gui::init(window.handle());
		gfx::init();

		layout.push<float>(2, false);


		arr.init();
		arr.bind();


		buffer.init(points.data(), points.size(), GL_STATIC_DRAW);
		buffer.bind();

		arr.apply(buffer, layout);


		gfx::Shader frag(fragShaderSrc, GL_FRAGMENT_SHADER);
		gfx::Shader vert(vertexShaderSrc, GL_VERTEX_SHADER);


		gfx::Handle hFrag = frag.compile();
		gfx::Handle hVert = vert.compile();

		program.init(hFrag, hVert);
		program.bind();
	}



	void run() override {
		
		//auto& SvcMgr = registry.ctx().get<qk::ServiceManager<qk::integrations::entt_service_storage>>();

		arr.bind();
		program.bind();
		gfx::drawArrays(GL_TRIANGLES, 0, buffer.count()); // sz should be 3

		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();
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

