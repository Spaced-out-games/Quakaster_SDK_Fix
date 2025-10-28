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
#include <Quakaster/qkkernel-new/Token.h>
#include <Quakaster/qkkernel-new/kernel.h>
#include <Quakaster/qkkernel-new/Tokenizer.h>


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


int echo_cmd(Kernel& kernel, std::span<const Token> args)
{
	// try checking stdin, print that...
	if (!kernel.m_stdin.empty())
	{
		kernel.m_Console << kernel.m_stdin;
		kernel.m_stdin = NullToken{};
	}
	// cout out the arguments
	for (const Token& tk : args)
	{
		// if stdout is empty, anything can populate it
		if (kernel.m_stdout.empty())
		{
			kernel.m_stdout = tk.resolve(kernel);
		}
		// if not empty, normalize it to string and append
		else
		{
			// normalize
			if (!kernel.m_stdout.is<StringToken>())
			{
				StringToken stk{ (std::string)kernel.m_stdout };
				kernel.m_stdout = stk;
			}
			else
			{
				kernel.m_stdout.as<StringToken>() += (std::string)tk.resolve(kernel);
			}
		}

	}
	//kernel.m_Console << kernel.m_stdout;
	//kernel.m_stdout = NullToken{};

	return 0;
}

int typeof_cmd(Kernel& kernel, std::span<const Token> args)
{
	const Token& input = !kernel.m_stdin.empty() ? kernel.m_stdin : (args.empty() ? NullToken{} : args[0]);
	std::string out;

	if (input.is<IntToken>()) out = "<int>";
	else if (input.is<FloatToken>()) out = "<float>";
	else if (input.is<StringToken>()) out = "<string>";
	//else if (input.is<ProgramToken>()) out = "<exec>";
	else if (input.is<IdentifierToken>()) out = "<var>";
	else if (input.is<NullToken>()) out = "<null>";
	else out = "<?>";

	kernel.m_stdout = StringToken{ out };
	kernel.m_stdin = NullToken{};  // clear stdin after use
	return 0;
}

int wc_cmd(Kernel& kernel, std::span<const Token> args)
{
	if (kernel.m_stdin.empty())
	{
		kernel.m_stdout = StringToken{ "0" };
	}
	std::string repr = (std::string)kernel.m_stdin;
	kernel.m_stdout = StringToken{ std::to_string(repr.size())};
	
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
			kernel.m_stdout = qk::kernel::tokenize(args[0].as<StringToken>());
		else
			kernel.m_stdout = StringToken{ "Expected a source string" };

	}
	else
	{
		kernel.m_stdout = StringToken{ "Expected a source string" };


	}
	return 0;
}




int Game::run()
{

	Kernel k;
	k.register_fn("echo"_hs, &echo_cmd);
	k.register_fn("typeof"_hs, &typeof_cmd);
	k.register_fn("wc"_hs, &wc_cmd);
	k.register_fn("compile"_hs, &compile_cmd);


	//k.run
	//(
	//	32.0f, '|', "$HI"_id, ';',
	//	"$HI"_id, '|', "wc"_cmd, ';'
		//"echo"_cmd, "$HI"_id
	//);

	std::string source = "compile 'echo \"hi\"' | $T; $T";
	auto tokens = qk::kernel::tokenize(source);
	
	k.run_program(tokens);

	//bool success = k.get_env("T"_hs.value()).is<Program>();

	//std::cout << success;

	std::cout << k;



	//k.print(k.get_env("T"_hs.value()).is<Program>());



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
