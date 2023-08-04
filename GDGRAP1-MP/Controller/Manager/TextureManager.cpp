#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"

using namespace controllers;

// @brief Loads the texture for the model and sets the loaded texture as a 2D image.
// @param path - The file path of the texture file to be loaded.
// @param flipVert - A boolean variable toggling whether the texture should be flipped vertically.
// @param target - A GLenum variable showing what type of texture it will load (e.g. GL_TEXTURE_2D).
void TextureManager::load(const char* path, bool flipVert, GLenum target) {
    stbi_set_flip_vertically_on_load(flipVert);
    
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

    glTexImage2D(
        target,
        0,
        channels,
        imgWidth,
        imgHeight,
        0,
        channels,
        GL_UNSIGNED_BYTE,
        data
    );

    stbi_image_free(data);
}

// @brief Singleton Content for Texture Manager, allowing it to be called on other files without an instantiated variable provided the file path is part of the #include files.
TextureManager* TextureManager::SHARED_INSTANCE = NULL;

TextureManager::TextureManager() {}
TextureManager::TextureManager(const TextureManager&) {}

TextureManager* TextureManager::getInstance() {
    if (SHARED_INSTANCE == NULL)
        SHARED_INSTANCE = new TextureManager();

    return SHARED_INSTANCE;
}