#include "VAO.hpp"

using namespace renderer;

VAO::VAO() {
    glGenVertexArrays(1, &this->vertexArray);
}

template<size_t attribs>
void VAO::createPointers(int(&attribDimentions)[attribs]) {
    int totalAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        totalAttribs += attribDimentions[i];
    }

    int usedAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        GLintptr newPointer = usedAttribs * sizeof(float);
        glVertexAttribPointer(
            i,
            attribDimentions[i],
            GL_FLOAT,
            GL_FALSE,
            totalAttribs * sizeof(float),
            (void*)newPointer
        );
        glEnableVertexAttribArray(i);
        usedAttribs += attribDimentions[i];
    }

}

void VAO::bind() {
    glBindVertexArray(this->vertexArray);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::deleteVAO() {
    glDeleteBuffers(1, &this->vertexArray);
}