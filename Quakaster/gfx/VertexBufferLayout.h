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


    unsigned int get_attribute_size(VertexAttribute attribute);

    

    

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