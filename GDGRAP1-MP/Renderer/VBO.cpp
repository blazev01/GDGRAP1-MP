#include "VBO.hpp"

using namespace renderer;

VBO::VBO() {
    glGenBuffers(1, &this->vertexBuffer);
}

void VBO::bufferData(std::vector<GLfloat> vertices) {
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertices.size(),
        vertices.data(),
        GL_STATIC_DRAW
    );
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() {
    glDeleteBuffers(1, &this->vertexBuffer);
}