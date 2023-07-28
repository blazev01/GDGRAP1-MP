#ifndef RENDERERS_VBO_HPP
#define RENDERERS_VBO_HPP

#include <vector>

#include <glad/glad.h>

namespace renderers {
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
        void deleteVertexBuffer();
    };
}

#endif
