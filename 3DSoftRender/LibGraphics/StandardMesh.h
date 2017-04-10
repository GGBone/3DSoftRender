#pragma once
#include "GraphicsLib.h"
#include "VertexBufferAccessor.h"
#include "TriMesh.h"

namespace Hikari
{
	class StandardMesh
	{
	public:
		StandardMesh(VertexFormat* vformat, bool isStatic = true, bool inside = false, const Transform* transform = 0);
		~StandardMesh();
		void SetTransform(const Transform& transform);

		const Transform& GetTransform()const;
		
		TriMesh* ExternalModel(int numOfAttribute,...);

		TriMesh* Rectangle(int xSample, int ySample, float xExtent, float yExtent);

		TriMesh* Disk(int shellSamples, int radialSamples, float radius);

		TriMesh* Box(float xExtent, float yExtent, float zExtent);

		TriMesh* Cylinder(int axisSample, int radialSamples, float radius,
			float height, bool open);
		TriMesh* Sphere(int zSamples, int radialSamples, float radius);

		TriMesh* Torus(int circleSamples, int radialSamples, float outerRadius, float innerRadius);

		// Platonic solids, all inscribed in a unit sphere centered at (0,0,0).
		TriMesh* Tetrahedron();
		TriMesh* Hexahedron();
		TriMesh* Octahedron();
		TriMesh* Dodecahedron();
		TriMesh* Icosahedron();

	private:
		void TransformData(VertexBufferAccessor& vba);
		void ReverseTriangleOrder(int numTriangle, int* indices);
		void CreatePlatonicNormals(VertexBufferAccessor& vba);
		void CreatePlatonicUVs(VertexBufferAccessor& vba);

		enum
		{
			MAX_UNITS = VertexFormat::AM_MAX_TOORD_UNITS
		};
		VertexFormatPtr mVFormat;
		Transform mTransform;
		bool mIsStatic, mInside, mHasNormals;
		bool mHasTCoords[MAX_UNITS];
		Buffer::Usage mUsage;
	};
}