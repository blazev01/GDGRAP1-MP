#include "VBO.hpp"

using namespace renderers;

// @brief Main class of the Vertex Buffer Object.
VBO::VBO() {
    glGenBuffers(1, &this->vertexBuffer);
}

// @brief Allocates and initializes a data store for a buffer object; loads data into the created VBO.
// @param vertices - A vector containing the vertex data to be stored in the VBO
void VBO::bufferData(std::vector<GLfloat> vertices) {
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertices.size(),
        vertices.data(),
        GL_STATIC_DRAW
    );
}

// @brief Used to bind the VBO, making it the currently active buffer for vertex attribute data.
void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

// @brief Unbinds the currently bound VAO, making it inactive.
void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// @brief Deletes the VBO from the OpenGL context, releasing GPU memory.
void VBO::deleteVertexBuffer() {
    glDeleteBuffers(1, &this->vertexBuffer);
}