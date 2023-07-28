#include "Skybox.hpp"
#include "iostream"
using namespace models;

Skybox::Skybox(VFShaders* Shaders, GLuint* texture) {
    this->texture = texture;
    this->Shaders = Shaders;
}

void Skybox::draw(Camera* Cam) {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(Cam->getView()));

    this->Shaders->setMat4("projection", Cam->getProjection());
    this->Shaders->setMat4("view", view);
}

void Skybox::buffer() {
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *this->texture);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

std::vector<GLfloat> Skybox::getVertices() {
    std::vector<GLfloat> vertices;
    for (int i = 0; i < 24; i++) {
        vertices.push_back(this->vertices[i]);
    }
    return vertices;
}

std::vector<GLuint> Skybox::getIndices() {
    std::vector<GLuint> indices;
    for (int i = 0; i < 36; i++) {
        indices.push_back(this->indices[i]);
    }
    return indices;
}