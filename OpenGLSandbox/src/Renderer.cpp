#include "Renderer.h"
#include "Core.h"

/**
* Create a Renderer.
*/
Renderer::Renderer()
{
    // Setup blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

/**
* Destroy this Renderer.
*/
Renderer::~Renderer()
{
}

void Renderer::Clear()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // hardcoded to uint for now (see IndexBuffer)
}
