#include "game.h"
#include "GameLayer.h"
#include "GUILayer.h"
#include "vertex_attribute_setup.h"
#include <cmath> // for sin, cos
qk::Application* create_application(int argc, char** argv) { return new Game(argc, argv); }


// Just a reminder of what all you changed:
// Removed ImGui .cpp includes from the Client, so we can figure out why glGenBuffers is
// unresolved even though it's not being used explicitly by my code (maybe ImGui is calling it!)
// You also removed glew32s.lib from Client, since the current hypothesis is that
// GLEW's context is not persistent across DLL boundaries. 
// TODO: Change VBO::init<T> to be generic, passing void*, sizeof(T), and length...
// ...since templates like to be a pain in the ass. Why? We need that glGenBuffers call for testing, and templates like kicking my nuts

// You could also make a namespace that wraps OpenGL calls so that they CAN be exported through the DLL, eg, QK_API void qkg::glGenBuffers(...); This would slow calls down, but it would make the compiler STFU



void Game::init() {

	qk::init_SDL_GL(3, 3);

	qkg::make_window(window, 1920, 1080, "Test");


	pipeline.init(window);


	qk::init_GLEW();

	
	glDisable(GL_CULL_FACE);
	glClearColor(0, 200, 255, 255);
	glViewport(0, 0, 1920, 1080);

	

	UIcontext.init(pipeline, window);
	
	console_widget = UIcontext.add_widget(new ConsoleUI());
	


	
	
	layers.insert(new GUILayer(&UIcontext));
	layers.insert(new GameLayer());

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
		t += 0.001;
		shader_instance.set_uniform(view_location, &view, qkg::gl_primitive_type::MAT4);

		layers.render();
		layers.propagate_events();

		glDrawElements(GL_TRIANGLES, ebo.size(), GL_UNSIGNED_INT, 0);

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
