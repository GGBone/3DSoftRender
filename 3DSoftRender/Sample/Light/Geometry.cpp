//#include "Geometry.h"
//using namespace Hikari;
//void Geometry::CreateBox(float width, float height, float depth, MeshData& meshData)
//{
//	Vertex v[24];
//
//	float w2 = 0.5f*width;
//	float h2 = 0.5f*height;
//	float d2 = 0.5f*depth;
//
//	// Fill in the front face vertex data.
//	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//	v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
//	v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//	v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
//
//	// Fill in the back face vertex data.
//	v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
//	v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//	v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
//	v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//	// Fill in the top face vertex data.
//	v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//	v[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
//	v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//	v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
//
//	// Fill in the bottom face vertex data.
//	v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
//	v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//	v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
//	v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//	// Fill in the left face vertex data.
//	v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
//	v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
//	v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
//	v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
//
//	// Fill in the right face vertex data.
//	v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
//	v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
//	v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
//	v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
//
//	meshData.Vertices.assign(&v[0], &v[24]);
//
//	UINT i[36];
//
//	// Fill in the front face index data
//	i[0] = 0; i[1] = 1; i[2] = 2;
//	i[3] = 0; i[4] = 2; i[5] = 3;
//
//	// Fill in the back face index data
//	i[6] = 4; i[7] = 5; i[8] = 6;
//	i[9] = 4; i[10] = 6; i[11] = 7;
//
//	// Fill in the top face index data
//	i[12] = 8; i[13] = 9; i[14] = 10;
//	i[15] = 8; i[16] = 10; i[17] = 11;
//
//	// Fill in the bottom face index data
//	i[18] = 12; i[19] = 13; i[20] = 14;
//	i[21] = 12; i[22] = 14; i[23] = 15;
//
//	// Fill in the left face index data
//	i[24] = 16; i[25] = 17; i[26] = 18;
//	i[27] = 16; i[28] = 18; i[29] = 19;
//
//	// Fill in the right face index data
//	i[30] = 20; i[31] = 21; i[32] = 22;
//	i[33] = 20; i[34] = 22; i[35] = 23;
//
//	meshData.Indices.assign(&i[0], &i[36]);
//}
//
//void Geometry::Subdivide(MeshData& meshData)
//{
//	MeshData inputCopy = meshData;
//
//
//	meshData.Vertices.resize(0);
//	meshData.Indices.resize(0);
//
//
//	UINT numTris = inputCopy.Indices.size() / 3;
//	for (UINT i = 0; i < numTris; ++i)
//	{
//		Vertex v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
//		Vertex v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
//		Vertex v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];
//
//		//
//		// Generate the midpoints.
//		//
//
//		Vertex m0, m1, m2;
//
//		// For subdivision, we just care about the position component.  We derive the other
//		// vertex components in CreateGeosphere.
//
//		m0.m_position = XMFLOAT3(
//			0.5f*(v0.m_position.x + v1.m_position.x),
//			0.5f*(v0.m_position.y + v1.m_position.y),
//			0.5f*(v0.m_position.z + v1.m_position.z));
//
//		m1.m_position = XMFLOAT3(
//			0.5f*(v1.m_position.x + v2.m_position.x),
//			0.5f*(v1.m_position.y + v2.m_position.y),
//			0.5f*(v1.m_position.z + v2.m_position.z));
//
//		m2.m_position = XMFLOAT3(
//			0.5f*(v0.m_position.x + v2.m_position.x),
//			0.5f*(v0.m_position.y + v2.m_position.y),
//			0.5f*(v0.m_position.z + v2.m_position.z));
//
//		//
//		// Add new geometry.
//		//
//
//		meshData.Vertices.push_back(v0); // 0
//		meshData.Vertices.push_back(v1); // 1
//		meshData.Vertices.push_back(v2); // 2
//		meshData.Vertices.push_back(m0); // 3
//		meshData.Vertices.push_back(m1); // 4
//		meshData.Vertices.push_back(m2); // 5
//
//		meshData.Indices.push_back(i * 6 + 0);
//		meshData.Indices.push_back(i * 6 + 3);
//		meshData.Indices.push_back(i * 6 + 5);
//
//		meshData.Indices.push_back(i * 6 + 3);
//		meshData.Indices.push_back(i * 6 + 4);
//		meshData.Indices.push_back(i * 6 + 5);
//
//		meshData.Indices.push_back(i * 6 + 5);
//		meshData.Indices.push_back(i * 6 + 4);
//		meshData.Indices.push_back(i * 6 + 2);
//
//		meshData.Indices.push_back(i * 6 + 3);
//		meshData.Indices.push_back(i * 6 + 1);
//		meshData.Indices.push_back(i * 6 + 4);
//	}
//}
//
//
//void Geometry::CreateHermit(std::vector<ControlPoint> control, MeshData& meshData)
//{
//	meshData.Vertices.reserve(100);
//	meshData.Indices.reserve(100);
//	int controlsize = control.size();
//	std::vector<ControlPoint>::iterator it;
//	int segment = 20;
//	static int i = 0;
//	static float t;
//	for (it = control.begin(); it != control.end() - 1; ++it)
//	{
//		for (int k = 0; k < 20; ++k, ++i)
//		{
//			t = k / 20.0f;
//			float x0 = (*(it)).GetPosition().x,
//				x1 = (*(it + 1)).GetPosition().x,
//				y0 = (*(it)).GetPosition().y,
//				y1 = (*(it + 1)).GetPosition().y,
//				z0 = (*(it)).GetPosition().z,
//				z1 = (*(it + 1)).GetPosition().z,
//				tangentX0 = (*(it)).GetTangent().x,
//				tangentX1 = (*(it + 1)).GetTangent().x,
//				tangentY0 = (*(it)).GetTangent().y,
//				tangentY1 = (*(it + 1)).GetTangent().y,
//				tangentZ0 = (*(it)).GetTangent().z,
//				tangentZ1 = (*(it + 1)).GetTangent().z;
//			meshData.Vertices.push_back(Geometry::Vertex(
//				XMFLOAT3(
//				(2 * t *t *t - 3 * t *t + 1) * x0
//					+ (t *t *t - 2 * t*t + t) * tangentX0 + (-2 * t*t*t + 3 * t*t)*x1 +
//					(t*t*t - t*t) * tangentX1,
//					(2 * t *t *t - 3 * t *t + 1) * y0
//					+ (t *t *t - 2 * t*t + t) * tangentY0 + (-2 * t*t*t + 3 * t*t)*y1 +
//					(t*t*t - t*t) * tangentY1,
//					(2 * t *t *t - 3 * t *t + 1) * z0
//					+ (t *t *t - 2 * t*t + t) * tangentZ0 + (-2 * t*t*t + 3 * t*t)*z1 +
//					(t*t*t - t*t) * tangentZ1
//				), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT2(0, 0)));
//			meshData.Indices.push_back(i);
//		}
//	}
//	meshData.Vertices.push_back(Geometry::Vertex(
//		(*it).GetPosition(), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT2(0, 0)
//	));
//	meshData.Indices.push_back(i);
//}
//
//
//void Geometry::CreateBeizer(std::vector<ControlPoint> control, MeshData& meshData)
//{
//	meshData.Vertices.reserve(100);
//	meshData.Indices.reserve(100);
//	int controlsize = control.size();
//	std::vector<ControlPoint>::iterator it;
//	int segment = 20;
//	static int i = 0;
//	static float t;
//}
//
//float Geometry::CalculateFinu(float u, float i, float n, std::vector<float>&knot)
//{
//	//N_i_1 = f_1_1  n == n+1
//	if (n == 1)
//	{
//
//		if (u >= knot[i] && u <= knot[i + 1])
//		{
//			return 1.0f;
//		}
//		else return 0.0f;
//	}
//
//	float result1 = (knot[i + n - 1] - knot[i]);
//	float result2 = (knot[i + n] - knot[i + 1]);
//
//
//	if (result1 > 0)
//	{
//		float f_i_n = (u - knot[i]) / result1;
//		result1 = f_i_n * CalculateFinu(u, i, n - 1, knot);
//	}
//	else result1 = 0;
//
//	if (result2 > 0)
//	{
//		float g_i_n = (knot[i + n] - u) / result2;
//		result2 = g_i_n * CalculateFinu(u, i + 1, n - 1, knot);
//	}
//	else result2 = 0;
//
//	return result1 + result2;
//}
//void Geometry::CrateNurbs(std::vector<ControlPoint>& control, std::vector<float>&knot, std::vector<float>& width, MeshData& meshData)
//{
//	meshData.Vertices.reserve(100);
//	meshData.Indices.reserve(100);
//	const int degree = 3;
//
//	//the first one and the last one is special for uniform
//	knot = { 0 ,0 ,0 ,0 , 2 , 6, 6, 6 ,6 };
//	//knot = { 0, 0, 0, 0,  1 , 3, 3, 3 ,3};
//	int controlSize = control.size();
//
//	int EKnotSize = degree + controlSize + 1;
//	int RKnotSize = knot.size();
//
//	if (EKnotSize == RKnotSize)
//	{
//		//kNot number is Correct
//		//knot is By order
//
//		const int tess = 80;
//		for (int j = 0; j < tess; j++)
//		{
//			float u = (knot[knot.size() - 1] - knot[0]) * j / (float)(tess - 1);
//
//			if (j == tess - 1)
//				u -= 0.001f;
//
//			Vertex temp(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0.0, 0.0));
//
//			XMFLOAT3 temSum(0.0, 0.0, 0.0);
//			for (int i = 0; i < control.size(); i++)
//			{
//				float N = CalculateFinu(u, i, degree, knot);
//
//				if (N > 0.000001f)
//				{
//					//temSum.x += N;
//					//temSum.y += N;
//					//temSum.z += N;
//					temp.m_position.x += N * control[i].GetPosition().x;
//					temp.m_position.y += N * control[i].GetPosition().y;
//					temp.m_position.z += N * control[i].GetPosition().z;
//				}
//			}
//			meshData.Vertices.push_back(temp);
//		}
//		meshData.Vertices.push_back(Vertex(control[controlSize - 1].GetPosition(), control[controlSize - 1].GetTangent(), XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0.0, 0.0)));
//
//	}
//	//Invalied
//	else return;
//
//}
//
