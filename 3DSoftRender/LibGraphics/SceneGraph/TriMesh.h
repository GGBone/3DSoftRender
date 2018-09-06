#pragma once

#include "GraphicsLib.h"
#include "Triangle.h"

namespace Hikari
{
	class TriMesh : public Triangles
	{
	DECLARE_RTTI;
	DECLARE_NAMES;

	protected:
		TriMesh();

	public:
		TriMesh(VertexFormat* vformat, Buffer* vbuffer, Buffer* ibuffer);
		virtual ~TriMesh();
		int GetNumTriangles() const override;
		bool GetTriangle(int i, int& v0, int& v1, int& v2) const override;
	};

	typedef TriMesh* TriMeshPtr;
}
