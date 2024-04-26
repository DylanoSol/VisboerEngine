#pragma once
#include <string> 

class TextureContainer
{
public: 
	TextureContainer(const char* texturePath); 

	void UseTexture(); 

	unsigned int GetTextureID(); 
	
private: 
	void CompileTexture();
	void DeleteTexture();

	const char* m_texturePath; 
	unsigned int m_textureID; 
};

