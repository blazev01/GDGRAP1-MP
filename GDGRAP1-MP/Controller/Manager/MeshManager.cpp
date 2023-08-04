#include "MeshManager.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../tiny_obj_loader.h"

using namespace controllers;

// @brief Loads the mesh for the model and provides a vector of vertex data from the loaded OBJ file.
// @param path - The file path of the OBJ file to be loaded
std::vector<GLfloat> MeshManager::load(std::string path) {
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
    }
    else {
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;

        for (int i = 0; i < shapes.size(); i++) {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j += 3) {
                tinyobj::index_t vData1 = shapes[i].mesh.indices[j];
                tinyobj::index_t vData2 = shapes[i].mesh.indices[j + 1];
                tinyobj::index_t vData3 = shapes[i].mesh.indices[j + 2];

                //XYZ
                glm::vec3 v1 = glm::vec3(
                    attributes.vertices[vData1.vertex_index * 3],
                    attributes.vertices[vData1.vertex_index * 3 + 1],
                    attributes.vertices[vData1.vertex_index * 3 + 2]
                );
                glm::vec3 v2 = glm::vec3(
                    attributes.vertices[vData2.vertex_index * 3],
                    attributes.vertices[vData2.vertex_index * 3 + 1],
                    attributes.vertices[vData2.vertex_index * 3 + 2]
                );
                glm::vec3 v3 = glm::vec3(
                    attributes.vertices[vData3.vertex_index * 3],
                    attributes.vertices[vData3.vertex_index * 3 + 1],
                    attributes.vertices[vData3.vertex_index * 3 + 2]
                );

                //UV
                glm::vec2 uv1 = glm::vec2(
                    attributes.texcoords[vData1.texcoord_index * 2],
                    attributes.texcoords[vData1.texcoord_index * 2 + 1]
                );
                glm::vec2 uv2 = glm::vec2(
                    attributes.texcoords[vData2.texcoord_index * 2],
                    attributes.texcoords[vData2.texcoord_index * 2 + 1]
                );
                glm::vec2 uv3 = glm::vec2(
                    attributes.texcoords[vData3.texcoord_index * 2],
                    attributes.texcoords[vData3.texcoord_index * 2 + 1]
                );

                glm::vec3 deltaPos1 = v2 - v1;
                glm::vec3 deltaPos2 = v3 - v1;

                glm::vec2 deltaUV1 = uv2 - uv1;
                glm::vec2 deltaUV2 = uv3 - uv1;

                float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));

                glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
                glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

                tangents.push_back(tangent);
                tangents.push_back(tangent);
                tangents.push_back(tangent);

                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
                bitangents.push_back(bitangent);
            }
        }

        std::vector<GLfloat> vertexData;
        for (int i = 0; i < shapes.size(); i++) {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
                tinyobj::index_t vData = shapes[i].mesh.indices[j];

                //X
                vertexData.push_back(
                    attributes.vertices[vData.vertex_index * 3]
                );
                //Y
                vertexData.push_back(
                    attributes.vertices[vData.vertex_index * 3 + 1]
                );
                //Z
                vertexData.push_back(
                    attributes.vertices[vData.vertex_index * 3 + 2]
                );

                //Normals X
                vertexData.push_back(
                    attributes.normals[vData.normal_index * 3]
                );
                //Normals Y
                vertexData.push_back(
                    attributes.normals[vData.normal_index * 3 + 1]
                );
                //Normals Z
                vertexData.push_back(
                    attributes.normals[vData.normal_index * 3 + 2]
                );

                //U
                vertexData.push_back(
                    attributes.texcoords[vData.texcoord_index * 2]
                );
                //V
                vertexData.push_back(
                    attributes.texcoords[vData.texcoord_index * 2 + 1]
                );

                vertexData.push_back(tangents[i].x);
                vertexData.push_back(tangents[i].y);
                vertexData.push_back(tangents[i].z);

                vertexData.push_back(bitangents[i].x);
                vertexData.push_back(bitangents[i].y);
                vertexData.push_back(bitangents[i].z);
            }
        }
        return vertexData;
    }
}

// @brief Singleton Content for Mesh Manager, allowing it to be called on other files without an instantiated variable provided the file path is part of the #include files.
MeshManager* MeshManager::SHARED_INSTANCE = NULL;

MeshManager::MeshManager() {}
MeshManager::MeshManager(const MeshManager&) {}

MeshManager* MeshManager::getInstance() {
    if (SHARED_INSTANCE == NULL)
        SHARED_INSTANCE = new MeshManager();

    return SHARED_INSTANCE;
}