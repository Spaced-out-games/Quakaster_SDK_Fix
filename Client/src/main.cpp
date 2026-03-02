#include <iostream>
#include "entrypoint.h"
#include "core/Window.h"
#include "core/EventQueue.h"
#include <thread>
#include <stdint.h>
#include "core/DefaultEvents.h"
#include "core/LayerStack.h"
#include "core/ServiceManager.h"
#include "integrations/entt_service_storage.h"

#include "TestLayer.h"
#include "GreetLayer.h"
#include "gfx/VertexAttributeSetupRegistry.h"
#include "gfx/gfx.h"
#include "GL/glew.h"
#include "gui/GUIService.h"
#include "gfx/GraphicsService.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"



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
    FragColor = vec4(1.0);
}
)frag";


struct MyApp : qk::Application {
	qk::Window window;
	std::shared_ptr<qk::EventQueue> queue;
	qk::LayerStack stack;
	entt::registry registry;
	qk::integrations::entt_service_storage storage{ &registry };
	qk::ServiceManager<qk::integrations::entt_service_storage> mgr;

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int shader = 0;

	void init(int argc, char** argv) override {
		Application::init(argc, argv);
		qk::init();
		mgr.storage = &storage;
		queue = std::make_unique<qk::EventQueue>();
		window.init(qk::Window::Size{ 480, 480 }, "Demo");
		window.make_context_current();
		gfx::init();
		gui::init(window.handle());

		window.set_event_queue(queue);
		stack.attach_queue(queue);
		stack.insert_layer(std::make_unique<TestLayer>());
		stack.insert_layer(std::make_unique<GreetLayer>());
		gfx::GraphicsPrimitiveService* gsvc = mgr.emplace<gfx::GraphicsPrimitiveService>("GraphicsSvc");
		
		//auto& reg = gsvc->m_AttributeSetupRegistry;

		gsvc->autoregister_vertex_attribute_setup_override<glm::vec2>([](unsigned int& location, bool normalize, uintptr_t offset) {
			gfx::add_vertex_attribute_pointer_impl(location, 2, GL_FLOAT, normalize, sizeof(glm::vec2), offset);
			location++;
		});

		gsvc->add_generator<glm::vec2>("vert2D");



		vao = gfx::generate_vao(); // 1
		gfx::bind_vao(vao);
		
		vbo = gsvc->generate_vbo("vert2D", points, GL_STATIC_DRAW); // 1
		gfx::bind_vertexBuffer_impl(vbo);




		shader = gfx::create_shader_program(vertexShaderSrc, fragShaderSrc);
		gfx::bind_shader_program(shader); // 3



	}



	void run() override {

		//gfx::test();

		gfx::bind_shader_program(shader);
		gfx::bind_vao(vao);
		gfx::drawArrays(GL_TRIANGLES, 0, points.size());
		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();
		set_status(window.should_close());

		//window.queue()->clear();
		//std::this_thread::sleep_for(std::chrono::milliseconds(17));
		//window.pollEvents();
		//stack.propagate_events();
		//gfx::test();

		//gfx::drawArrays(GL_TRIANGLES, 0, points.size());
		//gui::demo();

		//window.swap_buffers();


		//set_status(window.should_close());


	}

	~MyApp() override {
		window.destroy();
		gfx::close();
		qk::close();
	}



};

std::unique_ptr<qk::Application> qk::create_application(int argc, char** argv) {
	return std::make_unique<MyApp>();
}

