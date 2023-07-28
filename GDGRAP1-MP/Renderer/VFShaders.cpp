#include "VFShaders.hpp"

using namespace renderers;

VFShaders::VFShaders(std::string vertPath, std::string fragPath) {
    this->shaderProgram = glCreateProgram();

    createShader(vertPath, GL_VERTEX_SHADER);
    createShader(fragPath, GL_FRAGMENT_SHADER);

    glLinkProgram(this->shaderProgram);
}

void VFShaders::setFloat(const GLchar* varName, float f) {
    glUseProgram(this->shaderProgram);
    GLuint ambientStrLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform1f(ambientStrLoc, f);
}

void VFShaders::setVec3(const GLchar* varName, glm::vec3 v3) {
    glUseProgram(this->shaderProgram);
    GLuint lightLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform3fv(lightLoc, 1, glm::value_ptr(v3));
}
void VFShaders::setMat4(const GLchar* varName, glm::mat4 m4) {
    glUseProgram(this->shaderProgram);
    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m4));
}

void VFShaders::setTexture(const GLchar* varName, GLuint* texture, GLenum active, GLenum type, GLint unit) {
    glUseProgram(this->shaderProgram);
    GLuint textureLoc = glGetUniformLocation(this->shaderProgram, varName);
    glActiveTexture(active);
    glBindTexture(type, *texture);
    glUniform1i(textureLoc, unit);
}

void VFShaders::createShader(std::string path, GLenum shaderType) {
    std::fstream source(path);
    std::stringstream buff;
    buff << source.rdbuf();
    std::string str = buff.str();
    const char* c = str.c_str();

    GLuint newShader = glCreateShader(shaderType);
    glShaderSource(newShader, 1, &c, NULL);
    glCompileShader(newShader);

    glAttachShader(this->shaderProgram, newShader);
}

GLuint& VFShaders::getShaderProgram() {
    return this->shaderProgram;
}