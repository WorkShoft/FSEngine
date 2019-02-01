#include "pch.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace FSEngine {

Texture::Texture(int width, int height, int levels)
{
	createTexture(width, height, levels);
}

Texture::Texture(const textureData_t &data, int l) : m_data(data)
{
	createTexture(data.width, data.height, l);
	subImage(0, 0, 0, data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::makeActive(int bank) const
{
	glBindTextureUnit(bank, m_id);
}

void Texture::subImage(int level, int offsetX, int offsetY, const textureData_t &data)
{
	m_data = data;
	glTextureSubImage2D(m_id, level, offsetX, offsetY, data.width, data.height, GL_RGBA, GL_UNSIGNED_BYTE, data.data);
}

void Texture::createTexture(int width, int height, int l)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_id); //No need for other tex types as it's a 2D engine
	glTextureStorage2D(m_id, l, GL_RGBA8, width, height);
	glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

textureData_t Texture::LoadTextureData(const std::string &path)
{
	textureData_t data;
	data.data = stbi_load(path.c_str(), &data.width, &data.height, &data.components, STBI_rgb_alpha);
	if(!data.data) {
		FSE_ERROR("Failed to load texture {0}", stbi_failure_reason());
	}
	return data;
}

void Texture::DestroyTextureData(const textureData_t &data)
{
	stbi_image_free(data.data);
}

}