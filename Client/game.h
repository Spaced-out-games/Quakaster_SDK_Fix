#include <Quakaster.h>

#include <Quakaster/qk/defaults.h> //GUILayer.h>
#include <Quakaster/qkg/qkg.h>
#include <Quakaster/qkg/defaults.h>
#include <Quakaster/qkg/GL/MeshRegistry.h>
#include <Quakaster/qkui/Widgets/ConsoleUI.h>
#include <Quakaster/qkmath/CCamera.h>
#include "Quakaster/qk/QKTL.h"
#include <Quakaster/qkecs/Scene.h>
#include <Quakaster/qkecs/Entity.h>
#include <Quakaster/qkmath/CTransform.h>
#include <Quakaster/qkkernel/kernel.h>

namespace cl
{
	float fov_desired = 130.0f;
	float r_near = 0.0001f;
	float r_far = 1000.0f;
	float r_aspect_ratio = 16.0f / 9.0f;
}

struct Game : public qk::Application {

	//private: keep it public while im debugging
		qk::kernel::Kernel kernel;
		qkg::Window window;
		qk::Scene scene;
		qkg::GraphicsPipeline pipeline;
		qk::LayerStack layers;
		qkui::UIContext UIcontext;
		uint8_t console_widget = 0;
		//qk::mat4 projection = qk::mat4{ 1.0f };
		//qkg::VAO vao;
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		qkg::ShaderInstance shader_instance;
		//qk::CCamera camera;
	public:
		Game(int argc, char** argv) : Application(argc, argv) {}
		~Game() {}

		void init() override;
		
		int run() override;
		
		void destroy() override;
};