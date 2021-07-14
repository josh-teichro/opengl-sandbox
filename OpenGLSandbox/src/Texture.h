#pragma once

#include <string>

/**
* Texture API for loading textures and setting them up with OpenGL.
*/
class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	unsigned int m_id;
	std::string m_filepath;
	int m_width, m_height, m_bpp;
	unsigned char* m_localBuffer;
};

