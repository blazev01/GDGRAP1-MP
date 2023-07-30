#ifndef RENDERERS_VAO_HPP
#define RENDERERS_VAO_HPP

#include <glad/glad.h>

namespace renderers {
	class VAO {
    private:
        GLuint vertexArray;     // Main VAO variable

    public:
        VAO();

    public:
        void createPointers(int dimensions[], int attribs);
    
    public:
        void bind();
        void unbind();
        void deleteVertexArray();
    };
}

#endif
