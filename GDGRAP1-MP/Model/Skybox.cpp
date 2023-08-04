#include "Skybox.hpp"
#include "iostream"
using namespace models;

// Main constructor for the Skybox class.
// @param Shaders - Pointer to the Shader used for rendering the skybox
// @param texture - Pointer containing the textureID for the skybox's cube map texture
Skybox::Skybox(VFShaders* Shaders, GLuint* texture) {
    this->texture = texture;
    this->Shaders = Shaders;
}

// @brief Sets up the view and projection matrices for rendering the skybox.
// @param Cam - Pointer to the Camera used for rendering the view of the scene
void Skybox::draw(Camera* Cam) {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(Cam->getView()));

    this->Shaders->setMat4("projection", Cam->getProjection());
    this->Shaders->setMat4("view", view);
}

// @brief Renders the skybox on the screen; draws the cube with the skybox texture.
void Skybox::buffer() {
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *this->texture);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void Skybox::setShaders(VFShaders* Shaders) {
    this->Shaders = Shaders;
}

// @brief Returns a vector containing the vertex data of the skybox.
// @return vertices
std::vector<GLfloat> Skybox::getVertices() {
    std::vector<GLfloat> vertices;
    for (int i = 0; i < 24; i++) {
        vertices.push_back(this->vertices[i]);
    }
    return vertices;
}

// @brief Returns a vector containing the index data of the skybox.
// @return indices
std::vector<GLuint> Skybox::getIndices() {
    std::vector<GLuint> indices;
    for (int i = 0; i < 36; i++) {
        indices.push_back(this->indices[i]);
    }
    return indices;
}