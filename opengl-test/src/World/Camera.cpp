#include "Camera.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

Camera::Camera()
{
	position = glm::vec3(0.0f, 5.0f, -4.0f);
	Up = glm::vec3(0.0, 1.0, 0.0);
    Yaw = YAW;
	Pitch = PITCH;
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;
    WorldUp = Up;
}

void Camera::RefreshCameraData()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetMatrix() const
{
	return glm::lookAt(position, position + Front, Up);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    glm::vec3 newPosition = position;

    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        newPosition += Front * velocity;
    if (direction == BACKWARD)
        newPosition -= Front * velocity;
    if (direction == LEFT)
        newPosition -= Right * velocity;
    if (direction == RIGHT)
        newPosition += Right * velocity;

    if (newPosition.y < 5)
    {
        newPosition.y = 5;        
    }

	if (newPosition.x > -translate && newPosition.x < translate && newPosition.z > -translate +1 && newPosition.z < translate - 1)
	{
        position = newPosition;
	}

   
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch )
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    RefreshCameraData();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}
