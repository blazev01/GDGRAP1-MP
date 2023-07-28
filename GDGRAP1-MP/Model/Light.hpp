#ifndef MODELS_LIGHT_HPP
#define MODELS_LIGHT_HPP

#include <string>

#include <glm/gtc/matrix_transform.hpp>

namespace models {
	class Light {
    protected:
        std::string type;

        glm::vec3 position;

        glm::vec3 diffuseCol;
        glm::vec3 ambientCol;
        glm::vec3 specularCol;

        float ambientStr;
        float specularStr;

        float shininess;

    public:
        Light(glm::vec3 position, std::string type = "DLight");

    public:
        std::string getType();

        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        glm::vec3 getDiffuseCol();
        void setDiffuseCol(glm::vec3 diffuseCol);

        glm::vec3 getAmbientCol();
        void setAmbientCol(glm::vec3 ambientCol);

        glm::vec3 getSpecularCol();

        void setSpecularCol(glm::vec3 specularCol);

        float getAmbientStr();
        void setAmbientStr(float ambientStr);

        float getSpecularStr();
        void setSpecularStr(float specularStr);

        float getShininess();
        void setShininess(float shininess);
    };
}

#endif