#pragma once
#include "CoreLib.h"
#include "Mathematics.h"
#include <vector>


namespace Hikari
{
	class MeshLoader
	{
	public:
		
		bool loadMesh_assimp(
			const char * path,
			std::vector<unsigned short> & out_indices,
			std::vector<Vector3f> & out_vertices,
			std::vector<Vector2f> & out_uvs,
			std::vector<Vector3f> & out_normals);
	};
	
}


