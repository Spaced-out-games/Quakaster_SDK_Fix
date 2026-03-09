#pragma once
#include "../core.h"
#include "VertexBuffer.h"
//#include "VertexArray.h"
#include <vector>
#include <cassert>
#include "types.h"
#include "GL/glew.h"
namespace gfx
{





    struct VertexBufferLayoutElement {
        VertexAttribute type;
        unsigned int count;
        bool normalized;
    };


    unsigned int get_attribute_size(VertexAttribute attribute) {
        switch (attribute)
        {
            case GL_FLOAT:
                return sizeof(float);
            case GL_INT:
                return sizeof(int);
            case GL_UNSIGNED_BYTE:
                return sizeof(unsigned char);

        default:
            __debugbreak();
            return 0;
            break;
        }
        return 0;
    }

    

    

    class VertexBufferLayout {

        private:
            friend class VertexArray;
            template <class vertex_t>
            friend class VertexBuffer;
            std::vector<VertexBufferLayoutElement> m_Elements;
            unsigned int m_Stride = 0;

        public:

            template<class T>
            void push(unsigned int count, bool normalized = false)
            {
                m_Elements.emplace_back(VertexBufferLayoutElement{
                    VertexAttribute_cast<T>(),
                    count,
                    normalized
                    });

                m_Stride += count * sizeof(T);
            }

            unsigned int stride() {
                return m_Stride;
            }

    };

}