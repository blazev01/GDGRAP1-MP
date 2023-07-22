#ifndef RENDERER_VAO_HPP
#define RENDERER_VAO_HPP

#include <glad/glad.h>

namespace renderer {
	class VAO {
    private:
        GLuint vertexArray;

    public:
        VAO();

    public:
        template<size_t attribs>
        void createPointers(int(&attribDimentions)[attribs]);
    
    public:
        void bind();
        void unbind();
        void deleteVAO();
    };
}

#endif
