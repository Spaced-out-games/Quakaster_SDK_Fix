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

#include <Quakaster/qkgfx/gfx.h>
#include <Quakaster/qkgfx/Window.h>
#include <Quakaster/qkgfx/gfx-Context.h>
#include <Quakaster/qkkernel/kernel.h>
#include <Quakaster/qkkernel/KShell.h>
#include <Quakaster/qkkernel/KBuiltinModule.h>
#include <Quakaster/qkui/UIContext.h>
#include <Quakaster/qkui/Widgets/ConsoleUI.h>

namespace cl
{
	float fov_desired = 130.0f;
	float r_near = 0.0001f;
	float r_far = 1000.0f;
	float r_aspect_ratio = 16.0f / 9.0f;
}

struct Game : public qk::Application {

	//private: keep it public while im debugging
	qk::gfx::Window m_Window;
	qk::gfx::Context m_Context;
	qk::kernel::Kernel kernel;
	qk::kernel::KShell shell;
	qk::ui::UIContext  UIContext;
	
	public:
		Game(int argc, char** argv) : Application(argc, argv) {}
		~Game() {}

		void init() override;
		
		int run() override;
		
		void destroy() override;
};