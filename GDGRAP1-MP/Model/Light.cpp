#include "Light.hpp"

using namespace models;

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

std::string Light::getType() {
    return this->type;
}

glm::vec3 Light::getPosition() {
    return this->position;
}

void Light::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 Light::getDiffuseCol() {
    return this->diffuseCol;
}

void Light::setDiffuseCol(glm::vec3 diffuseCol) {
    this->diffuseCol = diffuseCol;
}

glm::vec3 Light::getAmbientCol() {
    return this->ambientCol;
}

void Light::setAmbientCol(glm::vec3 ambientCol) {
    this->ambientCol = ambientCol;
}

glm::vec3 Light::getSpecularCol() {
    return this->specularCol;
}

void Light::setSpecularCol(glm::vec3 specularCol) {
    this->specularCol = specularCol;
}

float Light::getAmbientStr() {
    return this->ambientStr;
}

void Light::setAmbientStr(float ambientStr) {
    this->ambientStr = ambientStr;
}

float Light::getSpecularStr() {
    return this->specularStr;
}

void Light::setSpecularStr(float specularStr) {
    this->specularStr = specularStr;
}

float Light::getShininess() {
    return this->shininess;
}

void Light::setShininess(float shininess) {
    this->shininess = shininess;
}