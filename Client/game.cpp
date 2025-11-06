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
#include <Quakaster/qkkernel/KTerminalModule.h>


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


int typeof_cmd(Kernel& kernel, std::span<const Token> args)
{
	const Token& input = !kernel.m_stdin.empty() ? kernel.m_stdin : (args.empty() ? NullToken{} : args[0]);
	std::string out;

	if (input.is<IntToken>()) out = "<int>";
	else if (input.is<FloatToken>()) out = "<float>";
	else if (input.is<StringToken>()) out = "<string>";
	//else if (input.is<ProgramToken>()) out = "<exec>";
	else if (input.is<IdentifierToken>()) out = input.resolve(kernel).type_str();
	else if (input.is<NullToken>()) out = "<null>";
	else if (input.is<Program>()) out = "<script>";
	else out = "<?>";

	kernel.m_stdout = StringToken{ out };
	kernel.m_stdin = NullToken{};  // clear stdin after use
	return 0;
}

int wc_cmd(Kernel& kernel, std::span<const Token> args)
{
	// early exit
	if (kernel.m_stdin.empty())
	{
		kernel.m_stdout = StringToken{ "0" };
		return 0;
	}


	bool print_cc = false;
	bool print_wc = false;
	bool print_lc = false;
	for (auto& arg : args)
	{
		if (arg.is<FlagToken>())
		{
			if (arg.as<FlagToken>().has('c'))
				print_cc = true;
			if (arg.as<FlagToken>().has('w'))
				print_wc = true;
			if (arg.as<FlagToken>().has('l'))
				print_lc = true;
		}
	}

	// no mutation occured
	if (!print_cc && !print_wc && !print_lc)
	{
		print_cc = 1;
		print_wc = 1;
		print_lc = 1;
	}


	std::string repr = kernel.m_stdin.print_str();

	size_t cc = repr.size();
	size_t wc = 0;
	size_t lc = 1;
	bool in_word = false;

	for (char c : repr)
	{
		if (c == '\n') lc++;
		if (c == ' ' || c == '\t')
			in_word = false;
		else
		{
			if(!in_word)
				wc++;
			in_word = true;
		}
	}

	StringToken out{ "" };

	if(print_cc)
		out += std::to_string(cc) + " ";
	if (print_wc)
		out += std::to_string(wc) + " ";
	if (print_lc)
		out += std::to_string(lc) + " ";
	kernel.m_stdout = out;
	return 0;
}

int compile_cmd(Kernel& kernel, std::span<const Token> args)
{
	if (args.size() == 0)
	{
		kernel.m_stdout = StringToken{ "No arguments provided!" };
	}
	else if (args.size() == 1)
	{
		if (args[0].is<StringToken>())
		{
			// make a string_view; make tokenizer use a string_view
			kernel.m_stdout = qk::kernel::tokenize(args[0].as<StringToken>());
		}
		else
			kernel.m_stdout = StringToken{ "Expected a source string" };

	}
	else
	{
		kernel.m_stdout = StringToken{ "Too many arguments in command 'compile'" };


	}
	return 0;
}
int cd_cmd(Kernel& kernel, std::span<const Token> args)
{
	if (args.size() == 0) return 0;
	if (args.size() == 1)
	{
		if (args[0].is<StringToken>()) kernel.m_Cd += args[0].as<StringToken>();
		if (args[0].is<IdentifierToken>()) kernel.m_Cd += args[0].as<IdentifierToken>().data();

	}
	else if (args.size() > 1)
	{
		kernel.m_stdout = StringToken{"Too many arguments in command 'echo'"};
	}
	return 0;
}


// consider making run_program output a result string instead of printing, then do it at the terminator (with a newline as well?)
// TODO: Fix old infrustructure to handle kernel* being nul
int Game::run()
{
	
	Kernel k;
	KShell sh;


	qk::kernel::bind(k, sh, std::cout);


	k.register_fn("compile", &compile_cmd);
	k.register_fn("typeof", &typeof_cmd);
	k.register_fn("wc", &wc_cmd);
	k.register_fn("cd", &cd_cmd);

	k.mount<KTerminalModule>("Core", SSID{0});

	while (true)
	{
		sh.tick();
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
