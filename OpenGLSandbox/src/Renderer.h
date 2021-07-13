#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/**
* Renderer class.
*/
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};
