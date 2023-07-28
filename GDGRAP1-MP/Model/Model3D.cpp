#include "Model3D.hpp"

using namespace models;

Model3D::Model3D(
    std::string name,
    std::vector<GLfloat>* mesh,
    VFShaders* Shaders,
    GLuint* texture,
    GLuint* normalMap,
    float scale,
    glm::vec3 position) {
    this->name = name;
    this->mesh = mesh;
    this->Shaders = Shaders;
    this->texture = texture;
    this->normalMap = normalMap;
    this->transformation = glm::mat4(1.0f);
    this->translate(position);
    this->scale(scale);
}

void Model3D::draw(Camera* Cam, std::vector<Light*> Lights) {
    this->Shaders->setMat4("transform", this->transformation);
    this->Shaders->setMat4("view", Cam->getView());
    this->Shaders->setMat4("projection", Cam->getProjection());

    for (Light* p : Lights) {
        this->drawLight(Cam, p);
    }

    this->Shaders->setTexture("tex0", this->texture, GL_TEXTURE0, GL_TEXTURE_2D, 0);
    this->Shaders->setTexture("normTex", this->normalMap, GL_TEXTURE1, GL_TEXTURE_2D, 1);
}

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

void Model3D::setPosition(glm::vec3 position) {
    this->transformation = glm::translate(glm::mat4(this->transformation[1][1]), position);
}

std::vector<GLfloat>* Model3D::getMesh() {
    return this->mesh;
}

glm::mat4 Model3D::getTransformation() {
    return this->transformation;
}