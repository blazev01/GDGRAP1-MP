#ifndef CONTROLLERS_MESH_MANAGER_HPP
#define CONTROLLERS_MESH_MANAGER_HPP

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace controllers {
	class MeshManager {
    private:
        //std::vector<std::vector<GLfloat>*> meshes;

    public:
        std::vector<GLfloat> load(std::string path);

    private:
        static MeshManager* SHARED_INSTANCE;

    private:
        MeshManager();
        MeshManager(const MeshManager&);
        MeshManager& operator = (const MeshManager&);

    public:
        static MeshManager* getInstance();
    };
}

#endif
