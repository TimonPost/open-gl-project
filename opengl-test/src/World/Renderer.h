#pragma once

#include <memory>
#include "Camera.h"
#include "../GlWrap.h"

class Renderer
{
private:
	glm::mat4 _identity;
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;
public:
	std::unique_ptr<Camera> camera;

	Renderer();

	void UpdateProjection(float screenWidth, float screenHeight, float aspectRatio, float nearPlane, float farPlane);

	glm::mat4 MVP() const;
	glm::mat4 MV() const;
	glm::mat4 M() const;
	glm::mat4 P() const;
	glm::mat4 V() const;

	glm::mat4 LightProjection() const;
	glm::vec3 LightPosition() const;
	glm::mat4 LightView() const;
	glm::mat4 LightModel() const;
	glm::mat4 LightSpaceMVP() const;
	glm::mat4 BiasMatrix() ;
	glm::mat4 DepthMat();
	
	static void Clear();
};
