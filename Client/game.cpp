#include "game.h"
#include <cmath> // for sin, cos
#include "boost/pfr.hpp"


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

	//ebo.init(*mesh.m_Indices);
	//ebo.bind();
}



void Game::init() {

	qk::SDL_init_backend(3, 3);

	qkg::make_window(window, 1920, 1080, "Test");


	pipeline.init((SDL_Window*)window);


	// Initializes GLEW
	qk::SDL_init_backend_symbol_loader();

	
	glDisable(GL_CULL_FACE);
	glClearColor(0, 200, 255, 255);
	glViewport(0, 0, 1920, 1080);

	

	UIcontext.init((SDL_GLContext)pipeline, (SDL_Window*)window);
	
	console_widget = UIcontext.add_widget(new ConsoleUI());
	


	
	layers.insert(new qk::GUILayer(&UIcontext));
	layers.insert(new qk::QKBaseLayer());

	#include "test_vertices.h" // just a lil' cleaner


	qkg::MeshConfiguration<Vertex> cfg;

	qkg::MeshRegistry reg;
	reg.register_configuration(cfg);

	qkg::Mesh<Vertex> mesh;
	mesh.upload_vertices(std::move(vertices));
	mesh.upload_indices(std::move(indices));
	foo(cfg, mesh, vao, vbo, ebo);


	qkg::ShaderSources shader;
	shader.attach_shader(GL_FRAGMENT_SHADER, default_frag);
	shader.attach_shader(GL_VERTEX_SHADER, default_vert);
	shader_instance.set_program(qkg::compile_shader(shader));
	projection = camera.projection();

}




int Game::run()
{
	//todo: get a basic sine and cosine going
	
	qk::vec3 eye = { 0.0, 1.0, 1.0f }; // camera position
	qk::vec3 target = { 0.0f, 0.0f, 0.0f };              // look-at point
	qk::vec3 up = { 0.0f, 0.0f, 1.0f };              // z-up

	qk::mat4 view = glm::lookAt(eye, target, up);

	shader_instance.bind();
	GLuint proj_location = shader_instance.get_uniform_location("u_Proj");
	GLuint view_location = shader_instance.get_uniform_location("u_View");

	//glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)&projection);



	float t = 0;

	FloatPtrUnion fpu(&t);

	std::cout << fpu.get();
	t = 1.0;
	std::cout << fpu.get();


	shader_instance.set_uniform(proj_location, &projection, qkg::gl_primitive_type::MAT4);

	// main loop. Runs until there's an error code.
	while (!qk::status)
	{
		qk::vec3 eye = { sin(t), cos(t), 1.0f }; // camera position
		view = glm::lookAt(eye, target, up);
		t += 0.001f;
		shader_instance.set_uniform(view_location, &view, qkg::gl_primitive_type::MAT4);

		layers.render();
		layers.propagate_events();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//UIcontext.end();
		window.swap();
	}
	return qk::status;

}

void Game::destroy()
{
	// do nothing. 
}

// Tell the entry point to use a Game
