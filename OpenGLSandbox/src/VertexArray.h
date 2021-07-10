#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
* Provides an API through which you can add a VertexBuffer with a layout to 
* OpenGL without having to further worry about binding the VertexBuffer or
* setting layout.
*/
class VertexArray
{
public: 
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_id;
};

