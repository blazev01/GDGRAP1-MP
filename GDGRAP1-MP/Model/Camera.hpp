#ifndef MODELS_CAMERA_HPP
#define MODELS_CAMERA_HPP

#include <glm/gtc/matrix_transform.hpp>

namespace models {
	class Camera {
    protected:
        glm::vec3 position;
        glm::vec3 center;
        glm::vec3 worldUp;

        glm::vec3 F;
        glm::vec3 R;
        glm::vec3 U;

        glm::mat4 orientation;
        glm::mat4 view;
        glm::mat4 projection;

    public:
        Camera(glm::vec3 position, glm::vec3 center);

    public:
        void translate(glm::vec3 position);
        void translate(float x, float y, float z);
        void move(float f, float r, float u);
        void tilt(float theta, glm::vec3 axis);
        void tilt(float theta, float x, float y, float z);

    protected:
        glm::mat4 calcOrientation();
        glm::mat4 calcView();
        virtual glm::mat4 calcProjection() = 0;

    public:
        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        glm::vec3 getCenter();
        void setCenter(glm::vec3 center);

        glm::mat4 getView();

        glm::mat4 getProjection();
    };
}

#endif
