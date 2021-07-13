#pragma once

#include "Core.h"
#include <vector>

/**
* Holds info on a single attribute that is stored in a VertexBuffer.
*/
struct VertexBufferAttribute
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	/**
	* Get the size of this attribute.
	*/
	unsigned int GetSize() const
	{
		switch (type)
		{
			case GL_FLOAT: return count * sizeof(GLfloat);
			case GL_UNSIGNED_INT: return count * sizeof(GLuint);
			case GL_UNSIGNED_SHORT: return count * sizeof(GLushort);
			case GL_UNSIGNED_BYTE: return count * sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

/**
* Defines the layout of a VertexBuffer.
*/
class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_stride(0) {};

	inline std::vector<VertexBufferAttribute> GetAttributes() const { return m_attributes; }
	inline unsigned int GetStride() const { return m_stride;  }

	/**
	* Add an attribute to the end of this layout, with type T.
	*
	* count: number of elements in the vector (should be 1, 2, 3, or 4 as per OpenGL docs)
	*/
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		VertexBufferAttribute attr = { count, GL_FLOAT, GL_TRUE };
		m_attributes.push_back(attr);
		m_stride += attr.GetSize();
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		VertexBufferAttribute attr = { count, GL_UNSIGNED_INT, GL_TRUE };
		m_attributes.push_back(attr);
		m_stride += attr.GetSize();
	}

	template<>
	void Push<unsigned short>(unsigned int count)
	{
		VertexBufferAttribute attr = { count, GL_UNSIGNED_SHORT, GL_TRUE };
		m_attributes.push_back(attr);
		m_stride += attr.GetSize();
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		VertexBufferAttribute attr = { count, GL_UNSIGNED_BYTE, GL_TRUE };
		m_attributes.push_back(attr);
		m_stride += attr.GetSize();
	}

private:
	std::vector<VertexBufferAttribute> m_attributes;
	unsigned int m_stride;
};
