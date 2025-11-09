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
//#include <Quakaster/qkkernel/Kernel.h>
//#include <Quakaster/qkkernel/kernel_core_subsystem.h>
#include <Quakaster/qkkernel/kernel.h>
#include <Quakaster/qkkernel/KShell.h>
#include <Quakaster/qkkernel/KBuiltinModule.h>
//#include <Quakaster/qkgfx/gfx-init.h>
//#include <Quakaster/qkgfx/gfx-window.h>
//#include <Quakaster/qkgfx/gfx-api.h>



using namespace entt::literals;

using namespace qk::kernel;


qk::Application* create_application(int argc, char** argv) { return new Game(argc, argv); }


/* TODO: set up proper error systems for:
	Window
	GraphicsPipeline
	UIContext
	GUILayer
	QKBaseLayer

*/

struct Vertex
{
	qk::vec3 p;
};

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



void Game::init() {
	window.init();
	pipeline.init(window);
}

template <typename ...arg_Ts>
inline void add_camera(qk::Entity& target, arg_Ts... args)
{
	target.get_or_emplace<qk::CTransform>();
	target.get_or_emplace<qk::mat4>();
	target.get_or_emplace<qk::CCamera>(std::forward<arg_Ts>(args)...);

}





// consider making run_program output a result string instead of printing, then do it at the terminator (with a newline as well?)
// TODO: Fix old infrustructure to handle kernel* being nul
int Game::run()
{
	
	Kernel k;
	KShell sh;
	qk::kernel::bind(k, sh, std::cout);
	//k.mount<KBuiltinModule>("Core", SSID{0});
	
	
	/*
	qk::gfx::platform::Window window;
	qk::gfx::Context context;

	if (qk::gfx::platform::init())
	{
		k.print("SDL2 failed to initialize");
		exit(1);
	}
	


	if (window.init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN))
	{
		k.print("Window failed to initialize");
		exit(2);
	}
	if (context.init(window))
	{
		k.print("gfx failed to initialize");
		exit(3);
	}
	if (qk::gfx::loader::load())
	{
		k.print("glew failed to initialize");
		exit(3);
	}
	*/

	while (true)
	{
		
		//context.clear(0.0, 1.0, 0.0, 1.0);
		//window.swap();
		sh.tick();
	}


	return 0;// kernel->m_Status;

	
}

/*
	Current problem: Window isn't clearing the right color. Perhaps types are wrong, or there's DLL fuckery

*/


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
