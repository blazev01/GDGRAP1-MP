#include "DirLight.hpp"

using namespace models;

// @brief Main constructor of the Direction Light
DirLight::DirLight(glm::vec3 position) : Light(position, "DLight") {}