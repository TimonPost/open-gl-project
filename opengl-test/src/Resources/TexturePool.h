#pragma once

#include <vector>

#include "TextureEntries.hpp"

/// <summary>
/// Pool with loaded textures that can be acquired.
/// This pool improves performance since textures are not to be loaded multiple times.
/// </summary>
class TexturePool
{
public:		
	static TexturePool* Instance();

	/// <summary>
	/// Adds an physical based rendering texture entry to the pool.
	/// </summary>
	/// <param name="entry"></param>
	void AddPBRTexture(PBRTextureEntry* entry);
	
	/// <summary>
	/// Adds an simple texture entry to the pool.
	/// </summary>
	/// <param name="entry"></param>
	void AddSimpleTexture(SimpleTextureEntry* entry);

	/// <summary>
	/// Returns the texture entry with the given texture id.
	/// </summary>
	/// <param name="textureId"></param>
	/// <returns></returns>
	SimpleTextureEntry* GetSimpleTextureById(std::string textureId);

	/// <summary>
	/// Returns the texture entry with the given texture id.
	/// </summary>
	/// <param name="textureId"></param>
	/// <returns></returns>
	PBRTextureEntry* GetPBRById(std::string textureId);

private:
	TexturePool() {}
	static TexturePool* instance;
	TexturePool(TexturePool const&);
	TexturePool& operator=(TexturePool const&);

	std::vector<PBRTextureEntry*> PBRTextures;
	std::vector<SimpleTextureEntry*> SimpleTextures;
	std::vector<ObjectTextureEntry*> ObjectTextures;
};
