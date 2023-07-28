#ifndef CONTROLLERS_TEXTURE_MANAGER_HPP
#define CONTROLLERS_TEXTURE_MANAGER_HPP

#include <vector>

#include <glad/glad.h>

namespace controllers {
	class TextureManager {
    public:
        void load(const char* path, bool flipVert, GLenum target);

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
