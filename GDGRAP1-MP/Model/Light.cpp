#include "Light.hpp"

using namespace models;

// @brief Constructor of the Light class.
// @param position - Position of the light source (in 3D space)
// @param type - Type of the light source to be created
Light::Light(glm::vec3 position, std::string type) {
    this->type = type;
    this->position = position;
    this->diffuseCol = glm::vec3(1.0f, 1.0f, 1.0f);
    this->ambientCol = glm::vec3(1.0f, 1.0f, 1.0f);
    this->specularCol = glm::vec3(1.0f, 1.0f, 1.0f);

    this->ambientStr = 0.1f;
    this->specularStr = 2.0f;

    this->shininess = 32.0f;
}

// @brief Returns the type of the light source.
// @return type
std::string Light::getType() {
    return this->type;
}

// @brief Returns the position of the light source.
// @return position
glm::vec3 Light::getPosition() {
    return this->position;
}

// @brief Sets the position of the light source.
// @param position - The new position of the light source
void Light::setPosition(glm::vec3 position) {
    this->position = position;
}

// @brief Returns the diffuse color of the light source.
// @return diffuseCol
glm::vec3 Light::getDiffuseCol() {
    return this->diffuseCol;
}

// @brief Sets the diffuse color of the light source to a given value.
// @param diffuseCol - New diffuse color of the light source
void Light::setDiffuseCol(glm::vec3 diffuseCol) {
    this->diffuseCol = diffuseCol;
}

// @brief Returns the ambient color of the light source.
// @return ambientCol
glm::vec3 Light::getAmbientCol() {
    return this->ambientCol;
}

// @brief Sets the ambient color of the light source to a given value.
// @param ambientCol - New ambient color of the light source
void Light::setAmbientCol(glm::vec3 ambientCol) {
    this->ambientCol = ambientCol;
}

// @brief Returns the specular color of the light source.
// @return specularCol
glm::vec3 Light::getSpecularCol() {
    return this->specularCol;
}

// @brief Sets the specular color of the light source to a given value.
// @param specularCol - New specular color of the light source
void Light::setSpecularCol(glm::vec3 specularCol) {
    this->specularCol = specularCol;
}

// @brief Returns the ambient strength of the light source.
// @return ambientStr
float Light::getAmbientStr() {
    return this->ambientStr;
}

// @brief Sets the ambient strength of the light source to a given value.
// @param ambientStr - New ambient strength of the light source
void Light::setAmbientStr(float ambientStr) {
    this->ambientStr = ambientStr;
}

// @brief Returns the specular strength of the light source.
// @return specularStr
float Light::getSpecularStr() {
    return this->specularStr;
}

// @brief Sets the specular strength of the light source to a given value.
// @param specularStr - New specular strength of the light source
void Light::setSpecularStr(float specularStr) {
    this->specularStr = specularStr;
}

// @brief Returns the shininess of the light source.
// @return shininess
float Light::getShininess() {
    return this->shininess;
}

// @brief Sets the shininess of the light source to a given value.
// @param shininess - New shininess value of the light source
void Light::setShininess(float shininess) {
    this->shininess = shininess;
}