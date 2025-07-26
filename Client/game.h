#include <Quakaster.h>

#include <Quakaster/qk/defaults.h> //GUILayer.h>
#include <Quakaster/qkg/qkg.h>
#include <Quakaster/qkg/defaults.h>
#include <Quakaster/qkg/GL/MeshRegistry.h>
#include <Quakaster/qkui/Widgets/ConsoleUI.h>
namespace cl
{
	float fov_desired = 70.0f;
	float r_near = 0.0001f;
	float r_far = 1000.0f;
	float r_aspect_ratio = 16.0f / 9.0f;
}

struct Game : public qk::Application {

	//private: keep it public while im debugging
		qkg::Window window;
		qkg::GraphicsPipeline pipeline;
		qk::LayerStack layers;
		qkui::UIContext UIcontext;
		uint8_t console_widget = 0;
		mat4 projection = mat4{ 1.0f };
		qkg::VAO vao;
		qkg::VBO vbo;
		qkg::EBO ebo;
		qkg::ShaderInstance shader_instance;
		qk::Camera camera;
	public:
		Game(int argc, char** argv) : Application(argc, argv), camera(&cl::fov_desired, &cl::r_aspect_ratio,&cl::r_near, &cl::r_far) {}
		~Game() {}

		void init() override;
		
		int run() override;
		
		void destroy() override;
};