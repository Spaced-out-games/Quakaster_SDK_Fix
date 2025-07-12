#include "QKBaseLayer.h"


namespace qk
{

	QKBaseLayer::~QKBaseLayer()
	{

	}


	QKBaseLayer::QKBaseLayer()
	{

	}

	void QKBaseLayer::on_attach()
	{

	}
	bool QKBaseLayer::on_event(const SDL_Event& evt)
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			qk::status = 1;
			return true;

		case SDL_KEYDOWN:
			if (evt.key.keysym.sym == SDLK_ESCAPE)
			{
				// Here, we'd invoke the console, but for now, just quit
				qk::status = 1;
				return true;
			}
			break;

		default:
			break;
		}
		return false; // Ensure every code path returns
	}
	void QKBaseLayer::on_detach()
	{

	}

	void QKBaseLayer::render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

}