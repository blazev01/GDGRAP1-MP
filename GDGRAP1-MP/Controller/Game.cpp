#include "Game.hpp"

using namespace controller;

Game::Game() : window(glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vaughn Vincent Cordero", NULL, NULL)) {
    float center[2] = { 0, 0 };

    /* Initialize the library */
    if (!glfwInit())
        exit(0);

    if (!this->window)
    {
        glfwTerminate();
        exit(0);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    //glfwSetKeyCallback(window, Key_Callback);

    this->BaseShaders = new VFShaders("Shaders/Default.vert", "Shaders/Default.frag");
    this->SkyboxShaders = new VFShaders("Shaders/Skybox.vert", "Shaders/Skybox.frag");

    this->mesh = MeshManager::getInstance()->load("3D/djSword.obj");
    this->Waifu = TextureManager::getInstance()->load("3D/Matoi.Ryuuko.jpg", GL_TEXTURE0);
    //Material DefaultMat("Default Material");

    
    this->Entities.push_back(new Model3D("Lola Bunny 1", mesh, Waifu, 0.5f));
    this->Entities.push_back(new Model3D("Lola Bunny 2", mesh, Waifu, 0.5f, glm::vec3(1.0f, 0.0f, -1.0f)));

    this->Entities[1]->rotate(90.0f, 0.0f, 1.0f, 0.0f);

    this->BaseLight = new PointLight(glm::vec3(10.0f, 3.0f, 10.0f));
    this->BasePCam = new PerspectiveCamera(glm::vec3(0.0f, 1.0f, 10.0f));

    std::string facesSkybox[]{
        "Skybox/rainbow_rt.png",
        "Skybox/rainbow_lf.png",
        "Skybox/rainbow_up.png",
        "Skybox/rainbow_dn.png",
        "Skybox/rainbow_ft.png",
        "Skybox/rainbow_bk.png"
    };

    this->BaseSky = new Skybox(facesSkybox);

    BaseVAO.bind();
    BaseVBO.bind();

    BaseVBO.bufferData(*mesh);
    
    int dimensions[] = { 3, 3, 2 };
    
    BaseVAO.createPointers(dimensions);

    BaseVAO.unbind();
    BaseVBO.unbind();
}

void Game::run() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
        
        this->update();

        this->render();

        this->buffer();
    }

    this->BaseVAO.deleteVAO();
    this->BaseVBO.deleteVBO();
    this->BaseSky->deleteBuffers();

    glfwTerminate();
}

void Game::update() {
    /*Update Game Objects Here*/
    this->Entities[0]->rotate(1.0f, 0.0f, 1.0f, 0.0f);
    this->Entities[1]->rotate(1.0f, 1.0f, 0.0f, 0.0f);
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Render Here*/
    this->BaseSky->render(*SkyboxShaders, *BasePCam);
    this->BaseSky->buffer();

    for (Model3D* p : Entities) {
        p->draw(*BaseShaders, *BasePCam, *BaseLight);
            
        BaseVAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, (*mesh).size() / 8);
    }
    glfwSwapBuffers(this->window);
}

void Game::buffer() {
    /*Draw From Buffers Here*/
    
}