#include "Renderer.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#include "../Constants.h"
#include "../GlWrap.h"


Renderer::Renderer()
{
	camera = std::make_unique<Camera>(MovementModes::Walking);

	_identity = glm::mat4(1.0f);
	_model = glm::scale(_identity, glm::vec3(1, 1, 1));
	_view = camera->GetViewMatrix();
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

glm::mat4 Renderer::CameraModel() const
{
	return _model;
}

glm::mat4 Renderer::CameraProjection() const
{
	return glm::perspective(glm::radians(camera->Zoom), GameWindow::AspectRatio(), 0.1f, 100.0f);
}

glm::mat4 Renderer::CameraView() const
{
	return camera->GetViewMatrix();
}

glm::mat4 Renderer::CameraMV() const
{
	return CameraView() * CameraModel();
}

glm::mat4 Renderer::CameraMVP() const
{
	return CameraProjection() * CameraMV();
}

glm::mat4 Renderer::LightProjection() const
{
	const float near_plane = 1.0f, far_plane = 50.5f;
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