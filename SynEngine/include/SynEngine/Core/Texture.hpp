#pragma once

#include "GL\glew.h"

namespace SynEngine {
	struct RGB
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	class Texture
	{
	public:
		Texture();
		~Texture();
		
		int width;
		int height;
		int channelsCount;
		RGB* data;

		//Temp 
		GLuint id;
		void LoadTexture();
	private:
		
	};

}