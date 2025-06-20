#include "LevelLayer.h"

LevelLayer::~LevelLayer()
{

}


LevelLayer::LevelLayer()
{

}

void LevelLayer::on_attach()
{
	// create the test mesh
}
bool LevelLayer::on_event(const SDL_Event& evt)
{
	// for now, do nothing and passthrough
	return 0;
}
void LevelLayer::on_detach()
{
	// do nothing, again
}

void LevelLayer::render()
{
	// render the test mesh
}