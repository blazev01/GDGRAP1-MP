#ifndef MODELS_POINT_LIGHT_HPP
#define MODELS_POINT_LIGHT_HPP

#include "../Light.hpp"

namespace models {
    class PointLight : public Light {
    private:
        float constant;
        float linear;
        float quadratic;

    public:
        PointLight(glm::vec3 position);

    public:
        float getConstant();
        void setConstant(float constant);

        float getLinear();
        void setLinear(float linear);

        float getQuadratic();
        void setQuadratic(float quadratic);
    };
}

#endif