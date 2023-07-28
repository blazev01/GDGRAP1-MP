#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "../Config/Settings.hpp"

#include "Manager/MeshManager.hpp"
#include "Manager/TextureManager.hpp"

#include "../Renderer/VFShaders.hpp"
#include "../Renderer/VAO.hpp"
#include "../Renderer/VBO.hpp"
#include "../Renderer/EBO.hpp"

#include "../Model/Model3D.hpp"
#include "../Model/Camera.hpp"
#include "../Model/Camera/PerspectiveCamera.hpp"
#include "../Model/Camera/OrthoCamera.hpp"
#include "../Model/Light.hpp"
#include "../Model/Light/PointLight.hpp"
#include "../Model/Skybox.hpp"

namespace controllers {
    using namespace renderers;
    using namespace models;
    
    class Game {
    private:
        GLFWwindow* window;

        VFShaders* BaseShaders;
        VFShaders* SkyShaders;

        Skybox* Sky;

        std::vector<std::vector<GLfloat>*> meshes;
        std::vector<GLuint*> textures;
        std::vector<GLuint*> normals;

        std::vector<VAO*> VAOs;
        std::vector<VBO*> VBOs;
        std::vector<EBO*> EBOs;

        std::vector<Camera*> Cameras;
        Camera* ActiveCam;

        std::vector<Light*> Lights;
        std::vector<Model3D*> Entities;

    public:
        Game();

    public:
        void run();

    private:
        void update();
        void render();
        void buffer();

    private:
        void createSkybox();
        void createShaders();
        void createMeshes();
        void createTextures();
        void createNormals();
        void createBuffers();
        void createObjects();
    };
}

#endif