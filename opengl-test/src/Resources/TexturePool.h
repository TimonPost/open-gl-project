#pragma once

#include <vector>

#include "texture.hpp"
#include "TextureEntries.hpp"

class TexturePool
{
public:
	std::vector<PBRTextureEntry*> PBRTextures;
	std::vector<SimpleTextureEntry*> SimpleTextures;

	TexturePool(TexturePool const&);
	TexturePool& operator=(TexturePool const&);

	static TexturePool* Instance();

	void AddPBRTexture(PBRTextureEntry* entry);
	void AddSimpleTexture(SimpleTextureEntry* entry);
	SimpleTextureEntry* GetSimpleTextureById(std::string textureId);
	PBRTextureEntry* GetPBRById(std::string textureId);

	TexturePool() {}
private:
	static TexturePool* instance;

	//TexturePool() {}
};
