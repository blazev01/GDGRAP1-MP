#ifndef RENDERERS_VF_SHADERS_HPP
#define RENDERERS_VF_SHADERS_HPP

#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace renderers {
    class VFShaders {
    private:
        GLuint shaderProgram;

    public:
        VFShaders(std::string vertPath, std::string fragPath);

    public:
        void setBool(const GLchar* varName, bool b);
        void setFloat(const GLchar* varName, float f);
        void setVec3(const GLchar* varName, glm::vec3 v3);
        void setMat4(const GLchar* varName, glm::mat4 m4);
        void setTexture(const GLchar* varName, GLuint* texture, GLenum active, GLenum type, GLint unit);

    private:
        void createShader(std::string path, GLenum shaderType);
    
    public:
        GLuint& getShaderProgram();
    };
}

#endif