void Game::init() {

	//qk::init_SDL_GL(3, 3);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	//qkg::make_window(window, 720, 720, std::string("Test"));
	window.m_Height = 720;
	window.m_Width = 720;
	window.m_Title = "Test";
	//window.init();
	window.m_Window = SDL_CreateWindow(
		m_Title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window.m_Width,
		window.m_Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window.m_Window) {
		fprintf(stderr, "Failed to create SDL_Window: %s\n", SDL_GetError());
		exit(1);
	}

	//context.init(window);
	context.m_GLContext = SDL_GL_CreateContext(window.m_Window);
	SDL_GL_MakeCurrent(window.m_Window, m_GLContext);
	SDL_GL_SetSwapInterval(1);

	//qk::init_GLEW();
	glewExperimental = GL_TRUE;
	glewInit();


	// ImGui initialization
	UIcontext.init(context.m_GLContext, window.m_Window);

	// background color
	glClearColor(0, 200, 255, 255);
	glViewport(0, 0, 720, 720);

	// add ImGui console widget
	console_widget = UIcontext.add_widget(new ConsoleUI());

	// this definitely doesn't do anything
	layers.insert(new GUILayer(&UIcontext));
	layers.insert(new GameLayer());

	#include "test_vertices.h" // just a lil' cleaner


	qkg::VAO vao;
	vao.init();
	vao.bind();
	check_gl_error("game::init()");
	qkg::VBO vbo(vertices); // this is where the error actually happens
	// setup_vertex_attributes<vec3>::setup();


}