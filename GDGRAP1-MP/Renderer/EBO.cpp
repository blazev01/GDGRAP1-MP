#include "EBO.hpp"

using namespace renderer;

EBO::EBO() {
    glGenBuffers(1, &this->elementBuffer);
}

void EBO::bufferData(std::vector<GLuint> elements) {
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLfloat) * elements.size(),
        elements.data(),
        GL_STATIC_DRAW
    );
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteEBO() {
    glDeleteBuffers(1, &this->elementBuffer);
}