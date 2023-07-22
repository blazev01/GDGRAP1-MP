#ifndef RENDERER_EBO_HPP
#define RENDERER_EBO_HPP

#include <vector>

#include <glad/glad.h>

namespace renderer {
    class EBO {
    private:
        GLuint elementBuffer;

    public:
        EBO();

    public:
        void bufferData(std::vector<GLuint> elements);

    public:
        void bind();
        void unbind();
        void deleteEBO();
    };
}

#endif
