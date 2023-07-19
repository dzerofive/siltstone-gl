#pragma once

#include <sln/type/mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace sln {
sln::Mesh parse_collada(std::filesystem::path dae_path) {
        Assimp::Importer importer;
        auto scene = importer.ReadFile(dae_path, aiProcess_Triangulate);
        if (scene == nullptr) throw std::runtime_error("Failed to open DAE file"); 

        sln::Mesh mesh;

        for(int i = 0; i < scene->mMeshes[0]->mNumVertices; ++i) {
                mesh.vertices.push_back({{scene->mMeshes[0]->mVertices[i].x, 
                                          scene->mMeshes[0]->mVertices[i].y,
                                          scene->mMeshes[0]->mVertices[i].z}, 
                                         {scene->mMeshes[0]->mTextureCoords[0][i].x,
                                          scene->mMeshes[0]->mTextureCoords[0][i].y},
                                         {scene->mMeshes[0]->mNormals[i].x,
                                          scene->mMeshes[0]->mNormals[i].y,
                                          scene->mMeshes[0]->mNormals[i].z}});
        }
        for(int i = 0; i < scene->mMeshes[0]->mNumFaces; ++i) {
                mesh.triangles.push_back({scene->mMeshes[0]->mFaces[i].mIndices[0],
                                          scene->mMeshes[0]->mFaces[i].mIndices[1],
                                          scene->mMeshes[0]->mFaces[i].mIndices[2]});
        }
        std::cout << scene->mMeshes[0]->mNumFaces << '\n';

        return mesh; 
}
}// namespace sln
