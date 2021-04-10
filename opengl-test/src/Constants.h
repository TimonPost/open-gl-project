#pragma once
#include <string>


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

const float UNIT_SIZE = 1.0f;
const float HUMAN_HEIGHT = 2.0f * UNIT_SIZE;
const float HUMAN_WIDTH = 1.0f * UNIT_SIZE;
const float HUMAN_RATIO = HUMAN_WIDTH / HUMAN_HEIGHT;

const float DEFAULT_ASPECT_RATIO = 1 * SCREEN_WIDTH / SCREEN_HEIGHT;

const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

const float CAMERA_PERSPECTIVE_VIEW_OFFSET_DEFAULT = UNIT_SIZE * 50.0f;

static std::string wall_texture = "wallTexture";
static std::string sphere_textureID = "sphereTextureId";
static std::string brick_textureID = "brickTextureId";
static std::string ground_texture = "groundTexture";
static std::string statue_texture = "statueTexture";
static std::string building_texture = "buildingTexture ";
static std::string romanArchTexture = "romanArchTexture";
static std::string post_texture = "postTexture";
static std::string window_texture = "windowTexture";
static std::string uvTemplateTexture = "uvTemplateTexture";
static std::string skyTextureID = "skyTexture";

static std::string wood_textureID = "wood_textureID";
static std::string cloth_textureID = "cloth_textureID";
static std::string medievalIronTextureID = "medievalIron";
static std::string goldShpereID = "roofTileTextureID";



static std::string window_meshID = "windowMesh";
static std::string post_meshID = "postMesh";
static std::string building_meshID = "buildingMesh";
static std::string statue_meshID = "statue_meshID";
static std::string cube_meshID = "cube_meshID";

static std::string shadowMapShaderID = "shadowMapShader";
static std::string shadowMappingShaderID = "shadowMappingShader"; 

static std::string objectShaderID = "objectShader";
static std::string pbrShaderID = "pbrShader"; 
static std::string lightingShaderID = "lightingShader";

static float wallSize = 60;
static float wallHeight = 30;
static float translate = 30;