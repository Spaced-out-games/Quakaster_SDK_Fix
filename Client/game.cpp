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
#include <Quakaster/qkkernel/Kernel.h>
#include <Quakaster/qkkernel/commands/kernel_core.h>
#include <Quakaster/qkkernel/Token.h>


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





int Game::run()
{
	std::string source = "";
	Kernel* kernel = new Kernel();
	std::unique_ptr<Program> program;
	kernel->register_fn("echo", &qk::kernel::echo);
	kernel->register_fn("cd", &qk::kernel::cd);
	kernel->register_fn("pwd", &qk::kernel::pwd);
	kernel->register_fn("clear", &qk::kernel::clear);
	kernel->register_fn("wc", &qk::kernel::wc);
	kernel->register_fn("exit", &qk::kernel::exit);
	kernel->register_fn("wf", &qk::kernel::wf);
	kernel->register_fn("cat", &qk::kernel::cat);
	kernel->register_fn("set", &qk::kernel::set);
	kernel->register_fn("run", &qk::kernel::run);








	while (!kernel->m_Status)
	{
		std::getline(std::cin, source);

		program = compile(std::move(source));

		kernel->run(program.get());
	}

	return kernel->m_Status;
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
