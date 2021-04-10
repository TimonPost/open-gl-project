#include "Renderer.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#include "../Constants.h"
#include "../GlWrap.h"


Renderer::Renderer()
{
	camera = std::make_unique<Camera>();

	_identity = glm::mat4(1.0f);
	_model = glm::scale(_identity, glm::vec3(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE));
	_view = camera->GetMatrix();

	UpdateProjection(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_ASPECT_RATIO, FAR_PLANE, NEAR_PLANE);
}

void Renderer::UpdateProjection(float screenWidth, float screenHeight, float aspectRatio, float nearPlane,
                                float farPlane)
{
	_projection = glm::perspective(glm::radians(camera->Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

glm::mat4 Renderer::M() const
{
	return _model;
}

glm::mat4 Renderer::P() const
{
	return _projection;
}

glm::mat4 Renderer::V() const
{
	return camera->GetMatrix();
}

glm::mat4 Renderer::MV() const
{
	return V() * M();
}

glm::mat4 Renderer::MVP() const
{
	return P() * MV();
}

glm::mat4 Renderer::LightProjection() const
{
	float near_plane = 1.0f, far_plane = 50.5f;
	return glm::ortho(-30.0f, 30.0f, -5.0f, 30.0f, near_plane, far_plane);
}

glm::vec3 Renderer::LightPosition() const
{
	return glm::vec3(-4.0f, 15, 20.0f);
}

glm::mat4 Renderer::LightView() const
{
	return glm::lookAt(LightPosition(),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Renderer::LightModel() const
{
	return glm::mat4(1.0);
}

glm::mat4 Renderer::LightSpaceMVP() const
{
	return LightProjection() * LightView();
}

glm::mat4 Renderer::BiasMatrix()
{
	return glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);	
}

glm::mat4 Renderer::DepthMat()
{
	return BiasMatrix() * LightSpaceMVP();
}