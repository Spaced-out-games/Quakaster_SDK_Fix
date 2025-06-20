#pragma once
#include <Quakaster.h>

template <class T>
struct setup_vertex_attributes
{
	static void setup();
};

template <>
void setup_vertex_attributes<vec3>::setup()
{
	GLuint index = 0;
	qkg::add_vec3_pointer(index, sizeof(vec3), 0);
}