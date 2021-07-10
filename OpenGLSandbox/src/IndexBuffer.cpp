#include "IndexBuffer.h"
#include "Renderer.h"

/**
* Create an IndexBuffer.
*
* data: a pointer to the data that holds the indeces to render
* count: number of indeces (indeces are assumed to be stored as unsigned ints
*/
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_id));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

/**
* Destroy this IndexBuffer.
*/
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_id));
}

/**
* Bind this IndexBuffer so that it can be drawn or modified.
*/
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

/**
* Unbind this (or any) IndexBuffer.
*/
void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
