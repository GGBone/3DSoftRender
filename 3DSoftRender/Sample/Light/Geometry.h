#pragma once
#include "WindowApplicationEngine.h"
#include "ControlPoint.h"

namespace Hikari
{
	class ControlPoint;

	class Geometry
	{
	private:
	public:
		struct Vertex
		{
			XMFLOAT3 m_position;
			XMFLOAT3 m_Normal;
			XMFLOAT3 TangentU;
			XMFLOAT2 m_uv;

			Vertex()
			{
			}

			Vertex(const XMFLOAT3& pos, const XMFLOAT3& tangent, const XMFLOAT3 normal, const XMFLOAT2& uv)
				: m_position(pos), m_Normal(normal), TangentU(tangent), m_uv(uv)
			{
			}

			Vertex(float px, float py, float pz,
			       float nx, float ny, float nz,
			       float tx, float ty, float tz,
			       float u, float v
			) : m_position(px, py, pz),
			    m_Normal(nx, ny, nz),
			    TangentU(tx, ty, tz),
			    m_uv(u, v)
			{
			}
		};

		struct MeshData
		{
			std::vector<Vertex> Vertices;
			std::vector<UINT> Indices;
		};

		void CreateBox(float width, float height, float depth, MeshData& meshData);
		void CreateSphere(float radius, UINT sliceCount, UINT stackCount, MeshData& meshData);
		void CreateBezier(std::vector<ControlPoint> control, MeshData& meshData);
		void CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData);
		void CreateFullscreenQuad(MeshData& meshData);
		void CreateHermit(std::vector<ControlPoint> control, MeshData& meshData);
		void CreateBeizer(std::vector<ControlPoint> control, MeshData& meshData);
		void CrateNurbs(std::vector<ControlPoint>& control, std::vector<float>& knot, std::vector<float>& width,
		                MeshData& meshData);
		//virtual void  GenerateShape();
	private:
		void Subdivide(MeshData& meshData);
		float CalculateFinu(float u, float i, float n, std::vector<float>& knot);
	};
}
