#include "OrthoCamera.hpp"

using namespace models;

OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec3 center)
: Camera(position, center) {
    this->near = 0.1f;
    this->far = 100.0f;
    this->projection = this->calcProjection();
}

glm::mat4 OrthoCamera::calcProjection() {
    return glm::ortho(
        -1.0f,
        1.0f,
        -1.0f,
        1.0f,
        this->near,
        this->far
    );
}

float OrthoCamera::getNear() {
    return this->near;
}

void OrthoCamera::setNear(float near) {
    this->near = near;
    this->projection = this->calcProjection();
}

float OrthoCamera::getFar() {
    return this->far;
}

void OrthoCamera::setFar(float far) {
    this->far = far;
    this->projection = this->calcProjection();
}