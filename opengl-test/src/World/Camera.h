#pragma once
#include <glm.hpp>
#include "../Constants.h"
#include "../GlWrap.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 40.5f;
const float SENSITIVITY = 0.4f;
const float ZOOM = 45.0f;

/// <summary>
/// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
/// </summary>
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

/// <summary>
/// A device for catching light in a scene. 
/// </summary>
class Camera
{
	float cameraSpeed = 1;

	// euler Angles
	float Yaw;
	float Pitch;

	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	void RefreshCameraData();

public:
	float Zoom;
	glm::vec3 position;
	
	float FarPlane = FAR_PLANE;
	float NearPlane = NEAR_PLANE;
	
	Camera();

	/// <summary>
	/// Returns the camera view matrix.
	/// </summary>
	glm::mat4 GetViewMatrix() const;

	// Processes input received from a keyboar input system. Expects the offset value in both the x and y direction.
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	
    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);
};
