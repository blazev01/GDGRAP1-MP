#ifndef MODELS_CAMERA_HPP
#define MODELS_CAMERA_HPP

#include <glm/gtc/matrix_transform.hpp>

namespace models {
	class Camera {
    protected:
        glm::vec3 position;
        glm::vec3 rotation;

        float distance;
        glm::vec3 center;
        glm::vec3 worldUp;
        glm::mat4 view;
        glm::mat4 projection;

    public:
        Camera(glm::vec3 position);

    public:
        void move(float fb, float rl, float ud);

        void tilt(float x, float y, float z);

    protected:
        glm::vec3 calcFront(float distance = 1.0f);
        glm::vec3 calcRight(float distance = 1.0f);

    public:
        glm::vec3 getPosition();

        glm::mat4 getView();

        glm::mat4 getProjection();
    };
}

#endif
