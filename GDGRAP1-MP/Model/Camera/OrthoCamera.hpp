#ifndef MODELS_ORTHO_CAMERA_HPP
#define MODELS_ORTHO_CAMERA_HPP

#include "../Camera.hpp"

namespace models {
	class OrthoCamera : public Camera {
	private:
        float near;
        float far;

    public:
        OrthoCamera(glm::vec3 position, glm::vec3 center = glm::vec3(0.0f));

    private:
        glm::mat4 calcProjection();

    public:
        float getNear();
        void setNear(float near);

        float getFar();
        void setFar(float far);
	};
}

#endif