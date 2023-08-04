#include "SpotLight.hpp"

using namespace models;

// @brief Main constructor of the Spot Light class
// @param position - Initial position of the spotlight.
// @param direction - Represents the direction the spotlight is pointing
// @param cutOff - Angle of the cone's cutoff; defines the spread of the spotlight's cone
SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff)
    : Light(position, "SLight") {
    this->direction = direction;
    this->cutOff = cutOff;
}

// @brief Returns the direction of the spotlight.
// @return this->direction
glm::vec3 SpotLight::getDirection() {
    return this->direction;
}

// @brief Sets the direction of the spotlight; changing its orientation and directing the light to a different location.
// @param direction - New direction of the spotlight
void SpotLight::setDirection(glm::vec3 direction) {
    this->direction = direction;
}

// @brief Returns the cutoff angle of the spotlight cone.
// @return this->cutOff
float SpotLight::getCutoff() {
    return this->cutOff;
}

// @brief Sets the cutoff angle of the spotlight cone; can adjust the spread of the cone, making it narrower/wider as needed.
// @param cutOff - The new value of the cutoff angle.
void SpotLight::setCutOff(float cutOff) {
    this->cutOff = cutOff;
}
