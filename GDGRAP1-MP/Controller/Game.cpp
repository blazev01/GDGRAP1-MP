#include "Game.hpp"

bool released1 = false;
bool released2 = false;
bool releasedF = false;

bool draggingLMBRight = false;
bool draggingLMBLeft = false;
bool draggingLMBUp = false;
bool draggingLMBDown = false;

bool holdingQ = false;
bool holdingW = false;
bool holdingE = false;
bool holdingA = false;
bool holdingS = false;
bool holdingD = false;


bool LMB = false;
bool LMBPressed = false;

double lastX = 0;
double lastY = 0;

double clickX = 0;
double clickY = 0;

int dragMargin = 64;

ViewTag CurrentView = ViewTag::THIRD_PERSON;


void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod
)
{
    if (key == GLFW_KEY_W &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingW = true;
    }
    else if (key == GLFW_KEY_W &&
        action == GLFW_RELEASE) {
        holdingW = false;
    }

    if (key == GLFW_KEY_S &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingS = true;
    }
    else if (
        key == GLFW_KEY_S &&
        action == GLFW_RELEASE) {
        holdingS = false;
    }

    if (key == GLFW_KEY_D &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingD = true;
    }
    else if (key == GLFW_KEY_D &&
        action == GLFW_RELEASE) {
        holdingD = false;
    }

    if (key == GLFW_KEY_A &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingA = true;
    }
    else if (key == GLFW_KEY_A &&
        action == GLFW_RELEASE) {
        holdingA = false;
    }

    if (key == GLFW_KEY_Q &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingQ = true;
    }
    else if (key == GLFW_KEY_Q &&
        action == GLFW_RELEASE) {
        holdingQ = false;
    }

    if (key == GLFW_KEY_E &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        holdingE = true;
    }
    else if (key == GLFW_KEY_E &&
        action == GLFW_RELEASE) {
        holdingE = false;
    }

    if (key == GLFW_KEY_F &&
        action == GLFW_RELEASE) {
        releasedF = true;
    }

    if (key == GLFW_KEY_1 &&
        action == GLFW_RELEASE) {
        released1 = true;
    }

    if (key == GLFW_KEY_2 &&
        action == GLFW_RELEASE) {
        released2 = true;
    }

}

void cursorPosCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{
    if (LMBPressed) {
        LMBPressed = false;
        clickX = xPos;
        clickY = yPos;
    }

    if (LMB && xPos != clickX) {
        double deltaPosX = xPos - clickX;
        if(deltaPosX > dragMargin) draggingLMBRight = true;
        else if (deltaPosX < -dragMargin) draggingLMBLeft = true;
    }

    if (LMB && yPos != clickY) {
        double deltaPosY = yPos - clickY;
        if (deltaPosY > dragMargin) draggingLMBUp = true;
        else if (deltaPosY < -dragMargin) draggingLMBDown = true;
    }
}

void mouseButtonCallback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
)
{
    if (CurrentView == ViewTag::THIRD_PERSON &&
        button == GLFW_MOUSE_BUTTON_LEFT &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        LMBPressed = true;
        LMB = true;
    }
    else if (action == GLFW_RELEASE) {
        LMB = false;
        draggingLMBRight = false;
        draggingLMBLeft = false;
        draggingLMBUp = false;
        draggingLMBDown = false;
    }

}


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


    glfwSetKeyCallback(this->window, keyCallback);
    glfwSetCursorPosCallback(this->window, cursorPosCallback);
    glfwSetMouseButtonCallback(this->window, mouseButtonCallback);


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
        this->processEvents();

        this->update();

        this->render();

        glfwSwapBuffers(this->window);

        glfwPollEvents();
    }

    for (Model3D* p : this->Entities) {
        if (this->VAOs[p->getMeshType()] != NULL) {
            this->VAOs[p->getMeshType()]->deleteVertexArray();
            delete this->VAOs[p->getMeshType()];
        }

        if (this->VBOs[p->getMeshType()] != NULL) {
            this->VBOs[p->getMeshType()]->deleteVertexBuffer();
            delete this->VBOs[p->getMeshType()];
        }
    }

    this->SkyVAO->deleteVertexArray();
    this->SkyVBO->deleteVertexBuffer();
    this->SkyEBO->deleteElementBuffer();

    glfwTerminate();
}

void Game::processEvents() {
    if (released1) {
        released1 = false;
        this->Player1->setTogglePersonView(true);
    }
    else if (released2) {
        released2 = false;
        this->Player1->setToggleOverhead(true);
    }

    if (draggingLMBRight) this->Player1->setIsOrbitingRight(true);
    else if (draggingLMBLeft) this->Player1->setIsOrbitingLeft(true);

    if (draggingLMBUp) this->Player1->setIsOrbitingUp(true);
    else if (draggingLMBDown) this->Player1->setIsOrbitingDown(true);


    switch (CurrentView) {
    case ViewTag::THIRD_PERSON:
        if (holdingW) this->Player1->setIsMovingForward(true);
        else if (holdingS) this->Player1->setIsMovingBackward(true);
        
        if (holdingD) this->Player1->setIsTurningRight(true);
        else if (holdingA) this->Player1->setIsTurningLeft(true);
        break;

    case ViewTag::FIRST_PERSON:
        if (holdingW) this->Player1->setIsLookingDown(true);
        else if (holdingS) this->Player1->setIsLookingUp(true);

        if (holdingD) this->Player1->setIsLookingRight(true);
        else if (holdingA) this->Player1->setIsLookingLeft(true);
        
        //if (holdingE) this->Player1->setIsTurningRight(true);
        //else if (holdingQ) this->Player1->setIsTurningLeft(true);
        break;

    case ViewTag::OVERHEAD:

        break;

    default:
        break;
    }
}

void Game::update() {
    /*Update Game Objects Here*/
    this->Player1->swapView();
    CurrentView = this->Player1->getCurrentView();
    this->ActiveCam = this->Cameras[(int)CurrentView];

    switch (CurrentView) {
    case ViewTag::THIRD_PERSON:
        this->Player1->circle(this->Cameras[0]);
        this->Player1->turn(this->Entities[0], this->Lights[0], this->Cameras[1]);
        this->Player1->move(this->Entities[0], this->Lights[0], this->Cameras[0], this->Cameras[1]);
        break;
    case ViewTag::FIRST_PERSON:
        this->Player1->look(this->Cameras[1]);
        break;
    case ViewTag::OVERHEAD:

        break;

    default:
        break;
    }
    
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
        this->VAOs[this->Entities[i]->getMeshType()]->bind();
        glDrawArrays(GL_TRIANGLES, 0, (*this->Entities[i]->getMesh()).size() / 14);
    }
}

void Game::createSkybox() {
    //shaders creation
    this->SkyShaders = new VFShaders("Shaders/Skybox.vert", "Shaders/Skybox.frag");

    const char* facesSkybox[]{
        "Skybox/nightsky_rt.png",
        "Skybox/nightsky_lf.png",
        "Skybox/nightsky_up.png",
        "Skybox/nightsky_dn.png",
        "Skybox/nightsky_ft.png",
        "Skybox/nightsky_bk.png"
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
        "3D/panzer_tank/panzer_tank_fixed.obj",
        "3D/Grass_Terrain/Grass_Terrain_Fixed.obj"
        //"3D/Watermelon/watermelon.obj"
        //, "3D/Cat Lamp/Cat Lamp.obj"
    };

    for (int i = 0; i < sizeof(meshPaths) / sizeof(std::string); i++) {
        this->meshes.push_back(new std::vector<GLfloat>(MeshManager::getInstance()->load(meshPaths[i])));
    }
}

void Game::createTextures() {
    std::string texPaths[]{
        "3D/brickwall.jpg",
        "3D/Grass_Terrain/Grass_Terrain.jpg"
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
        "3D/brickwall_normal.jpg",
        //"3D/Watermelon/watermelon.jpg",
        // "3D/brickwall_normal.jpg
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
    MeshType types[]{
        MeshType::MODEL_01,
        MeshType::MODEL_02
        //MeshType::MODEL_03
    };

    int dimensions[]{ 3,3,2,3,3 };

    for (int i = 0; i < this->meshes.size(); i++) {
        this->VAOs[types[i]] = new VAO;
        this->VBOs[types[i]] = new VBO;

        this->VAOs[types[i]]->bind();
        this->VBOs[types[i]]->bind();

        this->VBOs[types[i]]->bufferData(*this->meshes[i]);
        this->VAOs[types[i]]->createPointers(dimensions, 5);

        this->VBOs[types[i]]->unbind();
        this->VAOs[types[i]]->unbind();
        std::cout << "Buffers created." << std::endl;
    }
}

void Game::createObjects() {
    //Entity creation

    std::vector<Model3D*> Entities;
    this->Entities.push_back(new Model3D(
        "Tank",
        MeshType::MODEL_01,
        this->meshes[0],
        this->BaseShaders,
        this->textures[0],
        this->normals[0],
        1.0f
    ));

    this->Entities.push_back(new Model3D(
        "Grass Plain",
        MeshType::MODEL_02,
        this->meshes[1],
        this->BaseShaders,
        this->textures[1],
        NULL,
        0.1f
    ));

    //Elf Girl source: https://sketchfab.com/3d-models/elf-girl-52f2e84961b94760b7805c178890d644
    //Cat Lamp source: https://sketchfab.com/3d-models/uwu-cat-night-light-9c9767328ec54bf29c39765671e1033f
    //tank source: https://free3d.com/3d-model/tank-low-poly-712984.html


    //Camera creation
    float tankHeight = 1.5f;
    this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, tankHeight + 5.0f, -10.0f), glm::vec3(0.0f, tankHeight + 0.0f, 0.0f)));//0, 3rd pov
    this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, tankHeight, 0.0f), glm::vec3(0.0f, tankHeight, 1.0f)));//1, 1st pov
    this->Cameras.push_back(new OrthoCamera(glm::vec3(0.0f, 50.0f, -1.0f), glm::vec3(0.0f), 10.0f, 0.1f, 200.0f));//2, top down
    
    //Setting Active Camera
    this->ActiveCam = this->Cameras[(int)CurrentView];

    //Light creation
    this->Lights.push_back(new PointLight(this->Cameras[1]->getCenter()));
    this->Lights.push_back(new DirLight(glm::vec3(20.0f, 20.0f, 20.0f)));

    Player1 = new Player(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), CurrentView);
}