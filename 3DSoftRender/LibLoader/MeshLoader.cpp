#include "MeshLoader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
using namespace Hikari;
bool Hikari::MeshLoader::loadMesh_assimp(const char * path, std::vector<unsigned short>& out_indices, std::vector<Vector3f>& out_vertices, std::vector<Vector2f>& out_uvs, std::vector<Vector3f>& out_normals)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_GenNormals |
		aiProcess_Triangulate | aiProcess_CalcTangentSpace |
		aiProcess_FlipUVs);
	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
		!scene->mRootNode)
	{
		return false;
	}
	aiMesh* mesh = scene->mMeshes[0];

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vector3f tmpVec;
		tmpVec.X() = mesh->mVertices[i].x;
		tmpVec.Y() = mesh->mVertices[i].y;
		tmpVec.Z() = mesh->mVertices[i].z;
		out_vertices.push_back(tmpVec);

		tmpVec.X() = mesh->mNormals[i].x;
		tmpVec.Y() = mesh->mNormals[i].y;
		tmpVec.Z() = mesh->mNormals[i].z;
		out_normals.push_back(tmpVec);

		if (mesh->mTextureCoords[0])
		{
			tmpVec.X() = mesh->mTextureCoords[0][i].x;
			tmpVec.Y() = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tmpVec.X() = tmpVec.Y() = tmpVec.Z() = 0.0f;
		}
		out_uvs.push_back(Vector2f(tmpVec.X(),tmpVec.Y()));
	}

	for (int i = 0; i<mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j<face.mNumIndices; ++j) //0..2
		{
			out_indices.push_back(face.mIndices[j]);
		}
	}

	return true;

}
