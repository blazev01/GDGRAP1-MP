#include "PerspectiveCamera.hpp"

using namespace models;

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 center, float fov)
	: Camera(position, center) {
	this->fov = fov;
	this->near = 0.1f;
	this->far = 100.0f;
	this->projection = this->calcProjection();
}

glm::mat4 PerspectiveCamera::calcProjection() {
	return glm::perspective(
		glm::radians(this->fov),
		ASPECT,
		this->near,
		this->far
	);
}

float PerspectiveCamera::getFOV() {
	return this->fov;
}

void PerspectiveCamera::setFOV(float fov) {
	this->fov = fov;
	this->projection = this->calcProjection();
}

float PerspectiveCamera::getNear() {
	return this->near;
}

void PerspectiveCamera::setNear(float near) {
	this->near = near;
	this->projection = this->calcProjection();
}

float PerspectiveCamera::getFar() {
	return this->far;
}

void PerspectiveCamera::setFar(float far) {
	this->far = far;
	this->projection = this->calcProjection();
}