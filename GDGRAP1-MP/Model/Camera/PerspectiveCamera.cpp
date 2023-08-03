#include "PerspectiveCamera.hpp"

using namespace models;

// @brief The constructor of the Perspective Camera class.
// @param position - The position of the camera
// @param center - The point in which the camera is looking at (target)
// @param fov - The field of view of the camera
// @param near - The nearest point which the camera could render.
// @param far - The farthest point which the camera could render.
PerspectiveCamera::PerspectiveCamera(
	glm::vec3 position,
	glm::vec3 center,
	float fov,
	float near,
	float far)
	: Camera(position, center) {
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->projection = this->calcProjection();
}

// @brief Calculates the camera's projection matrix based on the camera's field of view, aspect ratio, near plane and far plane distance.
// @return glm::ortho()
glm::mat4 PerspectiveCamera::calcProjection() {
	return glm::perspective(
		glm::radians(this->fov),
		ASPECT,
		this->near,
		this->far
	);
}

// @brief Returns the current field of view value of the orthographic camera.
// @return this->fov
float PerspectiveCamera::getFOV() {
	return this->fov;
}

// @brief Sets the FOV of the orthographic camera.
// @param fov - The new value for this->fov
void PerspectiveCamera::setFOV(float fov) {
	this->fov = fov;
	this->projection = this->calcProjection();
}

// @brief Returns the near plane distance of the orthographic camera.
// @return this->near
float PerspectiveCamera::getNear() {
	return this->near;
}

// @brief Sets the near plane distance of the orthographic camera.
// @param near - The new value for this->near (near plane distance)
void PerspectiveCamera::setNear(float near) {
	this->near = near;
	this->projection = this->calcProjection();
}

// @brief Returns the far plane distance of the orthographic camera.
// @return this->far
float PerspectiveCamera::getFar() {
	return this->far;
}

// @brief Sets the far plane distance of the orthographic camera.
// @param near - The new value for this->far (far plane distance)
void PerspectiveCamera::setFar(float far) {
	this->far = far;
	this->projection = this->calcProjection();
}