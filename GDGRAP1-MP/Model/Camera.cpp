#include "Camera.hpp"

using namespace models;

Camera::Camera(glm::vec3 position) {
    this->position = position;
    this->rotation = glm::vec3(0.0f);

    this->distance = 10.0f;
    this->worldUp = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
    this->center = this->position - this->calcFront(this->distance);
    this->view = glm::lookAt(this->position, this->center, this->worldUp);

    this->projection = glm::mat4(1.0f);
}

void Camera::move(float fb, float rl, float ud) {
    if (fb) this->position += this->calcFront(fb);
    if (rl) this->position += this->calcRight(rl);
    if (ud) this->position.y += ud;

    this->center = this->position - this->calcFront(this->distance);
    this->view = glm::lookAt(this->position, this->center, this->worldUp);
}

void Camera::tilt(float x, float y, float z) {
    this->rotation += glm::vec3(x, y, z);

    this->center = this->position - this->calcFront(this->distance);
    this->view = glm::lookAt(this->position, this->center, this->worldUp);
}

glm::vec3 Camera::calcFront(float distance) {
    glm::vec3 front(0.0f, 0.0f, 0.0f);
    front.x = distance * sin(glm::radians(this->rotation.x)) * sin(glm::radians(this->rotation.z));
    front.y = distance * cos(glm::radians(this->rotation.y)) * sin(glm::radians(this->rotation.z));
    front.z = distance * cos(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));
    return front;
}
glm::vec3 Camera::calcRight(float distance) {
    glm::vec3 right(0.0f, 0.0f, 0.0f);
    right.x = distance * cos(glm::radians(this->rotation.z));
    right.z = distance * sin(glm::radians(this->rotation.x));
    return right;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::mat4 Camera::getView() {
    return this->view;
}

glm::mat4 Camera::getProjection() {
    return this->projection;
}