#include "Model3D.hpp"

using namespace models;

Model3D::Model3D(
    std::string name,
    std::vector<GLfloat>* model3D,
    GLuint* texture,
    //Material* Mat,
    float scale,
    glm::vec3 position) {
    this->name = name;
    this->mesh = mesh;
    this->texture = texture;
    //this->Mat = Mat;

    this->translate(position);
    this->scale(scale);
}

void Model3D::draw(VFShaders& Shaders, Camera& Cam, Light& Lit) {
    Shaders.setMat4("transform", this->transformation);
    Shaders.setMat4("view", Cam.getView());
    Shaders.setMat4("projection", Cam.getProjection());

    Shaders.setTexture("tex0", GL_TEXTURE0, this->texture);
    Shaders.setVec3("cameraPos", Cam.getPosition());

    this->drawLight(Shaders, Lit);
}

void Model3D::drawLight(VFShaders& Shaders, Light& Lit) {
    Shaders.setVec3("lightPos", Lit.getPosition());
    Shaders.setVec3("diffuseColor", Lit.getDiffuseCol());
    Shaders.setFloat("ambientStr", Lit.getAmbientStr());
    Shaders.setVec3("ambientColor", Lit.getAmbientCol());
    Shaders.setFloat("specularStr", Lit.getSpecularStr());
    Shaders.setVec3("specularColor", Lit.getSpecularCol());
    Shaders.setFloat("shininess", Lit.getShininess());
}

void Model3D::translate(glm::vec3 translation) {
    this->transformation = glm::translate(
        this->transformation,
        translation
    );
}

void Model3D::translate(float x, float y, float z) {
    this->translate(glm::vec3(x, y, z));
}

void Model3D::scale(glm::vec3 escalation) {
    this->transformation = glm::scale(
        this->transformation,
        escalation
    );
}

void Model3D::scale(float x, float y, float z) {
    this->scale(glm::vec3(x, y, z));
}

void Model3D::scale(float scalar) {
    this->scale(glm::vec3(scalar, scalar, scalar));
}

void Model3D::rotate(float theta, glm::vec3 axis) {
    this->transformation = glm::rotate(
        this->transformation,
        glm::radians(theta),
        glm::normalize(axis)
    );
}

void Model3D::rotate(float theta, float x, float y, float z) {
    this->rotate(theta, glm::vec3(x, y, z));
}

std::vector<GLfloat>* Model3D::getMesh() {
    return this->mesh;
}

glm::mat4 Model3D::getTransformation() {
    return this->transformation;
}