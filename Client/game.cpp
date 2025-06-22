#include "game.h"
#include "GameLayer.h"
#include "GUILayer.h"
#include "vertex_attribute_setup.h"
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

	qkg::make_window(window, 720, 720, "Test");


	pipeline.init(window);


	qk::init_GLEW();



	glClearColor(0, 200, 255, 255);
	glViewport(0, 0, 720, 720);



	UIcontext.init(pipeline, window);
	
	console_widget = UIcontext.add_widget(new ConsoleUI());
	



	
	
	layers.insert(new GUILayer(&UIcontext));
	//layers.insert(new GameLayer());

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




}




int Game::run()
{
	

	shader_instance.bind();


	// main loop. Runs until there's an error code.
	while (!qk::status)
	{
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
