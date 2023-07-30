#ifndef RENDERERS_EBO_HPP
#define RENDERERS_EBO_HPP

#include <vector>

#include <glad/glad.h>

namespace renderers {
    class EBO {
    private:
        GLuint elementBuffer;   // Main EBO variable

    public:
        EBO();

    public:
        void bufferData(std::vector<GLuint> elements);

    public:
        void bind();
        void unbind();
        void deleteElementBuffer();
    };
}

#endif
