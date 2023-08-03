#include "OrthoCamera.hpp"
#include "iostream"

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
    this->xOffset = 0.0f;
    this->yOffset = 0.0f;
    this->projection = this->calcProjection();
}

glm::mat4 OrthoCamera::calcProjection() {
    return glm::ortho(
        -this->viewScale * ASPECT + this->xOffset,
        this->viewScale * ASPECT + this->xOffset,
        -this->viewScale + this->yOffset,
        this->viewScale + this->yOffset,
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

float OrthoCamera::getXOffset() {
    return this->xOffset;
}

void OrthoCamera::setXOffset(float offset) {
    this->xOffset = offset;
}

float OrthoCamera::getYOffset() {
    return this->yOffset;
}

void OrthoCamera::setYOffset(float offset) {
    this->yOffset = offset;
}