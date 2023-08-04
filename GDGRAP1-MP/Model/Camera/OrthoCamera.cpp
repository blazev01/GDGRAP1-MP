#include "OrthoCamera.hpp"

using namespace models;

// @brief The constructor of the Orthographic Camera class.
// @param position - The position of the camera
// @param center - The point in which the camera is looking at (target)
// @param viewScale - The distance of the screen from its center square-wise (left, right, bottom, top)
// @param near - The nearest point which the camera could render.
// @param far - The farthest point which the camera could render.
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

// @brief Calculates the camera's projection matrix based on the camera's view scale, aspect ratio, near plane and far plane distance.
// @return glm::ortho()
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

// @brief Returns the current view scale of the orthographic camera.
// @return this->viewScale
float OrthoCamera::getViewScale() {
    return this->viewScale;
}

// @brief Sets the view scale of the orthographic camera.
// @param scale - The new value for viewScale
void OrthoCamera::setViewScale(float scale) {
    this->viewScale = scale;
}

// @brief Returns the near plane distance of the orthographic camera.
// @return this->near
float OrthoCamera::getNear() {
    return this->near;
}

// @brief Sets the near plane distance of the orthographic camera.
// @param near - The new value for this->near (near plane distance)
void OrthoCamera::setNear(float near) {
    this->near = near;
    this->projection = this->calcProjection();
}

// @brief Returns the far plane distance of the orthographic camera.
// @return this->far
float OrthoCamera::getFar() {
    return this->far;
}

// @brief Sets the far plane distance of the orthographic camera.
// @param near - The new value for this->far (far plane distance)
void OrthoCamera::setFar(float far) {
    this->far = far;
    this->projection = this->calcProjection();
}