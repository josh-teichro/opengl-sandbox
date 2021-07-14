#include "Texture.h"
#include "Core.h"
#include "stb_image/stb_image.h"

/**
* Create and load a Texture.
*
* This does not bind the Texture, since Textures must be bound to specific slots.
*
* filepath: path to the texture to load
*/
Texture::Texture(const std::string& filepath) :
	m_id(0), m_filepath(filepath), 
	m_width(0), m_height(0), 
	m_bpp(0), m_localBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(true);
	m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

	GLCall(glGenTextures(1, &m_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

/**
* Destroy this Texture.
*/
Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_id));
}

/**
* Bind this Texture to the given slot.
*
* slot: slot to bind texture to (typically a GPU will have 16 slots, phones maybe 8, etc.)
*/
void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

/**
* Unbind this Texture.
*/
void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
