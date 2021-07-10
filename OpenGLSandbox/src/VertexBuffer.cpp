#include "VertexBuffer.h"
#include "Renderer.h"

/**
* Create a VertexBuffer. This will also bind the buffer so that it can be used, as long as no other 
* buffer is created/binded afterwards.
*
* data: a pointer to the data that will be used to render
* size: size of data in bytes
*/
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_id));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

/**
* Destroy the VertexBuffer.
*/
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_id));
}

/**
* Bind this VertexBuffer so that it can be drawn or modified.
*/
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

/**
* Unbind this (or any) VertexBuffer.
*/
void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
