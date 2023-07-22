#ifndef CONTROLLER_MESH_MANAGER_HPP
#define CONTROLLER_MESH_MANAGER_HPP

#include <iostream>

#include <glad/glad.h>

#include "../../tiny_obj_loader.h"

namespace controller {
	class MeshManager {
    private:
        //std::vector<std::vector<GLfloat>*> meshes;

    public:
        std::vector<GLfloat>* load(std::string path);

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
