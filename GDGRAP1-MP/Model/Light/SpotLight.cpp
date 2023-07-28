#include "SpotLight.hpp"

using namespace models;

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff)
    : Light(position, "SLight") {
    this->direction = direction;
    this->cutOff = cutOff;
}

glm::vec3 SpotLight::getDirection() {
    return this->direction;
}

void SpotLight::setDirection(glm::vec3 direction) {
    this->direction = direction;
}

float SpotLight::getCutoff() {
    return this->cutOff;
}

void SpotLight::setCutOff(float cutOff) {
    this->cutOff = cutOff;
}
