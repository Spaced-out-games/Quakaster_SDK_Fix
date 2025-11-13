#include "game.h"
#include <cmath> // for sin, cos
#include "boost/pfr.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cstdint>

//temporary includes
#include <Quakaster/qkecs/AActor.h>
#include <entt/core/hashed_string.hpp>
#include <Quakaster/qkgfx/ShaderSource.h>
#include <Quakaster/qkgfx/Uniform.h>
#include <Quakaster/qkgfx/gfx-asm.h>

ImGuiContext* make_imgui_context()
{
	IMGUI_CHECKVERSION();
	ImGuiContext* result = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Optional: configure flags
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows
	return result;
}



using namespace entt::literals;

using namespace qk::kernel;

using namespace qk;


qk::Application* create_application(int argc, char** argv) { return new Game(argc, argv); }


struct Vertex
{
	qk::vec3 p;
};

/* TODO: set up proper error systems for:
	Window
	GraphicsPipeline
	UIContext
	GUILayer
	QKBaseLayer




template <class vertex_t>
void foo(
	qkg::MeshConfiguration<vertex_t>& configuration,
	const qkg::Mesh<vertex_t>& mesh,
	GLuint& vao,
	GLuint& vbo,
	GLuint& ebo
) {

	vao = qkg::vao::create();
	qkg::vao::bind(vao);

	vbo = qkg::vbo::create();
	qkg::vbo::bind(vbo);
	qkg::vbo::upload_vertices(vbo, *mesh.m_Vertices, GL_STATIC_DRAW);

	configuration.setup();
	ebo = qkg::ebo::create();
	qkg::ebo::bind(ebo);
	qkg::ebo::upload_indices(*mesh.m_Indices);


}

*/

using namespace qk::gfx;



void Game::init() {

	qk::gfx::Result err = qk::gfx::init_SDL();



	

	// Initialize SDL, GLEW, make a window
	if (!err)
	{
		std::cout << qk::gfx::to_string(err.as<qk::gfx::Error>());
		std::cout << " SDL2 failed to initialize";
		exit(1);
	}
	err = m_Window.init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 1080, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!err)
	{
		std::cout << qk::gfx::to_string(err.as<qk::gfx::Error>());
		std::cout << " Window failed to initialize";
		exit(2);
	}
	err = m_Context.init(m_Window);
	if (!err)
	{
		std::cout << qk::gfx::to_string(err.as<qk::gfx::Error>());
		std::cout << " gfx failed to initialize";
		exit(3);
	}

	err = qk::gfx::init_GLEW();
	if (!err)
	{
		std::cout << qk::gfx::to_string(err.as<qk::gfx::Error>());
		std::cout << " glew failed to initialize";
		exit(3);
	}
	

	// set up ImGui
	UIContext.init(make_imgui_context(), m_Context, m_Window);
	auto console = new qk::ui::ConsoleUI();
	//console->bind_shell(&shell);
	UIContext.add_widget(console);

	// Create an ImGui context.


	// bind it to the window and OpenGL
	//if (!ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context)) {
		// Handle error: SDL backend init failed
	//}



	// Set up the kernel and shell
	qk::kernel::bind(kernel, *console, console->oss);
	kernel.mount<KBuiltinModule>("Core", SSID{ 0 });


}
/*
template <typename ...arg_Ts>
inline void add_camera(qk::Entity& target, arg_Ts... args)
{
	target.get_or_emplace<qk::CTransform>();
	target.get_or_emplace<qk::mat4>();
	target.get_or_emplace<qk::CCamera>(std::forward<arg_Ts>(args)...);

}*/





// consider making run_program output a result string instead of printing, then do it at the terminator (with a newline as well?)
// TODO: Fix old infrustructure to handle kernel* being nul
int Game::run()
{
	qk::gfx::VAO_policy vertex_policy = qk::gfx::make_VAO_policy<Vertex>();

	qk::gfx::Error err;

	qk::gfx::VAO vao;
	vao.init();
	vao.bind();

	qk::gfx::VM vm;

	
	#include "test_vertices.h"

	qk::gfx::VBO vbo;
	vbo.init();
	vbo.bind();
	vbo.upload_vertices(vertices, GL_STATIC_DRAW);
	
	vertex_policy();


	qk::gfx::EBO ebo;
	ebo.init();
	ebo.bind();
	ebo.upload(indices.data(), indices.size(), GL_STATIC_DRAW);



	std::vector<GLuint> programs;
	
	programs.push_back(qk::gfx::compile_source(default_frag, GL_FRAGMENT_SHADER, &err));
	std::cout << err;
	programs.push_back(qk::gfx::compile_source(default_vert, GL_VERTEX_SHADER, &err));
	std::cout << err;

	GLuint shader = qk::gfx::link_sources(programs, &err);
	std::cout << err;

	qk::gfx::use_shader(shader);


	qk::gfx::RenderPass rp;
	rp.set_clear_color(0.0f, 1.0f, 0.0f, 1.0f)
		.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
		.bind_vertex_object(vao)
		.draw_vertex_object(GL_TRIANGLES, ebo.m_IndexCount, GL_UNSIGNED_INT, 0);
		//;
	
	kernel.print(rp.to_string());


	SDL_Event event;

	//glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 100.0f);
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -3.0f));

	//qk::gfx::Uniform<qk::mat4> view("u_View", shader);
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -3.0f));

	qk::gfx::Uniform uView("u_View", shader, view);
	qk::gfx::Uniform uProj("u_Proj", shader, proj);


	while (true)
	{
		
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event); // <--- this is key
			if (event.type == SDL_QUIT)
				exit(0);
		}
		//m_Context.clear(0.0, 1.0, 0.0, 1.0);
		uView.update();
		uProj.update();


		vm.call(&rp);

		UIContext.begin();
		UIContext.draw();
		UIContext.end();


		

		//shell.tick();
		m_Window.swap();

	}


	return 0;// kernel->m_Status;

	
}


/* old
int Game::run()
{




	//todo: get a basic sine and cosine going
	
	qk::Entity camera(scene);
	add_camera(camera, &cl::fov_desired, &cl::r_aspect_ratio, &cl::r_near, &cl::r_far);


	qk::vec3 eye = { 0.0, 1.0, 1.0f }; // camera position
	qk::vec3 target = { 0.0f, 0.0f, 0.0f };              // look-at point
	qk::vec3 up = { 0.0f, 0.0f, 1.0f };              // z-up


	//qk::mat4 view = glm::lookAt(eye, target, up);

	camera.get<qk::mat4>() = glm::lookAt(eye, target, up);


	shader_instance.bind();
	GLuint proj_location = shader_instance.get_uniform_location("u_Proj");
	GLuint view_location = shader_instance.get_uniform_location("u_View");

	//glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)&projection);



	float t = 0;



	qk::mat4 projection = camera.get<qk::CCamera>().projection();

	shader_instance.set_uniform(proj_location, &projection, qkg::gl_primitive_type::MAT4);
	SDL_Event evt;
	Event e;
	// main loop. Runs until there's an error code.
	while (!qk::status)
	{
	begin:
		goto end;
		qk::vec3 eye = { sin(t), cos(t), 1.0f };
		camera.get<qk::mat4>() = glm::lookAt(eye, target, up);
		t += 0.001f;
		shader_instance.set_uniform(view_location, &camera.get<qk::mat4>(), qkg::gl_primitive_type::MAT4);

		layers.render();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		window.swap();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	return qk::status;

}
*/

void Game::destroy()
{
	// do nothing. 
}
