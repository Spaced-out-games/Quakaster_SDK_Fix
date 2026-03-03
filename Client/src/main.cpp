#include <iostream>
#include "entrypoint.h"
#include "core/Window.h"
#include "core/EventQueue.h"
#include <thread>
#include <stdint.h>
#include "core/DefaultEvents.h"
#include "core/LayerStack.h"
#include "core/ServiceManager.h"
#include "core/ISystem.h"
#include "integrations/entt_service_storage.h"

#include "gfx/VertexAttributeSetupRegistry.h"
#include "gfx/gfx.h"
#include "GL/glew.h"
#include "gui/GUIService.h"
#include "gfx/GraphicsPrimitiveService.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "gfx/MeshConfig.h"
#include "gfx/Shader.h"
#include "gfx/ShaderProgram.h"
#include "gfx/VAO.h"
#include "gfx/VBO.h"
#include "entity/CHeirarchy.h"


const std::vector<glm::vec2> points = {
	glm::vec2{0.0, 0.0},
	glm::vec2{0.0, 1.0},
	glm::vec2{1.0, 0.0}
};

const char* vertexShaderSrc = R"(
#version 330 core
in vec2 aPos;

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
	gfx::MeshGroup mesh;
	gfx::ShaderProgram program;

	// Test OpenGL state
	gfx::VBO vao;
	gfx::VBO vbo;
	unsigned int shader = 0;



	void get_dirty_entities(std::vector<entt::entity>& out) {

		auto view = registry.view<qk::entity::CHeirarchy::DirtyFlag>();

		for (auto entity : view) {
			out.push_back(entity);
		}

	}



	void init(int argc, char** argv) override {

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
		}


		

		// Set up the application
		Application::init(argc, argv);
		qk::init(3,3);

		// Set up queues, services, stacks, and systems
		auto& SvcMgr = registry.ctx().emplace<qk::ServiceManager<qk::integrations::entt_service_storage>>();
		auto& SvcStg = registry.ctx().emplace<qk::integrations::entt_service_storage>(&registry);
		SvcMgr.storage = &SvcStg;
		auto& evt_queue = registry.ctx().emplace<qk::EventQueue>();
		stack.attach_queue(&evt_queue);

		// Window initialization
		window.init(qk::Window::Size{ 480, 480 }, "Demo");
		window.make_context_current();
		window.set_event_queue(&evt_queue);

		// initialize gui and gfx
		gui::init(window.handle());
		gfx::init();


		
		
		mesh.ctor();
		mesh.bind();
		mesh.m_Config.m_VertexType = typeid(glm::vec2);
		mesh.m_Config.setup = [](unsigned int& location, bool normalize, uintptr_t offset) {
			gfx::add_vertex_attribute_pointer_impl(location, 2, GL_FLOAT, normalize, sizeof(glm::vec2), offset);
			location++;
		};

		vbo = mesh.generate_vbo(points.data(), points.size(), GL_STATIC_DRAW);



		gfx::Shader vert(vertexShaderSrc, GL_VERTEX_SHADER);
		
		gfx::Shader frag(fragShaderSrc, GL_FRAGMENT_SHADER);

		program.init(frag, vert);



		


	}



	void run() override {
		
		auto& SvcMgr = registry.ctx().get<qk::ServiceManager<qk::integrations::entt_service_storage>>();

		//gui::demo();

		program.bind();

		mesh.bind();
		gfx::drawArrays(GL_TRIANGLES, 0, points.size());
		window.swap_buffers();
		window.pollEvents();
		stack.propagate_events();
		set_status(window.should_close());
		
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

