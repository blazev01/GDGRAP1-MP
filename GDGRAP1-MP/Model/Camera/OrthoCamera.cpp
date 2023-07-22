#include "OrthoCamera.hpp"

using namespace models;

OrthoCamera::OrthoCamera(glm::vec3 position)
: Camera(position) {
    this->near = -1.0f;
    this->far = 1.0f;
    this->projection = this->computeProjection();
}

glm::mat4 OrthoCamera::computeProjection() {
    return glm::ortho(
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        this->near,
        this->far
    );
}

float OrthoCamera::getNear() {
    return this->near;
}

void OrthoCamera::setNear(float near) {
    this->near = near;
    this->projection = this->computeProjection();
}

float OrthoCamera::getFar() {
    return this->far;
}

void OrthoCamera::setFar(float far) {
    this->far = far;
    this->projection = this->computeProjection();
}