#ifndef MODELS_GAME_OBJECT_HPP
#define MODELS_GAME_OBJECT_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Renderer/VFShaders.hpp"
#include "Enum/MeshType.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "Light/DirLight.hpp"
#include "Light/PointLight.hpp"
#include "Light/SpotLight.hpp"

namespace models {
    using namespace renderers;
    class Model3D {
    private:
        std::string name;
        MeshType Type;
        std::vector<GLfloat>* mesh;
        glm::mat4 transformation;
        VFShaders* Shaders;
        GLuint* texture;
        GLuint* normalMap;

    public:
        Model3D(
            std::string name,
            MeshType Type,
            std::vector<GLfloat>* mesh,
            VFShaders* Shaders,
            GLuint* texture = NULL,
            GLuint* normalMap = NULL,
            float scale = 1.0f,
            glm::vec3 position = glm::vec3(0.0f));

    public:
        void draw(Camera* Cam, std::vector<Light*> Lights);
        void drawLight(Camera* Cam, Light* Lit);
        
    public:
        void translate(glm::vec3 translation);
        void translate(float x, float y, float z);
        void scale(glm::vec3 escalation);
        void scale(float x, float y, float z);
        void scale(float scalar);
        void rotate(float theta, glm::vec3 axis);
        void rotate(float theta, float x, float y, float z);

    public:
        void setPosition(glm::vec3 position);

        MeshType getMeshType();
        std::vector<GLfloat>* getMesh();
        glm::mat4 getTransformation();
        glm::vec3 getPosition();
    };
}

#endif