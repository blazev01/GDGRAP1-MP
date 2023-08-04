#include "PointLight.hpp"

using namespace models;

// @brief Main constructor of the Point Light class
// @param position - The initialized position of the Point Light
PointLight::PointLight(glm::vec3 position)
    : Light(position, "PLight") {
    this->constant = 1.0;
    this->linear = 0.02;
    this->quadratic = 0.0015;
}

// @brief Returns the constant attenuation factor of the Point Light.
// @return this->constant
float PointLight::getConstant() {
    return this->constant;
}

// @brief Sets the constant attenuation factor of the Point Light; ensures the light's intensity regardless of distance from light source.
// @param constant - The new value for the constant attenuation
void PointLight::setConstant(float constant) {
    this->constant = constant;
}

// @brief Returns the linear attenuation factor of the Point Light.
// @return this->linear
float PointLight::getLinear() {
    return this->linear;
}

// @brief Sets the linear attenuation factor of the Point Light; adds additional attenuation based on the distance from the light source.
// @param linear - The new value for linear attenuation
void PointLight::setLinear(float linear) {
    this->linear = linear;
}

// @brief Returns the quadratic attenuation factor of the Point Light.
// @return this->quadratic
float PointLight::getQuadratic() {
    return this->quadratic;
}

// @brief Sets the quadratic attenuation factor of the Point Light; causes light intensity to decrease quadratically via distance.
// @param quadratic - The new value for the quadratic attenuation factor
void PointLight::setQuadratic(float quadratic) {
    this->quadratic = quadratic;
}