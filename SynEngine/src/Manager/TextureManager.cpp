#include "..\..\include\SynEngine\Managers\TextureManager.hpp"
#include "..\..\include\SynEngine\Engine.hpp"

SynEngine::TexutreManager::TexutreManager()
{
	ilInit();
}

SynEngine::TexutreManager::~TexutreManager()
{
}

SynEngine::Texture * SynEngine::TexutreManager::LoadTexture(const char* path)
{
	if (ilLoadImage(path) == IL_FALSE) {
		printf("IL error: %s\n", ilGetError());
		return nullptr;
	}

	ILint channels = ilGetInteger(IL_IMAGE_CHANNELS);
	if (channels > 3) {
		printf("ERROR: Channels: %d. Too much channel. Can't handle alpha channel.\n", channels);
		return nullptr;
	}
	ILubyte* data = ilGetData();
	ILint width = ilGetInteger(IL_IMAGE_WIDTH);
	ILint height = ilGetInteger(IL_IMAGE_HEIGHT);

	int dataPixelCount = width * height;

	Texture* texture = new Texture();
	texture->height = height;
	texture->width = width;
	texture->channelsCount = channels;
	texture->data = new RGB[dataPixelCount];

	std::memcpy(texture->data, data, dataPixelCount*channels);

	printf("%s texture loaded successfully.\n", path);

	return texture;
}
