#pragma once
#include "../qk/QKTL.h"
#include "../Core.h"
#include <GL/glew.h>
#include <typeindex>

namespace qk::gfx
{
	/// <summary>
	/// Acts as a handle to a OpenGL Uniform
	/// Lets you edit uniforms with ease, and
	/// upload them with ease
	/// </summary>
	struct QK_API Uniform
	{
		/// <summary>
		/// TODO: Make it emulate shared_ptr with ref counts and all
		/// Then, integrate into some kind of resource manager
		/// </summary>
		private:
			GLuint					m_Location = 0;
			GLuint					m_Program = 0;
			std::type_index			m_Type;
			void*					m_Data = nullptr;
			func_ptr_t<void, void*&>	m_Destructor = nullptr;

			static GLuint get_uniform_location(std::string name, GLuint program);

		public:

			GLuint get_program() const;

			GLuint get_location() const;

			operator bool() const;

			~Uniform();
			Uniform()
				: m_Location(0),
				m_Program(0),
				m_Type(typeid(void)),
				m_Data(nullptr),
				m_Destructor(nullptr)
			{
			}

			

			template <class T>
			Uniform(std::string name, GLuint program, const T& initial_value):
				m_Type(typeid(void))
			{
				GLuint location = get_uniform_location(name, program);
				m_Location = location;
				m_Program = program;
				m_Type = typeid(T);
				T* ptr = new T{};
				*ptr = initial_value;
				m_Data = ptr;
	
				m_Destructor = [](void*& handle)
				{
					if (!handle) return;
					T* item = (T*)handle;
					delete item;
					handle = nullptr;
				};
			}

			template <class T>
			bool is()
			{
				return m_Type == typeid(T);
			}
			template <class T>
			T* get()
			{
				if (!is<T>()) return nullptr;
				return (T*)m_Data;
			}
			void update();

	};


}