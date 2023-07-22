#ifndef MODELS_SKYBOX_HPP
#define MODELS_SKYBOX_HPP

#include <glad/glad.h>

#include "../tiny_obj_loader.h"

#include "../stb_image.h"

#include "../Renderer/VFShaders.hpp"
#include "Camera.hpp"

namespace models {
    using namespace renderer;
	class Skybox {
    private:
        const float vertices[24]{
            -1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
             1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f
        };

        const unsigned int indices[36]{
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

        unsigned int texture;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

    public:
        Skybox(std::string* faces);

    public:
        void render(VFShaders& Shaders, Camera& Cam);
        void buffer();

        void deleteBuffers();
    };
}

#endif