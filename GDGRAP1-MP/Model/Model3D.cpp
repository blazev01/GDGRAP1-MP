#include "Model3D.hpp"

using namespace models;

// @brief Main constructor of the Model3D class.
// @param name - Name of the 3D model
// @param Type - Enum variable denoting the type of mesh the model has
// @param mesh - Pointer to a vector representing the mesh data of the model
// @param Shaders - Pointer to the VFShaders class representing the shaders used for the model
// @param texture - Pointer to the texture ID for the model's texture
// @param normalMap - Pointer to the texture ID for the model's normal map
// @param scale - Initial scale factor (size) of the model
// @param position - Initial position of the model in 3D space
Model3D::Model3D(
    std::string name,
    MeshType Type,
    std::vector<GLfloat>* mesh,
    VFShaders* Shaders,
    GLuint* texture,
    GLuint* normalMap,
    float scale,
    glm::vec3 position) {
    this->name = name;
    this->Type = Type;
    this->mesh = mesh;
    this->Shaders = Shaders;
    this->texture = texture;
    this->normalMap = normalMap;
    this->transformation = glm::mat4(1.0f);
    this->translate(position);
    this->scale(scale);
}

// @brief Draws/Renders the 3D models with appropriate textures, shading, and lighting.
// @param Cam - Pointer to the Camera representing the view of the scene
// @param Lights - Vector of pointers to Light representing the lighting in the scene
void Model3D::draw(Camera* Cam, std::vector<Light*> Lights) {
    this->Shaders->setMat4("transform", this->transformation);
    this->Shaders->setMat4("view", Cam->getView());
    this->Shaders->setMat4("projection", Cam->getProjection());

    for (Light* p : Lights) {
        this->drawLight(Cam, p);
    }

    bool hasTexture = this->texture != NULL;
    this->Shaders->setBool("hasTexture", hasTexture);
    if (hasTexture) this->Shaders->setTexture("tex0", this->texture, GL_TEXTURE0, GL_TEXTURE_2D, 0);
    
    bool hasNormal = this->normalMap != NULL;
    this->Shaders->setBool("hasNormal", hasNormal);
    if (hasNormal) this->Shaders->setTexture("normTex", this->normalMap, GL_TEXTURE1, GL_TEXTURE_2D, 1);
}

// @brief Manages the lighting of models with respect to the camera position.
// @param Cam - Pointer to the Camera representing the view of the scene
// @param Lit - Pointer to the Light representing the light used for shading
void Model3D::drawLight(Camera* Cam, Light* Lit) {
    std::string lightPos = Lit->getType() + ".position";

    std::string diffCol = Lit->getType() + ".diffuseCol";
    std::string ambiCol = Lit->getType() + ".ambientCol";
    std::string specCol = Lit->getType() + ".specularCol";

    std::string ambiStr = Lit->getType() + ".ambientStr";
    std::string specStr = Lit->getType() + ".specularStr";
    
    std::string shine = Lit->getType() + ".shininess";

    this->Shaders->setVec3("cameraPos", Cam->getPosition());

    this->Shaders->setVec3(lightPos.c_str(), Lit->getPosition());
    this->Shaders->setVec3(diffCol.c_str(), Lit->getDiffuseCol());
    this->Shaders->setVec3(ambiCol.c_str(), Lit->getAmbientCol());
    this->Shaders->setVec3(specCol.c_str(), Lit->getSpecularCol());

    this->Shaders->setFloat(ambiStr.c_str(), Lit->getAmbientStr());
    this->Shaders->setFloat(specStr.c_str(), Lit->getSpecularStr());
    
    this->Shaders->setFloat(shine.c_str(), Lit->getShininess());

    if (Lit->getType() == "PLight") {
        PointLight* PLight = (PointLight*)Lit;
        std::string con = Lit->getType() + ".con";
        std::string lin = Lit->getType() + ".lin";
        std::string quad = Lit->getType() + ".quad";

        this->Shaders->setFloat(con.c_str(), PLight->getConstant());
        this->Shaders->setFloat(lin.c_str(), PLight->getLinear());
        this->Shaders->setFloat(quad.c_str(), PLight->getQuadratic());
    }
}

// @brief Handles the transformation of the model via vector.
// @param translation - A vector containing the offset values for the model's position
void Model3D::translate(glm::vec3 translation) {
    this->transformation = glm::translate(
        this->transformation,
        translation
    );
}

// @brief Handles the translation of the model via float values.
// @param x - X component of the offset value
// @param y - Y component of the offset value
// @param z - Z component of the offset value
void Model3D::translate(float x, float y, float z) {
    this->translate(glm::vec3(x, y, z));
}

// @brief Handles the scale transformation of the model via vector.
// @param escalation - Vector containing the value for scaling the model's size
void Model3D::scale(glm::vec3 escalation) {
    this->transformation = glm::scale(
        this->transformation,
        escalation
    );
}

// @brief Handles the scale transformation of the model via different float values.
// @param x - X component of the scale value
// @param y - Y component of the scale value
// @param z - Z component of the scale value
void Model3D::scale(float x, float y, float z) {
    this->scale(glm::vec3(x, y, z));
}

// @brief Handles the scale transformation of the model via a single float value to be added to all axes.
// @param scalar - Acts as both X, Y, and Z components of the scale value
void Model3D::scale(float scalar) {
    this->scale(glm::vec3(scalar, scalar, scalar));
}

// @brief Rotates the model at a given angle around a specified axis.
// @param theta - The angle (in radians) by which to tilt the model
// @param axis - Axis of rotation where the model rotates around
void Model3D::rotate(float theta, glm::vec3 axis) {
    this->transformation = glm::rotate(
        this->transformation,
        glm::radians(theta),
        glm::normalize(axis)
    );
}

// @brief Rotates the model by a given angle around a specified axis, but provided as individual x, y, and z components.
// @param theta - The angle (in radians) by which to tilt the model
// @param x - X component of the axis of rotation
// @param y - Y component of the axis of rotation
// @param z - Z component of the axis of rotation
void Model3D::rotate(float theta, float x, float y, float z) {
    this->rotate(theta, glm::vec3(x, y, z));
}

// @brief Sets the model's current position to a given value.
// @param position - The model's new position
void Model3D::setPosition(glm::vec3 position) {
    this->transformation = glm::translate(glm::mat4(this->transformation[1][1]), position);
}

// @brief Returns the model's mesh type.
MeshType Model3D::getMeshType() {
    return this->Type;
}

// @brief Returns the model's mesh
std::vector<GLfloat>* Model3D::getMesh() {
    return this->mesh;
}

// @brief Returns the model's transformation matrix
glm::mat4 Model3D::getTransformation() {
    return this->transformation;
}

glm::vec3 Model3D::getPosition() {
    return glm::vec3(this->transformation[3][0], this->transformation[3][1], this->transformation[3][2]);
}