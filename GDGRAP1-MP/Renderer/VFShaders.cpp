#include "VFShaders.hpp"

using namespace renderers;

// @brief Main class of the Vertex and Fragment Shaders.
// @param vertPath - A string variable holding the file path of the vertex shader
// @param fragPath - A string variable with the file path of the fragment shader
VFShaders::VFShaders(std::string vertPath, std::string fragPath) {
    this->shaderProgram = glCreateProgram();

    createShader(vertPath, GL_VERTEX_SHADER);
    createShader(fragPath, GL_FRAGMENT_SHADER);

    glLinkProgram(this->shaderProgram);
}

void VFShaders::setBool(const GLchar* varName, bool b) {
    glUseProgram(this->shaderProgram);
    GLuint boolLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform1i(boolLoc, b);
}

// @brief Helps set float-based values on shader variables, while the primary function is to set Ambient Strength.
// @param varName - The designated variable located inside the shader
// @param f - The float value to be set on varName
void VFShaders::setFloat(const GLchar* varName, float f) {
    glUseProgram(this->shaderProgram);
    GLuint floatLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform1f(floatLoc, f);
}

// @brief Helps set vec3 (vector) values on shader variables, while the primary function is to set Light Position.
// @param varName - The designated variable located inside the shader
// @param v3 - The vec3 value to be set on varName
void VFShaders::setVec3(const GLchar* varName, glm::vec3 v3) {
    glUseProgram(this->shaderProgram);
    GLuint vec3Loc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform3fv(vec3Loc, 1, glm::value_ptr(v3));
}

// @brief Helps set mat4 (matrix) values on shader variables, while the primary function is to set a model's Transformation Matrix.
// @param varName - The designated variable located inside the shader
// @param m4 - The mat4 value to be set on varName
void VFShaders::setMat4(const GLchar* varName, glm::mat4 m4) {
    glUseProgram(this->shaderProgram);
    GLuint mat4Loc = glGetUniformLocation(this->shaderProgram, varName);
    glUniformMatrix4fv(mat4Loc, 1, GL_FALSE, glm::value_ptr(m4));
}

// @brief Sets the texture of a 3D model.
// @param varName - The designated variable located inside the shader
// @param texture - A pointer to the loaded texture
// @param active - An enum variable denoting which GL_TEXTURE type is used
// @param type - An enum variable that represents the type of texture to be bound (e.g.: GL_TEXTURE_2D)
// @param unit - An integer that specifies the texture unit index
void VFShaders::setTexture(const GLchar* varName, GLuint* texture, GLenum active, GLenum type, GLint unit) {
    glUseProgram(this->shaderProgram);
    GLuint textureLoc = glGetUniformLocation(this->shaderProgram, varName);
    glActiveTexture(active);
    glBindTexture(type, *texture);
    glUniform1i(textureLoc, unit);
}

// @brief The main function for creating the shaders to be linked into the shader program.
// @param path - The file path of the shader
// @param shaderType - The type of shader to be created
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

// @brief Finds and returns the Shader Program used by the class variable.
// @return this->shaderProgram (GLuint variable)
GLuint& VFShaders::getShaderProgram() {
    return this->shaderProgram;
}