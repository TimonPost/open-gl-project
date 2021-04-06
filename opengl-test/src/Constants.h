#pragma once
#include <string>

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 1024;

const float UNIT_SIZE = 1.0f;
const float HUMAN_HEIGHT = 2.0f * UNIT_SIZE;
const float HUMAN_WIDTH = 1.0f * UNIT_SIZE;
const float HUMAN_RATIO = HUMAN_WIDTH / HUMAN_HEIGHT;

const float DEFAULT_ASPECT_RATIO = 1 * SCREEN_WIDTH / SCREEN_HEIGHT;

const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

const float CAMERA_PERSPECTIVE_VIEW_OFFSET_DEFAULT = UNIT_SIZE * 50.0f;

static std::string wall_texture = "wallTexture";
static std::string ground_texture = "groundTexture";
static std::string statue_texture = "statueTexture";
static std::string romanArchTexture = "romanArchTexture";

static std::string shadowMapShader = "shadowMapShader";
static std::string shadowMappingShader = "shadowMappingShader";