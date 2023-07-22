#ifndef CONTROLLER_TEXTURE_MANAGER_HPP
#define CONTROLLER_TEXTURE_MANAGER_HPP

#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../stb_image.h"

namespace controller {
	class TextureManager {
    private:
        //std::vector< GLuint*> textures;

    public:
        GLuint* load(const char* path, GLenum active);
        //GLuint* getTexture();

    private:
        static TextureManager* SHARED_INSTANCE;

    private:
        TextureManager();
        TextureManager(const TextureManager&);
        TextureManager& operator = (const TextureManager&);

    public:
        static TextureManager* getInstance();
    };
}

#endif
