#include "EBO.hpp"

using namespace renderers;

// @brief EBO constructor; generates a new Element Buffer Object ID.
EBO::EBO() {
    glGenBuffers(1, &this->elementBuffer);
}

// @brief Allocates and initializes a data store for a buffer object; 
// @param elements - A vector containing the index data that needs to be stored in the EBO
void EBO::bufferData(std::vector<GLuint> elements) {
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * elements.size(),
        elements.data(),
        GL_STATIC_DRAW
    );
}

// @brief Binds the EBO, making it the currently active EBO for vertex attribute configuration.
void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

// @brief Unbinds the currently bound EBO so that it is no longer active.
void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// @brief Deletes the EBO from the OpenGL context, releasing GPU memory.
void EBO::deleteElementBuffer() {
    glDeleteBuffers(1, &this->elementBuffer);
}