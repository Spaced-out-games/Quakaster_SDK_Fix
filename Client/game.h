#include <Quakaster.h>


struct Game : public qk::Application {

	//private: keep it public while im debugging
		qkg::Window window;
		qkg::Context context;
		qk::LayerStack layers;
		qkui::UIContext UIcontext;
		uint8_t console_widget = 0;
		qkg::VAO vao;
		qkg::VBO vbo;
		qkg::EBO ebo;
	public:
		Game(int argc, char** argv) : Application(argc, argv) {}
		~Game() {}

		void init() override;
		
		int run() override;
		
		void destroy() override;
};