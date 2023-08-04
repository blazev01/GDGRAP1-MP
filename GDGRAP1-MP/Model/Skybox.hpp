#ifndef MODELS_SKYBOX_HPP
#define MODELS_SKYBOX_HPP

#include <vector>

#include <glad/glad.h>

#include "../Renderer/VFShaders.hpp"
#include "Camera.hpp"

namespace models {
    using namespace renderers;
	class Skybox {
    private:
        float vertices[24]{
            -1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
             1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f
        };

        unsigned int indices[36]{
            1,2,6,
            6,5,1,

            0,4,7,
            7,3,0,

            4,5,6,
            6,7,4,

            0,3,2,
            2,1,0,

            0,1,5,
            5,4,0,

            3,7,6,
            6,2,3
        };

        VFShaders* Shaders;
        GLuint* texture;

    public:
        Skybox(VFShaders* Shaders, GLuint* texture);

    public:
        void draw(Camera* Cam);
        void buffer();

    public:
        void setShaders(VFShaders* Shaders);

        std::vector<GLfloat> getVertices();

        std::vector<GLuint> getIndices();

    };
}

#endif