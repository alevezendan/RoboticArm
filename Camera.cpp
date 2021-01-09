#include"pch.h"
#include "Camera.hpp"

namespace gps {

	//Camera constructor
	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
		//TODO
//init fiecare val din camera.hpp  camerapos=camerapos; cameratarget=cameratrget;cameraup=cameraupdirection
		this->cameraPosition = cameraPosition;
		this->cameraTarget = cameraTarget;
		this->cameraUpDirection = cameraUp;
		this->cameraFrontDirection = glm::normalize(-this->cameraPosition + this->cameraTarget);
		this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
	}

	//return the view matrix, using the glm::lookAt() function
	glm::mat4 Camera::getViewMatrix() {
		//TODO
		//primu arg:cam pos;;al doilea:o directie anume:cameraTarget-camerposition;;;al treilea:cameraUp
		glm::mat4 view = glm::lookAt(this->cameraPosition, this->cameraPosition + this->cameraFrontDirection, this->cameraUpDirection);
		return view;
	}

	//update the camera internal parameters following a camera move event
	void Camera::move(MOVE_DIRECTION direction, float speed) {
		switch (direction) {
		case MOVE_FORWARD: this->cameraPosition += this->cameraFrontDirection * speed;
		case MOVE_BACKWARD: this->cameraPosition -= this->cameraFrontDirection * speed;
		case MOVE_RIGHT: this->cameraPosition += this->cameraRightDirection * speed;
		case MOVE_LEFT: this->cameraPosition -= this->cameraRightDirection * speed;
		}
	}

	//update the camera internal parameters following a camera rotate event
	//yaw - camera rotation around the y axis
	//pitch - camera rotation around the x axis
	void Camera::rotate(float pitch, float yaw) {
		//TODO
		if (pitch > 89)
			pitch = 89;
		if (pitch < -89)
			pitch = -89;

		glm::vec3 v;
		v.x = glm::cos(pitch) * glm::cos(yaw);
		v.y = glm::sin(pitch);
		v.z = glm::cos(pitch) * glm::sin(yaw);

		// i se atribuie lui front=normalize(v); right=normalize(cross(front,(0,1,0)))

	}
}