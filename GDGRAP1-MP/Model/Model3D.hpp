#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Renderer/VFShaders.hpp"
#include "Camera.hpp"
#include "Light.hpp"

namespace models {
    using namespace renderer;
    class Model3D {
    private:
        std::string name;
        std::vector<GLfloat>* mesh;
        glm::mat4 transformation;
        GLuint* texture;
        //Material* Mat;

    public:
        Model3D(
            std::string name,
            std::vector<GLfloat>* model3D,
            GLuint* texture,
            //Material* Mat,
            float scale = 1.0f,
            glm::vec3 position = glm::vec3(0.0f));

    public:
        void draw(VFShaders& Shaders, Camera& Cam, Light& Lit);

    private:
        void drawLight(VFShaders& Shaders, Light& Lit);

    public:
        void translate(glm::vec3 translation);
        void translate(float x, float y, float z);
        void scale(glm::vec3 escalation);
        void scale(float x, float y, float z);
        void scale(float scalar);
        void rotate(float theta, glm::vec3 axis);
        void rotate(float theta, float x, float y, float z);

    public:
        std::vector<GLfloat>* getMesh();
        glm::mat4 getTransformation();
    };
}

#endif