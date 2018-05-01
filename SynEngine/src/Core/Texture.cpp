#include "..\..\include\SynEngine\Core\Texture.hpp"
#include <iostream>

SynEngine::Texture::Texture()
{
}

SynEngine::Texture::~Texture()
{
	delete[] data;
}

void SynEngine::Texture::LoadTexture()
{
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	printf("Texture id: %u\n", id);
}
