#include "GraphicsPrimitiveService.h"
#include "GL/glew.h"

namespace gfx {


    void drawArrays(unsigned int mode, int first, int count) {
        glDrawArrays(mode, first, (GLsizei)count);

    }


}