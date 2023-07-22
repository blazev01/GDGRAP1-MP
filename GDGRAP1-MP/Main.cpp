#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tiny_obj_loader.h"

#include "stb_image.h"

#include "Controller/Game.hpp"

using namespace controller;
//
//const float width = 600.f;
//const float height = 600.f;
//const float aspect = width / height;
//
//const glm::mat4 identityMatrix = glm::mat4(1.0f);
//
//float thetaSpeed = 1.0f;
//float moveSpeed = 0.1f;
//
//float yawV = 0.0f;
//float pitchV = 0.0f;
//float rollV = 0.0f;
//
//float fbV = 0.0f;
//float rlV = 0.0f;
//float udV = 0.0f;

//void Key_Callback(
//    GLFWwindow* window,
//    int key, //key code
//    int scancode, //phys pos
//    int action, //press/release
//    int mod //modifier keys
//)
//
//{
//    if (key == GLFW_KEY_D &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        rlV = moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        rlV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_A &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        rlV = -moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        rlV = 0.0f;
//    }
//    
//    if (key == GLFW_KEY_S &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        fbV = moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        fbV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_W &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        fbV = -moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        fbV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_SPACE &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        udV = moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        udV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_C &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        udV = -moveSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        udV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_Q &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//    }
//    else if (action == GLFW_RELEASE) {
//
//    }
//
//    if (key == GLFW_KEY_E &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//
//    }
//    else if (action == GLFW_RELEASE) {
//
//    }
//
//    if (key == GLFW_KEY_LEFT &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        yawV = thetaSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        yawV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_RIGHT &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        yawV = -thetaSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        yawV = 0.0f;
//    }
//    
//    if (key == GLFW_KEY_UP &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        pitchV = thetaSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        pitchV = 0.0f;
//    }
//
//    if (key == GLFW_KEY_DOWN &&
//        action == GLFW_PRESS &&
//        action != GLFW_RELEASE) {
//        pitchV = -thetaSpeed;
//    }
//    else if (action == GLFW_RELEASE) {
//        pitchV = 0.0f;
//    }
//}
//
//class Shaders {
//private:
//    GLuint shaderProgram;
//
//public:
//    Shaders(std::string vertPath, std::string fragPath) {
//        this->shaderProgram = glCreateProgram();
//
//        createShader(vertPath, GL_VERTEX_SHADER);
//        createShader(fragPath, GL_FRAGMENT_SHADER);
//
//        glLinkProgram(this->shaderProgram);
//    }
//
//public:
//    void setFloat(const GLchar* varName, float f) {
//        glUseProgram(this->shaderProgram);
//        GLuint ambientStrLoc = glGetUniformLocation(this->shaderProgram, varName);
//        glUniform1f(ambientStrLoc, f);
//    }
//
//    void setVec3(const GLchar* varName, glm::vec3 v3) {
//        glUseProgram(this->shaderProgram);
//        GLuint lightLoc = glGetUniformLocation(this->shaderProgram, varName);
//        glUniform3fv(lightLoc, 1, glm::value_ptr(v3));
//    }
//    void setMat4(const GLchar* varName, glm::mat4 m4) {
//        glUseProgram(this->shaderProgram);
//        unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, varName);
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m4));
//    }
//
//    void setTexture(const GLchar* varName, GLenum active, GLuint* texture) {
//        glUseProgram(this->shaderProgram);
//        GLuint textureLoc = glGetUniformLocation(this->shaderProgram, varName);
//        glActiveTexture(active);
//        glBindTexture(GL_TEXTURE_2D, *texture);
//        glUniform1i(textureLoc, 0);
//    }
//
//private:
//    void createShader(std::string path, GLenum shaderType) {
//        std::fstream source(path);
//        std::stringstream buff;
//        buff << source.rdbuf();
//        std::string str = buff.str();
//        const char* c = str.c_str();
//
//        GLuint newShader = glCreateShader(shaderType);
//        glShaderSource(newShader, 1, &c, NULL);
//        glCompileShader(newShader);
//
//        glAttachShader(this->shaderProgram, newShader);
//    }
//};
//
//class VAO {
//private:
//    GLuint vertexArray;
//
//public:
//    VAO() {
//        glGenVertexArrays(1, &this->vertexArray);
//    }
//
//public:
//    template<size_t attribs>
//    void createPointers(int(&attribDimentions)[attribs]) {
//        int totalAttribs = 0;
//        for (int i = 0; i < attribs; i++) {
//            totalAttribs += attribDimentions[i];
//        }
//
//        int usedAttribs = 0;
//        for (int i = 0; i < attribs; i++) {
//            GLintptr newPointer = usedAttribs * sizeof(float);
//            glVertexAttribPointer(
//                i,
//                attribDimentions[i],
//                GL_FLOAT,
//                GL_FALSE,
//                totalAttribs * sizeof(float),
//                (void*)newPointer
//            );
//            glEnableVertexAttribArray(i);
//            usedAttribs += attribDimentions[i];
//        }
//        
//    }
//
//public:
//    void bind() {
//        glBindVertexArray(this->vertexArray);
//    }
//
//    void unbind() {
//        glBindVertexArray(0);
//    }
//    
//    void deleteVAO() {
//        glDeleteBuffers(1, &this->vertexArray);
//    }
//};
//
//class VBO {
//private:
//    GLuint vertexBuffer;
//
//public:
//    VBO() {
//        glGenBuffers(1, &this->vertexBuffer);
//    }
//
//public:
//    void BufferData(std::vector<GLfloat> vertices) {
//        glBufferData(
//            GL_ARRAY_BUFFER,
//            sizeof(GLfloat) * vertices.size(),
//            vertices.data(),
//            GL_STATIC_DRAW
//        );
//    }
//
//public:
//    void bind() {
//        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
//    }
//
//    void unbind() {
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//    }
//
//    void deleteVBO() {
//        glDeleteBuffers(1, &this->vertexBuffer);
//    }
//};
//
//class EBO {
//private:
//    GLuint elementBuffer;
//
//public:
//    EBO() {
//        glGenBuffers(1, &this->elementBuffer);
//    }
//
//public:
//    void BufferData(std::vector<GLuint> elements) {
//        glBufferData(
//            GL_ELEMENT_ARRAY_BUFFER,
//            sizeof(GLuint) * elements.size(),
//            elements.data(),
//            GL_STATIC_DRAW
//        );
//    }
//
//    /*void BufferSubData(std::vector<GLuint> elements) {
//        glBufferSubData(
//            GL_ELEMENT_ARRAY_BUFFER,
//            size of offset
//            sizeof(GLuint) * elements.size(),
//            (void*)vertices
//        );
//    }*/
//
//public:
//    void bind() {
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffer);
//    }
//
//    void unbind() {
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }
//
//    void deleteEBO() {
//        glDeleteBuffers(1, &this->elementBuffer);
//    }
//};
//
//class Model3D {
//private:
//    std::vector<GLfloat> vertexData;
//
//public:
//    Model3D(std::string path) {
//        tinyobj::attrib_t attributes;
//        std::vector<tinyobj::shape_t> shapes;
//        std::vector<tinyobj::material_t> material;
//        std::string warning, error;
//
//        bool success = tinyobj::LoadObj(
//            &attributes,
//            &shapes,
//            &material,
//            &warning,
//            &error,
//            path.c_str()
//        );
//
//        if (!success) {
//            std::cout << error << std::endl;
//        }
//        else {
//            for (int i = 0; i < shapes.size(); i++) {
//                for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
//                    tinyobj::index_t vData = shapes[i].mesh.indices[j];
//
//                    this->vertexData.push_back(attributes.vertices[vData.vertex_index * 3]);
//                    this->vertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 1]);
//                    this->vertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 2]);
//
//                    if (!attributes.normals.empty()) {
//                        this->vertexData.push_back(attributes.normals[vData.normal_index * 3]);
//                        this->vertexData.push_back(attributes.normals[vData.normal_index * 3 + 1]);
//                        this->vertexData.push_back(attributes.normals[vData.normal_index * 3 + 2]);
//                    }
//
//                    this->vertexData.push_back(attributes.texcoords[vData.texcoord_index * 2]);
//                    this->vertexData.push_back(attributes.texcoords[vData.texcoord_index * 2 + 1]);
//                }
//            }
//        }
//    }
//
//public:
//    std::vector<GLfloat> getVertexData() {
//        return this->vertexData;
//    }
//};
//
//class TextureLoader {
//public:
//    GLuint load(const char* path, GLenum active) {
//        int imgWidth;
//        int imgHeight;
//        int colorChannels;
//
//        unsigned char* data = stbi_load(
//            path,
//            &imgWidth,
//            &imgHeight,
//            &colorChannels,
//            0
//        );
//
//        int channels = 0;
//        if (colorChannels == 3)
//            channels = GL_RGB;
//        else if (colorChannels > 3)
//            channels = GL_RGBA;
//
//        GLuint texture;
//        glGenTextures(1, &texture);
//        glActiveTexture(active);
//        glBindTexture(GL_TEXTURE_2D, texture);
//
//        glTexImage2D(
//            GL_TEXTURE_2D,
//            0,
//            channels,
//            imgWidth,
//            imgHeight,
//            0,
//            channels,
//            GL_UNSIGNED_BYTE,
//            data
//        );
//
//        glGenerateMipmap(GL_TEXTURE_2D);
//        stbi_image_free(data);
//
//        return texture;
//    }
//};
//
//class Material {
//private:
//    std::string name;
//
//    glm::vec3 diffuseCol;
//    glm::vec3 ambientCol;
//    glm::vec3 specularCol;
//
//    float ambientStr;
//    float specularStr;
//
//    float shininess;
//
//public:
//    Material(std::string name) {
//        this->name = "Material";
//
//        this->diffuseCol = glm::vec3(1.0f, 1.0f, 1.0f);
//        this->ambientCol = glm::vec3(1.0f, 1.0f, 1.0f);
//        this->specularCol = glm::vec3(1.0f, 1.0f, 1.0f);
//
//        this->ambientStr = 0.1f;
//        this->specularStr = 0.5f;
//
//        this->shininess = 16.0f;
//    }
//
//    Material(
//        std::string name,
//        glm::vec3 diffuseCol,
//        glm::vec3 ambientCol,
//        glm::vec3 specularCol,
//        float ambientStr,
//        float specularStr,
//        float shininess
//    ) {
//        this->name = name;
//
//        this->diffuseCol = diffuseCol;
//        this->ambientCol = ambientCol;
//        this->specularCol = specularCol;
//
//        this->ambientStr = ambientStr;
//        this->specularStr = specularStr;
//
//        this->shininess = shininess;
//    }
//
//public:
//    std::string getName() {
//        return this->name;
//    }
//
//    void setName(std::string name) {
//        this->name = name;
//    }
//
//    glm::vec3 getDiffuseCol() {
//        return this->diffuseCol;
//    }
//
//    void setDiffuseCol(glm::vec3 diffuseCol) {
//        this->diffuseCol = diffuseCol;
//    }
//
//    glm::vec3 getAmbientCol() {
//        return this->ambientCol;
//    }
//
//    void setAmbientCol(glm::vec3 ambientCol) {
//        this->ambientCol = ambientCol;
//    }
//    
//    glm::vec3 getSpecularCol() {
//        return this->specularCol;
//    }
//
//    void setSpecularCol(glm::vec3 specularCol) {
//        this->specularCol = specularCol;
//    }
//
//    float getAmbientStr() {
//        return this->ambientStr;
//    }
//
//    void setAmbientStr(float ambientStr) {
//        this->ambientStr = ambientStr;
//    }
//
//    float getSpecularStr() {
//        return this->specularStr;
//    }
//
//    void setSpecularStr(float specularStr) {
//        this->specularStr = specularStr;
//    }
//
//    float getShininess() {
//        return this->shininess;
//    }
//
//    void setShininess(float shininess) {
//        this->shininess = shininess;
//    }
//};
//
//class Transformable {
//protected:
//    glm::mat4 transformation;
//
//public:
//    Transformable(glm::vec3 position = glm::vec3(0.0f)) {
//        this->transformation = identityMatrix;
//        this->translate(position);
//    }
//
//public:
//    void translate(glm::vec3 translation) {
//        this->transformation = glm::translate(
//            this->transformation,
//            translation
//        );
//    }
//
//    void translate(float x, float y, float z) {
//        this->translate(glm::vec3(x, y, z));
//    }
//
//    void scale(glm::vec3 escalation) {
//        this->transformation = glm::scale(
//            this->transformation,
//            escalation
//        );
//    }
//
//    void scale(float x, float y, float z) {
//        this->scale(glm::vec3(x, y, z));
//    }
//
//    void scale(float scalar) {
//        this->scale(glm::vec3(scalar, scalar, scalar));
//    }
//
//    void rotate(float theta, glm::vec3 axis) {
//        this->transformation = glm::rotate(
//            this->transformation,
//            glm::radians(theta),
//            glm::normalize(axis)
//        );
//    }
//
//    void rotate(float theta, float x, float y, float z) {
//        this->rotate(theta, glm::vec3(x, y, z));
//    }
//
//public:
//    glm::mat4 getTransformation() {
//        return this->transformation;
//    }
//};
//
//class Camera {
//protected:
//    glm::vec3 position;
//    glm::vec3 rotation;
//
//    float distance;
//    glm::vec3 center;
//    glm::vec3 worldUp;
//    glm::mat4 view;
//    glm::mat4 projection;
//
//public:
//    Camera(glm::vec3 position) {
//        this->position = position;
//        this->rotation = glm::vec3(0.0f);
//
//        this->distance = 10.0f;
//        this->worldUp = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
//        this->center = this->position - this->computeFront(this->distance);
//        this->view = glm::lookAt(this->position, this->center, this->worldUp);
//
//        this->projection = glm::mat4(1.0f);
//    }
//
//public:
//    void move(float fb, float rl, float ud) {
//        if(fb) this->position += this->computeFront(fb);
//        if(rl) this->position += this->computeRight(rl);
//        if(ud) this->position.y += ud;
//
//        this->center = this->position - this->computeFront(this->distance);
//        this->view = glm::lookAt(this->position, this->center, this->worldUp);
//    }
//
//    void tilt(float x, float y, float z) {
//        this->rotation += glm::vec3(x, y, z);
//
//        this->center = this->position - this->computeFront(this->distance);
//        this->view = glm::lookAt(this->position, this->center, this->worldUp);
//    }
//
//protected:
//    glm::vec3 computeFront(float distance = 1.0f) {
//        glm::vec3 front(0.0f, 0.0f, 0.0f);
//        front.x = distance * sin(glm::radians(this->rotation.x)) * sin(glm::radians(this->rotation.z));
//        front.y = distance * cos(glm::radians(this->rotation.y)) * sin(glm::radians(this->rotation.z));
//        front.z = distance * cos(glm::radians(this->rotation.x)) * cos(glm::radians(this->rotation.y));
//        return front;
//    }
//    glm::vec3 computeRight(float distance = 1.0f) {
//        glm::vec3 right(0.0f, 0.0f, 0.0f);
//        right.x = distance * cos(glm::radians(this->rotation.z));
//        right.z = distance * sin(glm::radians(this->rotation.x));
//        return right;
//    }
//
//public:
//    glm::vec3 getPosition() {
//        return this->position;
//    }
//
//    glm::mat4 getView() {
//        return this->view;
//    }
//
//    glm::mat4 getProjection() {
//        return this->projection;
//    }
//};
//
//class PerspectiveCamera
//: public Camera {
//private:
//    float fov;
//    float near;
//    float far;
//
//public:
//    PerspectiveCamera(glm::vec3 position, float fov = 45.f)
//        : Camera(position) {
//        this->fov = fov;
//        this->near = 0.1f;
//        this->far = 100.0f;
//        this->projection = this->computeProjection();
//    }
//
//private:
//    glm::mat4 computeProjection() {
//        return glm::perspective(
//            glm::radians(this->fov),
//            aspect,
//            this->near,
//            this->far
//        );
//    }
//
//public:
//    float getFOV() {
//        return this->fov;
//    }
//
//    void setFOV(float fov) {
//        this->fov = fov;
//        this->projection = this->computeProjection();
//    }
//
//    float getNear() {
//        return this->near;
//    }
//
//    void setNear(float near) {
//        this->near = near;
//        this->projection = this->computeProjection();
//    }
//
//    float getFar() {
//        return this->far;
//    }
//
//    void setFar(float far) {
//        this->far = far;
//        this->projection = this->computeProjection();
//    }
//
//};
//
//class OrthoCamera
//    : public Camera {
//private:
//    float near;
//    float far;
//
//public:
//    OrthoCamera(glm::vec3 position)
//        : Camera(position) {
//        this->near = -1.0f;
//        this->far = 1.0f;
//        this->projection = this->computeProjection();
//    }
//
//private:
//    glm::mat4 computeProjection() {
//        return glm::ortho(
//            -0.5f,
//            0.5f,
//            -0.5f,
//            0.5f,
//            this->near,
//            this->far
//        );
//    }
//
//public:
//    float getNear() {
//        return this->near;
//    }
//
//    void setNear(float near) {
//        this->near = near;
//        this->projection = this->computeProjection();
//    }
//
//    float getFar() {
//        return this->far;
//    }
//
//    void setFar(float far) {
//        this->far = far;
//        this->projection = this->computeProjection();
//    }
//
//};
//
//class Light {
//protected:
//    glm::vec3 position;
//
//    glm::vec3 diffuseCol;
//    glm::vec3 ambientCol;
//    glm::vec3 specularCol;
//
//    float ambientStr;
//    float specularStr;
//
//    float shininess;
//
//public:
//    Light(glm::vec3 position) {
//        this->position = position;
//        this->diffuseCol = glm::vec3(1.0f, 1.0f, 1.0f);
//        this->ambientCol = glm::vec3(1.0f, 1.0f, 1.0f);
//        this->specularCol = glm::vec3(1.0f, 1.0f, 1.0f);
//
//        this->ambientStr = 0.1f;
//        this->specularStr = 0.5f;
//
//        this->shininess = 16.0f;
//    }
//
//public:
//    glm::vec3 getPosition() {
//        return this->position;
//    }
//
//    void setPosition(glm::vec3 position) {
//        this->position = position;
//    }
//
//    glm::vec3 getDiffuseCol() {
//        return this->diffuseCol;
//    }
//
//    void setDiffuseCol(glm::vec3 diffuseCol) {
//        this->diffuseCol = diffuseCol;
//    }
//
//    glm::vec3 getAmbientCol() {
//        return this->ambientCol;
//    }
//
//    void setAmbientCol(glm::vec3 ambientCol) {
//        this->ambientCol = ambientCol;
//    }
//
//    glm::vec3 getSpecularCol() {
//        return this->specularCol;
//    }
//
//    void setSpecularCol(glm::vec3 specularCol) {
//        this->specularCol = specularCol;
//    }
//
//    float getAmbientStr() {
//        return this->ambientStr;
//    }
//
//    void setAmbientStr(float ambientStr) {
//        this->ambientStr = ambientStr;
//    }
//
//    float getSpecularStr() {
//        return this->specularStr;
//    }
//
//    void setSpecularStr(float specularStr) {
//        this->specularStr = specularStr;
//    }
//
//    float getShininess() {
//        return this->shininess;
//    }
//
//    void setShininess(float shininess) {
//        this->shininess = shininess;
//    }
//};
//
//class PointLight : public Light {
//private:
//    float constant;
//    float linear;
//    float quadratic;
//
//public:
//    PointLight(glm::vec3 position)
//    : Light(position) {
//        this->constant = 1.0;
//        this->linear = 0.02;
//        this->quadratic = 0.0015;
//    }
//
//public:
//    float getConstant() {
//        return this->constant;
//    }
//
//    void setConstant(float constant) {
//        this->constant = constant;
//    }
//
//    float getLinear() {
//        return this->linear;
//    }
//
//    void setLinear(float linear) {
//        this->linear = linear;
//    }
//
//    float getQuadratic() {
//        return this->quadratic;
//    }
//
//    void setQuadratic(float quadratic) {
//        this->quadratic = quadratic;
//    }
//};
//
//class SpotLight : public Light {
//private:
//    glm::vec3 direction;
//    float cutOff;
//
//public:
//    SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff = 1.0f)
//    : Light(position) {
//        this->direction = direction;
//        this->cutOff = cutOff;
//    }
//
//public:
//    glm::vec3 getDirection() {
//        return this->direction;
//    }
//
//    void setDirection(glm::vec3 direction) {
//        this->direction = direction;
//    }
//
//    float getCutoff() {
//        return this->cutOff;
//    }
//
//    void setCutOff(float cutOff) {
//        this->cutOff = cutOff;
//    }
//};
//
//class Skybox {
//private:
//    float vertices[24]{
//        -1.f, -1.f,  1.f,
//         1.f, -1.f,  1.f,
//         1.f, -1.f, -1.f,
//        -1.f, -1.f, -1.f,
//        -1.f,  1.f,  1.f,
//         1.f,  1.f,  1.f,
//         1.f,  1.f, -1.f,
//        -1.f,  1.f, -1.f
//    };
//
//    unsigned int indices[36]{
//        1,2,6,
//        6,5,1,
//
//        0,4,7,
//        7,3,0,
//
//        4,5,6,
//        6,7,4,
//
//        0,3,2,
//        2,1,0,
//
//        0,1,5,
//        5,4,0,
//
//        3,7,6,
//        6,2,3
//    };
//
//    unsigned int texture;
//
//    unsigned int VAO;
//    unsigned int VBO;
//    unsigned int EBO;
//
//public:
//    Skybox(std::string* faces) {
//        this->texture = 0;
//        glGenTextures(1, &this->texture);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
//
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//        stbi_set_flip_vertically_on_load(false);
//
//        for (unsigned int i = 0; i < 6; i++) {
//            int w, h, skyColChannel;
//
//            unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &skyColChannel, 0);
//
//            if (data) {
//                glTexImage2D(
//                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                    0,
//                    GL_RGB,
//                    w,
//                    h,
//                    0,
//                    GL_RGB,
//                    GL_UNSIGNED_BYTE,
//                    data
//                );
//            }
//
//            stbi_image_free(data);
//        }
//
//        stbi_set_flip_vertically_on_load(true);
//
//        glGenVertexArrays(1, &this->VAO);
//        glGenBuffers(1, &this->VBO);
//        glGenBuffers(1, &this->EBO);
//
//        glBindVertexArray(this->VAO);
//
//        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//    }
//
//public:
//    void draw(Shaders& VFShaders, Camera& Cam) {
//        glDepthMask(GL_FALSE);
//        glDepthFunc(GL_LEQUAL);
//
//        glm::mat4 view = glm::mat4(1.0f);
//        view = glm::mat4(glm::mat3(Cam.getView()));
//        
//        VFShaders.setMat4("projection", Cam.getProjection());
//        VFShaders.setMat4("view", view);
//
//        glBindVertexArray(this->VAO);
//
//        glActiveTexture(0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
//
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//        glDepthMask(GL_TRUE);
//        glDepthFunc(GL_LESS);
//    }
//
//    void deleteBuffers() {
//        glDeleteVertexArrays(1, &this->VAO);
//        glDeleteBuffers(1, &this->VBO);
//        glDeleteBuffers(1, &this->EBO);
//    }
//};
//
//
//class Entity : public Transformable {
//private:
//    std::string name;
//    Model3D* Model;
//    GLuint* texture;
//    Material* Mat;
//
//public:
//    Entity(std::string name, Model3D* Model, GLuint* texture, Material* Mat, glm::vec3 position = glm::vec3(0.0f))
//        : Transformable(position) {
//        this->name = name;
//        this->Model = Model;
//        this->texture = texture;
//        this->Mat = Mat;
//    }
//
//public:
//    void draw(Shaders& VFShaders, Camera& Cam, Light& Lit) {
//        VFShaders.setMat4("transform", this->transformation);
//        VFShaders.setMat4("view", Cam.getView());
//        VFShaders.setMat4("projection", Cam.getProjection());
//
//        VFShaders.setTexture("tex0", GL_TEXTURE0, this->texture);
//        VFShaders.setVec3("cameraPos", Cam.getPosition());
//
//        this->drawLight(VFShaders, Lit);
//    }
//
//private:
//    void drawLight(Shaders& VFShaders, Light& Lit) {
//        VFShaders.setVec3("lightPos", Lit.getPosition());
//        VFShaders.setVec3("diffuseColor", Lit.getDiffuseCol());
//        VFShaders.setFloat("ambientStr", Lit.getAmbientStr());
//        VFShaders.setVec3("ambientColor", Lit.getAmbientCol());
//        VFShaders.setFloat("specularStr", Lit.getSpecularStr());
//        VFShaders.setVec3("specularColor", Lit.getSpecularCol());
//        VFShaders.setFloat("shininess", Lit.getShininess());
//    }
//};
//

int main(void) {
    Game MyGame = Game();

    MyGame.run();

    //GLFWwindow* window;
    //float center[2] = { 0, 0 };

    ///* Initialize the library */
    //if (!glfwInit())
    //    return -1;

    ///* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(width, height, "Vaughn Vincent Cordero", NULL, NULL);
    //if (!window)
    //{
    //    glfwTerminate();
    //    return -1;
    //}

    ///* Make the window's context current */
    //glfwMakeContextCurrent(window);
    //gladLoadGL();

    //glViewport(0, 0, width, height);

    //stbi_set_flip_vertically_on_load(true);

    //glEnable(GL_DEPTH_TEST);

    //glfwSetKeyCallback(window, Key_Callback);

    ////Loading in Shaders
    //Shaders BaseShaders = Shaders("Shaders/Default.vert", "Shaders/Default.frag");
    //Shaders SkyboxShaders = Shaders("Shaders/Skybox.vert", "Shaders/Skybox.frag");

    ////Load obj
    //TextureLoader TexLdr;

    //Model3D Bunny("3D/djSword.obj");
    //GLuint Waifu = TexLdr.load("3D/Matoi.Ryuuko.jpg", GL_TEXTURE0);
    //Material DefaultMat("Default Material");

    //std::vector<Entity*> Entities;
    //Entities.push_back(new Entity("Lola Bunny", &Bunny, &Waifu, &DefaultMat));
    //Entities.push_back(new Entity("Lola Bunny", &Bunny, &Waifu, &DefaultMat, glm::vec3(1.0f, 0.0f, -1.0f)));

    //std::vector<GLfloat> fullVertexData;
    //fullVertexData = Bunny.getVertexData();

    //Entities[0]->scale(0.05f);
    //Entities[1]->scale(0.05f);
    //Entities[1]->rotate(90.0f, 0.0f, 1.0f, 0.0f);

    //PointLight BaseLight(glm::vec3(10.0f, 3.0f, 10.0f));

    //PerspectiveCamera BasePCam(glm::vec3(0.0f, 1.0f, 10.0f));

    //std::string facesSkybox[]{
    //    "Skybox/rainbow_rt.png",
    //    "Skybox/rainbow_lf.png",
    //    "Skybox/rainbow_up.png",
    //    "Skybox/rainbow_dn.png",
    //    "Skybox/rainbow_ft.png",
    //    "Skybox/rainbow_bk.png"
    //};

    //Skybox BaseSky(facesSkybox);

    //VAO BaseVAO;
    //VBO BaseVBO;

    //BaseVAO.bind();
    //BaseVBO.bind();

    //BaseVBO.BufferData(Bunny.getVertexData());
    //
    //int dimensions[] = { 3, 3, 2 };
    //
    //BaseVAO.createPointers(dimensions);

    //BaseVAO.unbind();
    //BaseVBO.unbind();

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window)) {
    //    if (fbV || rlV || udV) BasePCam.move(fbV, rlV, udV);
    //    if (yawV || pitchV || rollV) BasePCam.tilt(yawV, pitchV, rollV);

    //    Entities[0]->rotate(1.0f, 0.0f, 1.0f, 0.0f);
    //    Entities[1]->rotate(1.0f, 1.0f, 0.0f, 0.0f);

    //    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    /* Create drawable here */
    //    BaseSky.draw(SkyboxShaders, BasePCam);

    //    for (Entity* p : Entities) {
    //        p->draw(BaseShaders, BasePCam, BaseLight);
    //        
    //        BaseVAO.bind();
    //        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
    //    }

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    //BaseVAO.deleteVAO();
    //BaseVBO.deleteVBO();
    //BaseSky.deleteBuffers();
    ////glDeleteBuffers(1, &VBO_UV);
    ////glDeleteBuffers(1, &EBO);

    //glfwTerminate();
    return 0;
}