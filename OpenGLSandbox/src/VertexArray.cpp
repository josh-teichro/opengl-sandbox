#include "VertexArray.h"

/**
* Create a VertexArray.
*/
VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_id)); // create vertex array object
    Bind();
}

/**
* Destroy this VertexArray.
*/
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_id));
}

/**
* Add a VertexBuffer to OpenGL, that is tied to this VertexArray. That is, after
* having added the VertexBuffer, you will no longer need to bind it or set it's 
* layout, rather you will only need to bind this VertexArray.
*
* vb: VertexBuffer to add
* layout: defines the layout of attributes in the VertexBuffer
*/
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const auto& attributes = layout.GetAttributes();
    unsigned int offset = 0;

    for (int i = 0; i < attributes.size(); i++)
    {
        const auto& attribute = attributes[i];

        GLCall(glEnableVertexAttribArray(i)); // 
        GLCall(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, layout.GetStride(), (const void*)offset));
        offset += attribute.GetSize();
    }
}

/**
* Bind this VertexArray so that it can be drawn or modified.
*/
void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_id));
}

/**
* Unbind this (or any) VertexArray.
*/
void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
