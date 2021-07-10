#pragma once

/**
* Stores vertex data in OpenGL so that it can be rendered.
*
* Use this along with a VertexArray so that OpenGL knows how the data is laid out.
*/
class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_id;
};

