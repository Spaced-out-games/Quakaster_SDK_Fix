#include "game.h"
#include "vertex_attribute_setup.h"
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
	vec3 p;
	vec3 n;
};


void Game::init() {
	Vertex v = { {0,0,0}, {1,1,1} };
	auto field_count = boost::pfr::get<0>(v);
	std::cout << field_count.x;

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


	vao.init();
	vao.bind();


	vbo.init(vertices);
	vbo.bind();
	setup_vertex_attributes<vec3>::setup();

	ebo.init(indices);
	ebo.bind();

	qkg::Shader shader;
	shader.attach_shader(GL_FRAGMENT_SHADER, default_frag);
	shader.attach_shader(GL_VERTEX_SHADER, default_vert);
	shader_instance.set_program(qkg::compile_shader(shader));


	//camera.set_aspect(16.0f / 9.0f);
	//camera.set_fov(100.0f);
	//camera.set_near(0.001f);
	//camera.set_far(1000.0f);
	projection = camera.projection();

}




int Game::run()
{
	//todo: get a basic sine and cosine going
	
	vec3 eye = { 0.0, 1.0, 1.0f }; // camera position
	vec3 target = { 0.0f, 0.0f, 0.0f };              // look-at point
	vec3 up = { 0.0f, 0.0f, 1.0f };              // z-up

	glm::mat4 view = glm::lookAt(eye, target, up);

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
		vec3 eye = { sin(t), cos(t), 1.0f }; // camera position
		view = glm::lookAt(eye, target, up);
		t += 0.001f;
		shader_instance.set_uniform(view_location, &view, qkg::gl_primitive_type::MAT4);

		layers.render();
		layers.propagate_events();
		glDrawElements(GL_TRIANGLES, (GLsizei)ebo.size(), GL_UNSIGNED_INT, 0);

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
