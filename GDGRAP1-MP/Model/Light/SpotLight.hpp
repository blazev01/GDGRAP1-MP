#ifndef MODELS_SPOT_LIGHT_HPP
#define MODELS_SPOT_LIGHT_HPP

#include "../Light.hpp"

namespace models {
	class SpotLight : public Light {
    private:
        glm::vec3 direction;
        float cutOff;

    public:
        SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff = 1.0f);

    public:
        glm::vec3 getDirection();
        void setDirection(glm::vec3 direction);

        float getCutoff();
        void setCutOff(float cutOff);
    };
}

#endif