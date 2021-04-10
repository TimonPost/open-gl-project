#pragma once

#include <memory>
#include "Camera.h"

/// <summary>
/// Renderer for the game graphics.
/// </summary>
class Renderer
{
	glm::mat4 _identity;
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

public:
	std::unique_ptr<Camera> camera;

	Renderer();

	/// <summary>
	/// Updates projection matrix when screen, aspect ratio, nearplane or far plane have changed.
	/// </summary>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearPlane"></param>
	/// <param name="farPlane"></param>
	void UpdateProjection(float screenWidth, float screenHeight, float aspectRatio, float nearPlane, float farPlane);

	/// <summary>
	/// Returns the camera model view projection matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 CameraMVP() const;

	/// <summary>
	/// Returns the camera model view matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 CameraMV() const;

	/// <summary>
	/// Returns the camera model matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 CameraModel() const;
	
	/// <summary>
	/// Returns the camera projection matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 CameraProjection() const;

	/// <summary>
	/// Returns the camera view matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 CameraView() const;

	/// <summary>
	/// Returns the light projection matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 LightProjection() const;

	/// <summary>
	/// Returns the light position.
	/// </summary>
	/// <returns></returns>
	glm::vec3 LightPosition() const;

	/// <summary>
	/// Returns the light view matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 LightView() const;

	/// <summary>
	/// Returns the light model matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 LightModel() const;

	/// <summary>
	/// Returns the light model view projection matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 LightSpaceMVP() const;

	/// <summary>
	/// Returns the light bias matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 BiasMatrix();

	/// <summary>
	/// Returns the light depth matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4 DepthMat();

	/// <summary>
	/// Clears the game screen.
	/// </summary>
	static void Clear();
};
