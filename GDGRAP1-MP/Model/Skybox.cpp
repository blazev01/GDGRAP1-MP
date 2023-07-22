#include "Skybox.hpp"

using namespace models;

Skybox::Skybox(std::string* faces) {
    this->texture = 0;
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyColChannel;

        unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &skyColChannel, 0);

        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(true);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
}

void Skybox::render(VFShaders& Shaders, Camera& Cam) {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(Cam.getView()));

    Shaders.setMat4("projection", Cam.getProjection());
    Shaders.setMat4("view", view);
}

void Skybox::buffer() {
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glBindVertexArray(this->VAO);

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void Skybox::deleteBuffers() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}