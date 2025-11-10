#pragma once
#include "../Core.h"
#include <GL/glew.h>


namespace qk::gfx
{
	class QK_API VAO
	{
		GLuint m_vao = 0;
		public:
			// Make sure to call init()!
		 	 VAO();

			 // Make sure you called init() beforehand!
			 VAO(GLuint ID);

			~VAO();

			// Actually initialize it
			void init();

			void bind();

			static void unbind();

			// Manually destroys the VAO
			void destroy();

			// Backwards compatability
			operator GLuint();

	};
}