#include "TexturePool.h"

#include <vector>

TexturePool::TexturePool(TexturePool const&)
{
}

TexturePool* TexturePool::instance = nullptr;

TexturePool* TexturePool::Instance()
{
	if (instance == nullptr)
	{
		instance = new TexturePool();
	}

	return instance;
}

void TexturePool::AddPBRTexture(PBRTextureEntry* entry)
{
	PBRTextures.push_back(entry);
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

	throw std::exception("Texture Could not be found");
}

PBRTextureEntry* TexturePool::GetPBRById(const std::string textureId)
{
	for (auto& pbr_texture : PBRTextures)
	{
		if (pbr_texture->Label == textureId)
			return pbr_texture;
	}

	throw std::exception("Texture Could not be found");
}

TexturePool::~TexturePool()
{
	for (PBRTextureEntry* obj : PBRTextures)
		delete obj;
	for (SimpleTextureEntry* obj : SimpleTextures)
		delete obj;
	for (ObjectTextureEntry* obj : ObjectTextures)
		delete obj;

	PBRTextures.clear();
	SimpleTextures.clear();
	ObjectTextures.clear();
}
