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




    

    

    class QK_API VertexBufferLayout {

        private:

            std::vector<VertexBufferLayoutElement> m_Elements;
            unsigned int m_Stride = 0;

        public:

            template<class T>
            void push(unsigned int count, bool normalized)
            {
                m_Elements.emplace_back(VertexBufferLayoutElement{
                    VertexAttribute_cast<T>(),
                    count,
                    normalized
                    });

                m_Stride += count * sizeof(T);
            }

    };

}