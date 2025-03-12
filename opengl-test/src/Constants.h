#pragma once
#include <string>

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

static float wallSize = 60;
static float wallHeight = 30;
static float translate = 30;

// Texture Identifiers
static std::string wall_textureID = "wall_textureID";
static std::string sphere_textureID = "sphere_textureID";
static std::string brick_textureID = "brick_textureID";
static std::string ground_textureID = "ground_textureID";
static std::string statue_textureID = "statue_textureID";
static std::string building_textureID = "building_textureID ";
static std::string ironFence_textureID = "ironFence_textureID";
static std::string midevil_textureID = "midevil_textureID ";
static std::string window_textureID = "window_textureID";
static std::string sky_texture_ID = "sky_texture_ID";

static std::string wood_textureID = "wood_textureID";
static std::string cloth_textureID = "cloth_textureID";
static std::string gold_textureID = "gold_textureID";

// Mesh Identifiers
static std::string window_meshID = "window_meshID";
static std::string ironFence_meshID = "ironFence_meshID";
static std::string building_meshID = "building_meshID";
static std::string statue_meshID = "statue_meshID";
static std::string cube_meshID = "cube_meshID";
static std::string self_designed_MeshID = "self_designed_MeshID";


// Shader Identifiers
static std::string shadow_map_shaderID = "shadow_map_shaderID";
static std::string shadow_passtrough_shaderID = "shadow_passtrough_shaderID"; 
static std::string object_shaderID = "object_shaderID";
static std::string object_no_texture_shaderID = "object_no_texture_shaderID";

static std::string pbr_shaderID = "pbr_shaderID"; 
static std::string lighting_shaderID = "lighting_shaderID";

