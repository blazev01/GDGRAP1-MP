#include "TextureManager.hpp"

using namespace controller;

GLuint* TextureManager::load(const char* path, GLenum active) {
    int imgWidth;
    int imgHeight;
    int colorChannels;

    unsigned char* data = stbi_load(
        path,
        &imgWidth,
        &imgHeight,
        &colorChannels,
        0
    );

    int channels = 0;
    if (colorChannels == 3)
        channels = GL_RGB;
    else if (colorChannels > 3)
        channels = GL_RGBA;

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(active);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        channels,
        imgWidth,
        imgHeight,
        0,
        channels,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return &texture;
}

TextureManager* TextureManager::SHARED_INSTANCE = NULL;

TextureManager::TextureManager() {}
TextureManager::TextureManager(const TextureManager&) {}

TextureManager* TextureManager::getInstance() {
    if (SHARED_INSTANCE == NULL)
        SHARED_INSTANCE = new TextureManager();

    return SHARED_INSTANCE;
}