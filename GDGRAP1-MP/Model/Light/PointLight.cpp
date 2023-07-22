#include "PointLight.hpp"

using namespace models;

PointLight::PointLight(glm::vec3 position)
    : Light(position) {
    this->constant = 1.0;
    this->linear = 0.02;
    this->quadratic = 0.0015;
}

float PointLight::getConstant() {
    return this->constant;
}

void PointLight::setConstant(float constant) {
    this->constant = constant;
}

float PointLight::getLinear() {
    return this->linear;
}

void PointLight::setLinear(float linear) {
    this->linear = linear;
}

float PointLight::getQuadratic() {
    return this->quadratic;
}

void PointLight::setQuadratic(float quadratic) {
    this->quadratic = quadratic;
}