#ifndef MODELS_ORTHO_CAMERA_HPP
#define MODELS_ORTHO_CAMERA_HPP

#include "../../Config/Settings.hpp"

#include "../Camera.hpp"

namespace models {
	class OrthoCamera : public Camera {
	private:
        float viewScale;
        float near;
        float far;

    public:
        OrthoCamera(
            glm::vec3 position,
            glm::vec3 center = glm::vec3(0.0f),
            float viewScale = 1.0f,
            float near = 0.1f,
            float far = 100.0f
        );

    private:
        glm::mat4 calcProjection();

    public:
        float getViewScale();
        void setViewScale(float scale);

        float getNear();
        void setNear(float near);

        float getFar();
        void setFar(float far);
	};
}

#endif