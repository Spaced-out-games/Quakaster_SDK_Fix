#include <Quakaster.h>


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
		Game(int argc, char** argv) : Application(argc, argv) {}
		~Game() {}

		void init() override;
		
		int run() override;
		
		void destroy() override;
};