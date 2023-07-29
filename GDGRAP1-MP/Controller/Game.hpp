#ifndef CONTROLLERS_GAME_HPP
#define CONTROLLERS_GAME_HPP

#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "../Config/Settings.hpp"

#include "../Model/Enum/MeshType.hpp"

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

        VAO* SkyVAO;
        VBO* SkyVBO;
        EBO* SkyEBO;

        std::vector<std::vector<GLfloat>*> meshes;
        std::vector<GLuint*> textures;
        std::vector<GLuint*> normals;

        std::unordered_map<MeshType, VAO*> VAOs;
        std::unordered_map<MeshType, VBO*> VBOs;

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