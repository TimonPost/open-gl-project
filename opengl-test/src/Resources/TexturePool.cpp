#include "TexturePool.h"

#include <vector>

TexturePool::TexturePool(TexturePool const&)
{
}

TexturePool* TexturePool::instance = 0;

TexturePool* TexturePool::Instance()
{
	if (instance == 0)
	{
		instance = new TexturePool();
	}

	return instance;
}

void TexturePool::AddPBRTexture(PBRTextureEntry* entry)
{
	PBRTextures.push_back(entry);
}

void TexturePool::AddObjectTexture(ObjectTextureEntry* entry)
{
	ObjectTextures.push_back(entry);
}

void TexturePool::AddSimpleTexture(SimpleTextureEntry* entry)
{
	SimpleTextures.push_back(entry);
}

SimpleTextureEntry* TexturePool::GetSimpleTextureById(const std::string textureId)
{
	for (auto& simple_texture : SimpleTextures)
	{
		if (simple_texture->Label == textureId)
			return simple_texture;
	}

	throw "Texture Could not be found";
}

PBRTextureEntry* TexturePool::GetPBRById(const std::string textureId)
{
	for (auto& pbr_texture : PBRTextures)
	{
		if (pbr_texture->Label == textureId)
			return pbr_texture;
	}

	throw "Texture Could not be found";
}
