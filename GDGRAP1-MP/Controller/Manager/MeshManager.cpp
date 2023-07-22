#include "MeshManager.hpp"

using namespace controller;

std::vector<GLfloat>* MeshManager::load(std::string path) {
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    if (!success) {
        std::cout << error << std::endl;
        return NULL;
    }
    else {
        std::vector<GLfloat> vertexData;
        for (int i = 0; i < shapes.size(); i++) {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
                tinyobj::index_t vData = shapes[i].mesh.indices[j];

                vertexData.push_back(attributes.vertices[vData.vertex_index * 3]);
                vertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 1]);
                vertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 2]);

                if (!attributes.normals.empty()) {
                    vertexData.push_back(attributes.normals[vData.normal_index * 3]);
                    vertexData.push_back(attributes.normals[vData.normal_index * 3 + 1]);
                    vertexData.push_back(attributes.normals[vData.normal_index * 3 + 2]);
                }

                vertexData.push_back(attributes.texcoords[vData.texcoord_index * 2]);
                vertexData.push_back(attributes.texcoords[vData.texcoord_index * 2 + 1]);
            }
        }
        return &vertexData;
    }
}

MeshManager* MeshManager::SHARED_INSTANCE = NULL;

MeshManager::MeshManager() {}
MeshManager::MeshManager(const MeshManager&) {}

MeshManager* MeshManager::getInstance() {
    if (SHARED_INSTANCE == NULL)
        SHARED_INSTANCE = new MeshManager();

    return SHARED_INSTANCE;
}