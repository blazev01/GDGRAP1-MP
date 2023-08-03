#include "Game.hpp"

bool isOrbitingRight = false;
bool isOrbitingLeft = false;
bool isOrbitingUp = false;
bool isOrbitingDown = false;
bool isLookingRight = false;
bool isLookingLeft = false;
bool isLookingUp = false;
bool isLookingDown = false;
bool isTurningRight = false;
bool isTurningLeft = false;
bool isMovingForward = false;
bool isMovingBackward = false;

int tiltMargin = 64;

bool spaceToggled = false;

bool LMB = false;
bool LMBPressed = false;

int activeCam = 0;

float thetaSpeed = 1.0f;
float moveSpeed = 0.1f;
float lightSpeed = 0.01f;
float tiltSpeed = 0.0002;

float yaw = 0.0f;
float pitch = 0.0f;
float roll = 0.0f;

float rV = 0.0f;
float gV = 0.0f;
float bV = 0.0f;

float xV = 0.0f;
float yV = 0.0f;
float zV = 0.0f;

float pIntensity = 0.0f;
float dIntensity = 0.0f;

double lastX = 0;
double lastY = 0;

double clickX = 0;
double clickY = 0;

float xTilt = 0.0f;
float yTilt = 0.0f;

//for ortho cam
float xOrtho = 0;
float yOrtho = yV + 25.0f;
float zOrtho = 1.0f;

glm::vec3 orthoPos = glm::vec3(xOrtho, yOrtho, zOrtho);

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
        isMovingForward = true;
    }
    else if (key == GLFW_KEY_S &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        isMovingBackward = true;
    }
    else if ((key == GLFW_KEY_W ||
        key == GLFW_KEY_S) &&
        action == GLFW_RELEASE) {
        isMovingForward = false;
        isMovingBackward = false;
    }

    if (key == GLFW_KEY_D &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        isTurningRight = true;
    }
    else if (key == GLFW_KEY_A &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        isTurningLeft = true;
    }
    else if ((key == GLFW_KEY_D ||
        key == GLFW_KEY_A) &&
        action == GLFW_RELEASE) {
        isTurningRight = false;
        isTurningLeft = false;
    }

    if (key == GLFW_KEY_Q &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        yV = moveSpeed;
    }
    else if (key == GLFW_KEY_E &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        yV = -moveSpeed;
    }
    else if ((key == GLFW_KEY_Q ||
        key == GLFW_KEY_E) &&
        action == GLFW_RELEASE) {
        yV = 0.0f;
    }

    if (key == GLFW_KEY_I &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) rV = -lightSpeed;
        else yaw = -thetaSpeed;
    }
    else if (key == GLFW_KEY_K &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) rV = lightSpeed;
        else yaw = thetaSpeed;
    }
    else if ((key == GLFW_KEY_I ||
        key == GLFW_KEY_K) &&
        action == GLFW_RELEASE) {
        if (spaceToggled)  rV = 0.0f;
        else yaw = 0.0f;
    }

    if (key == GLFW_KEY_L &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) gV = lightSpeed;
        else pitch = thetaSpeed;
    }
    else if (key == GLFW_KEY_J &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) gV = -lightSpeed;
        else pitch = -thetaSpeed;
    }
    else if ((key == GLFW_KEY_L ||
        key == GLFW_KEY_J) &&
        action == GLFW_RELEASE) {
        if (spaceToggled)  gV = 0.0f;
        else pitch = 0.0f;
    }

    if (key == GLFW_KEY_U &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) bV = lightSpeed;
        else roll = thetaSpeed;
    }
    else if (key == GLFW_KEY_O &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) bV = -lightSpeed;
        else roll = -thetaSpeed;
    }
    else if ((key == GLFW_KEY_U ||
        key == GLFW_KEY_O) &&
        action == GLFW_RELEASE) {
        if (spaceToggled)  bV = 0.0f;
        else roll = 0.0f;
    }

    if (key == GLFW_KEY_UP &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) pIntensity = lightSpeed;

    }
    else if (key == GLFW_KEY_DOWN &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) pIntensity = -lightSpeed;
    }
    else if ((key == GLFW_KEY_UP ||
        key == GLFW_KEY_DOWN) &&
        action == GLFW_RELEASE) {
        pIntensity = 0.0f;
    }

    if (key == GLFW_KEY_RIGHT &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) dIntensity = lightSpeed;
    }
    else if (key == GLFW_KEY_LEFT &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        if (spaceToggled) dIntensity = -lightSpeed;
    }
    else if ((key == GLFW_KEY_RIGHT ||
        key == GLFW_KEY_LEFT) &&
        action == GLFW_RELEASE) {
        dIntensity = 0.0f;
    }

    if (key == GLFW_KEY_SPACE &&
        action == GLFW_RELEASE) {
        spaceToggled = !spaceToggled;
        if (spaceToggled) std::cout << "true" << std::endl;
        else std::cout << "false" << std::endl;
    }

    if (key == GLFW_KEY_1 &&
        action == GLFW_RELEASE) {
        if (activeCam == 1 || activeCam == 2) activeCam = 0;
        else if (activeCam == 0 || activeCam == 2) activeCam = 1;
        std::cout << "Camera: " << activeCam << std::endl;
    }

    if (key == GLFW_KEY_2 &&
        action == GLFW_RELEASE) {
        if (activeCam == 0 || activeCam == 1) activeCam = 2;
        else if (activeCam == 2) activeCam = 0;
        std::cout << "Camera: " << activeCam << std::endl;
    }

}

void cursorPosCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{
    if (LMBPressed) {
        clickX = xPos;
        clickY = yPos;
        LMBPressed = false;
    }

    if (LMB && xPos != clickX) {
        double deltaPosX = xPos - clickX;
        if(deltaPosX > tiltMargin) isOrbitingRight = true;
        else if (deltaPosX < -tiltMargin) isOrbitingLeft = true;
    }

    if (LMB && yPos != clickY) {
        double deltaPosY = yPos - clickY;
        if (deltaPosY > tiltMargin) isOrbitingUp = true;
        else if (deltaPosY < -tiltMargin) isOrbitingDown = true;
    }
}

void mouseButtonCallback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT &&
        action == GLFW_PRESS &&
        action != GLFW_RELEASE) {
        LMBPressed = true;
        LMB = true;
    }
    else if (action == GLFW_RELEASE) {
        LMB = false;
        isOrbitingRight = false;
        isOrbitingLeft = false;
        isOrbitingUp = false;
        isOrbitingDown = false;
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
    if (isOrbitingRight) {
        this->Player1->setIsOrbitingRight(true);
    }
    else if (isOrbitingLeft) {
        this->Player1->setIsOrbitingLeft(true);
    }

    if (isOrbitingUp) {
        this->Player1->setIsOrbitingUp(true);
    }
    else if (isOrbitingDown) {
        this->Player1->setIsOrbitingDown(true);
    }

    if (isLookingRight) {
        isLookingRight = false;
        this->Player1->setIsLookingRight(true);
    }
    else if (isLookingLeft) {
        isLookingLeft = false;
        this->Player1->setIsLookingLeft(true);
    }

    if (isLookingUp) {
        isLookingUp = false;
        this->Player1->setIsLookingUp(true);
    }
    else if (isLookingDown) {
        isLookingDown = false;
        this->Player1->setIsLookingDown(true);
    }

    if (isTurningRight) {
        this->Player1->setIsTurningRight(true);
    }
    else if (isTurningLeft) {
        this->Player1->setIsTurningLeft(true);
    }

    if (isMovingForward) {
        this->Player1->setIsMovingForward(true);
    }
    else if (isMovingBackward) {
        this->Player1->setIsMovingBackward(true);
    }

}

void Game::update() {
    /*Update Game Objects Here*/
    this->ActiveCam = this->Cameras[activeCam];

    this->Player1->turn(this->Entities[0]);
    this->Player1->circle(this->Cameras[0]);
    this->Player1->move(this->Entities[0], this->Cameras[0]);
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


    /*
    glm::vec3 FPovPos = glm::vec3(xV, yV, zV);
    glm::vec3 FPovCenter = FPovPos;

    PerspectiveCamera FirstPov(FPovPos, FPovCenter, 45.0f);

    glm::vec3 TPovPos = glm::vec3(xV, 0, 1.0f);

    PerspectiveCamera ThirdPov(TPovPos, FPovCenter, 45.0f);
    */

    //this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    //Camera creation
    this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, 5.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f)));//0, 3rd pov
    this->Cameras.push_back(new PerspectiveCamera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(-1.0f, 1.0f, 0.0f)));//1, 1st pov
    this->Cameras.push_back(new OrthoCamera(orthoPos));//2, top down
    //this->Cameras.push_back(new OrthoCamera(glm::vec3(0.0f, yV + 25.0f, 1.0f))); original
    //Setting Active Camera
    this->ActiveCam = this->Cameras[0];

    std::cout << "Current Camera: " << activeCam << std::endl;

    //Light creation
    this->Lights.push_back(new PointLight(glm::vec3(2.0f)));
    this->Lights.push_back(new DirLight(glm::vec3(20.0f, 20.0f, 20.0f)));

    Player1 = new Player(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}