#include "Game.hpp"

using namespace controllers;

Game::Game() {
    /* Initialize the library */
    if (!glfwInit())
        exit(0);

    this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vaughn Vincent Cordero", NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        exit(0);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    //glfwSetKeyCallback(window, Key_Callback);

    this->createSkybox();
    this->createShaders();
    this->createMeshes();
    this->createTextures();
    this->createNormals();
    this->createBuffers();
    this->createObjects();
}

void Game::run() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
        
        this->update();

        this->render();

        glfwSwapBuffers(this->window);
    }

    for (VAO* p : this->VAOs) { p->deleteVertexArray(); }
    for (VBO* p : this->VBOs) { p->deleteVertexBuffer(); }

    this->SkyVAO->deleteVertexArray();
    this->SkyVBO->deleteVertexBuffer();
    this->SkyEBO->deleteElementBuffer();

    glfwTerminate();
}

void Game::update() {
    /*Update Game Objects Here*/


}

void Game::render() {
    /*Render objects here*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Render Here*/
    //Skybox render
    this->Sky->draw(this->ActiveCam);
    this->SkyVAO->bind();
    this->Sky->buffer();

    //object render
    for (int i = 0; i < this->Entities.size(); i++) {
        this->Entities[i]->draw(this->ActiveCam, this->Lights);
        this->VAOs[i]->bind();
        glDrawArrays(GL_TRIANGLES, 0, (*this->Entities[i]->getMesh()).size() / 14);
    }
}

void Game::createSkybox() {
    //shaders creation
    this->SkyShaders = new VFShaders("Shaders/Skybox.vert", "Shaders/Skybox.frag");

    const char* facesSkybox[]{
        "Skybox/rainbow_rt.png",
        "Skybox/rainbow_lf.png",
        "Skybox/rainbow_up.png",
        "Skybox/rainbow_dn.png",
        "Skybox/rainbow_ft.png",
        "Skybox/rainbow_bk.png"
    };

    //texture creation
    GLuint* skyTex = new GLuint;
    glGenTextures(1, skyTex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *skyTex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        TextureManager::getInstance()->load(facesSkybox[i], false, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }

    //object creation
    this->Sky = new Skybox(this->SkyShaders, skyTex);

    //buffer creation
    int skyDimensions[]{ 3 };

    this->SkyVAO = new VAO;
    this->SkyVBO = new VBO;
    this->SkyEBO = new EBO;

    this->SkyVAO->bind();

    this->SkyVBO->bind();
    this->SkyVBO->bufferData(this->Sky->getVertices());
    this->SkyVAO->createPointers(skyDimensions, 1);

    this->SkyEBO->bind();
    this->SkyEBO->bufferData(this->Sky->getIndices());

    this->SkyVAO->unbind();
}

void Game::createShaders() {
    this->BaseShaders = new VFShaders("Shaders/Default.vert", "Shaders/Default.frag");
}

void Game::createMeshes() {
    std::string meshPaths[]{
        "3D/Elf01_posed/Elf01_posed.obj"
        //, "3D/Cat Lamp/Cat Lamp.obj"
    };

    for (int i = 0; i < sizeof(meshPaths) / sizeof(std::string); i++) {
        this->meshes.push_back(new std::vector<GLfloat>(MeshManager::getInstance()->load(meshPaths[i])));
    }
}

void Game::createTextures() {
    std::string texPaths[]{
        "3D/brickwall.jpg"
        //, "3D/Cat Lamp/Cat_Lamp_Albedo.tga.png"
    };

    for (int i = 0; i < sizeof(texPaths) / sizeof(std::string); i++) {
        this->textures.push_back(new GLuint);
        glGenTextures(1, this->textures[i]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *this->textures[i]);

        TextureManager::getInstance()->load(texPaths[i].c_str(), true, GL_TEXTURE_2D);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Game::createNormals() {
    std::string normalPaths[]{
        "3D/brickwall_normal.jpg"
        //, "3D/Cat Lamp/Cat_Lamp_Normal.tga.png"
    };

    for (int i = 0; i < sizeof(normalPaths) / sizeof(std::string); i++) {
        this->normals.push_back(new GLuint);
        glGenTextures(1, this->normals[i]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, *this->normals[i]);

        TextureManager::getInstance()->load(normalPaths[i].c_str(), true, GL_TEXTURE_2D);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Game::createBuffers() {
    int dimensions[]{ 3,3,2,3,3 };

    for (int i = 0; i < this->meshes.size(); i++) {
        this->VAOs.push_back(new VAO);
        this->VBOs.push_back(new VBO);

        this->VAOs[i]->bind();
        this->VBOs[i]->bind();

        this->VBOs[i]->bufferData(*this->meshes[i]);
        this->VAOs[i]->createPointers(dimensions, 5);

        this->VBOs[i]->unbind();
        this->VAOs[i]->unbind();
        std::cout << "Buffers created." << std::endl;
    }
}

void Game::createObjects() {
    //Entity creation
    std::string entityNames[]{
        "Elf Girl"
        //, "Cat Lamp"
    };

    std::vector<Model3D*> Entities;
    for (int i = 0; i < sizeof(entityNames) / sizeof(std::string); i++) {
        this->Entities.push_back(new Model3D(
            entityNames[i],
            this->meshes[i],
            this->BaseShaders,
            this->textures[i],
            this->normals[i],
            0.05f,
            glm::vec3(0.0f, i * 0.5f, 0.0f)
        ));
    }

    //Elf Girl source: https://sketchfab.com/3d-models/elf-girl-52f2e84961b94760b7805c178890d644
    //Cat Lamp source: https://sketchfab.com/3d-models/uwu-cat-night-light-9c9767328ec54bf29c39765671e1033f

    //Camera creation
    this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    this->Cameras.push_back(new OrthoCamera(glm::vec3(0.0f, 1.0f, 5.0f)));
    //Setting Active Camera
    this->ActiveCam = this->Cameras[0];

    //Light creation
    this->Lights.push_back(new PointLight(glm::vec3(2.0f)));
    this->Lights.push_back(new DirLight(glm::vec3(4.0f, 11.0f, -3.0f)));
}