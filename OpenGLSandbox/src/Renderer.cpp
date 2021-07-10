#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR] (" << error << ") " <<
            function << " " << file << ":" << line << std::endl;
        return true;
    }

    return false;
}
