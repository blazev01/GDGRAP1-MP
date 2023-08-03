#include "OrthoCamera.hpp"

using namespace models;

OrthoCamera::OrthoCamera(
    glm::vec3 position,
    glm::vec3 center,
    float viewScale,
    float near,
    float far
) : Camera(position, center) {
    this->viewScale = viewScale;
    this->near = near;
    this->far = far;
    this->projection = this->calcProjection();
}

glm::mat4 OrthoCamera::calcProjection() {
    return glm::ortho(
        -this->viewScale * ASPECT,
        this->viewScale * ASPECT,
        -this->viewScale,
        this->viewScale,
        this->near,
        this->far
    );
}

float OrthoCamera::getViewScale() {
    return this->viewScale;
}

void OrthoCamera::setViewScale(float scale) {
    this->viewScale = scale;
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