#ifndef RENDERER_VBO_HPP
#define RENDERER_VBO_HPP

#include <vector>

#include <glad/glad.h>

namespace renderer {
    class VBO {
    private:
        GLuint vertexBuffer;

    public:
        VBO();

    public:
        void bufferData(std::vector<GLfloat> vertices);

    public:
        void bind();
        void unbind();
        void deleteVBO();
    };
}

#endif
