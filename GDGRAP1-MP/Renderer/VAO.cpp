#include "VAO.hpp"

using namespace renderers;

// @brief VAO constructor; generates a new Vertex Array Object ID.
VAO::VAO() {
    glGenVertexArrays(1, &this->vertexArray);
}

// @brief Sets up the vertex attribute pointers for the VAO.
// @param dimensions[] - An integer array holding the number of components for each attribute in the vertex data
// @param attribs - An int variable specifying the number of attributes in the vertex data
void VAO::createPointers(int dimensions[], int attribs) {
    int totalAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        totalAttribs += dimensions[i];
    }

    int usedAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        GLintptr newPointer = usedAttribs * sizeof(float);
        glVertexAttribPointer(
            i,
            dimensions[i],
            GL_FLOAT,
            GL_FALSE,
            totalAttribs * sizeof(float),
            (void*)newPointer
        );
        glEnableVertexAttribArray(i);
        usedAttribs += dimensions[i];
    }

}

// @brief Binds the VAO, making it the currently active VAO for vertex attribute configuration.
void VAO::bind() {
    glBindVertexArray(this->vertexArray);
}

// @brief Unbinds the currently bound VAO so that it is no longer active.
void VAO::unbind() {
    glBindVertexArray(0);
}

// @brief Deletes the VAO from the OpenGL context, releasing GPU memory.
void VAO::deleteVertexArray() {
    glDeleteBuffers(1, &this->vertexArray);
}