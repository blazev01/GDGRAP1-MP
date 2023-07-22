#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"
#include "../stb_image.h"

#include "../Config/Settings.hpp"

#include "../Model/Model3D.hpp"
#include "../Model/Camera.hpp"
#include "../Model/Camera/PerspectiveCamera.hpp"
#include "../Model/Camera/OrthoCamera.hpp"
#include "../Model/Light.hpp"
#include "../Model/Light/PointLight.hpp"
#include "../Model/Skybox.hpp"

#include "../Renderer/VFShaders.hpp"
#include "../Renderer/VAO.hpp"
#include "../Renderer/VBO.hpp"
#include "../Renderer/EBO.hpp"

#include "Manager/MeshManager.hpp"
#include "Manager/TextureManager.hpp"

namespace controller {
    using namespace models;
    using namespace renderer;
    class Game {
    private:
        GLFWwindow* window;

        VFShaders* BaseShaders;
        VFShaders* SkyboxShaders;

        std::vector<GLfloat>* mesh;
        GLuint* Waifu;
        std::vector<Model3D*> Entities;

        PointLight* BaseLight;
        PerspectiveCamera* BasePCam;

        Skybox* BaseSky;

        VAO BaseVAO;
        VBO BaseVBO;

    public:
        Game();

    public:
        void run();

    private:
        void update();
        void render();
        void buffer();
    };
}

#endif