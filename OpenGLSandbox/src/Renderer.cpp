#include "Renderer.h"
#include "Core.h"

/**
* Create a Renderer.
*/
Renderer::Renderer()
{
}

/**
* Destroy this Renderer.
*/
Renderer::~Renderer()
{
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // hardcoded to uint for now (see IndexBuffer)
}
