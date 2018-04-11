#include "Graphics\GraphicsPCH.h"
#include "StandardMesh.h"
using namespace Hikari;
Hikari::StandardMesh::StandardMesh(VertexFormat * vformat, bool isStatic, bool inside, const Transform * transform)
	:
	mVFormat(vformat),
	mIsStatic(isStatic),
	mInside(inside),
	mHasNormals(false),
	mUsage(isStatic? Buffer::BU_STATIC : Buffer::BU_DYNAMIC)
{
	int posIndex = mVFormat->GetIndex(VertexFormat::AU_POSITION);
	if (posIndex < 0)
		return;
	VertexFormat::AttributeType posType =
		mVFormat->GetAttributeType(posIndex);
	
	int norIndex = mVFormat->GetIndex(VertexFormat::AU_NORMAL);
	if (norIndex >= 0)
	{
		VertexFormat::AttributeType norType =
			mVFormat->GetAttributeType(norIndex);
	}

	for (int unit = 0; unit < MAX_UNITS; ++unit)
	{
		mHasTCoords[unit] = false;
		int tcdIndex = mVFormat->GetIndex(VertexFormat::AU_TEXCOORD, unit);
		if (tcdIndex >= 0)
		{
			VertexFormat::AttributeType tcdType =
				mVFormat->GetAttributeType(tcdIndex);

			if (tcdType == VertexFormat::AT_FLOAT2)
			{
				mHasTCoords[unit] = true;
			}
		}
	}
	if (transform)
		mTransform = *transform;
}
Hikari::StandardMesh::~StandardMesh()
{
}
void Hikari::StandardMesh::SetTransform(const Transform & transform)
{
	mTransform = transform;
}
TriMesh * Hikari::StandardMesh::ExternalModel(int numOfAttribute, ...)
{
	if (numOfAttribute < 0)
		return nullptr;
	int numVertices = 0;
	int numIndices = 0;
	int stride = 0;
	va_list arguments;
	va_start(arguments, numOfAttribute);
	unsigned int offset = 0;
	switch (numOfAttribute)
	{
	case 4:
		const std::vector<unsigned short> & indicies = va_arg(arguments, std::vector<unsigned short>);
		const std::vector<Vector3f>& vertices = va_arg(arguments, std::vector<Vector3f>);
		const std::vector<Vector2f>& uv = va_arg(arguments, std::vector<Vector2f>);
		const std::vector<Vector3f>& normal = va_arg(arguments, std::vector<Vector3f>);

		numVertices = vertices.size();
		numIndices = indicies.size();
		stride = mVFormat->GetStride();
		VertexBuffer* vbuffer = new VertexBuffer(numVertices, stride, mUsage);
		VertexBufferAccessor vba(mVFormat, vbuffer);

		// Generate geometry.
		std::vector<Vector3f>::const_iterator iter;
		int i;
		for (iter = vertices.begin(),i = 0; iter != vertices.end(); ++iter,++i)
		{
			vba.Position<Float3>(i) = Float3((*iter)[0], (*iter)[1], (*iter)[2] );

		}

		for (iter = normal.begin(), i = 0; iter != normal.end(); ++iter, ++i)
		{
			vba.Normal<Float3>(i) = Float3((*iter)[0], (*iter)[1], (*iter)[2]);

		}

		std::vector<Vector2f>::const_iterator uv_iter;
		int j = 0;
		for (i = 0; i < MAX_UNITS; ++i)
		{
			if (mHasTCoords[i])
			{
				for (uv_iter = uv.begin() ,j =0;uv_iter != uv.end(); ++j,++uv_iter)
				{
					vba.TCoord<Float2>(i, j) = Float2((*uv_iter)[0], (*uv_iter)[1]);

				}
			}

		}


		IndexBuffer* ibuffer = new IndexBuffer(numIndices, sizeof(unsigned short), mUsage);
		unsigned short* temp = (unsigned short*)ibuffer->GetData();
		std::vector<unsigned short>::const_iterator indexIter;
		for (indexIter = indicies.begin(),i=0; indexIter != indicies.end(); ++indexIter,++i)
		{
			temp[i] = (*indexIter);
		}

		TriMesh* mesh = new TriMesh(mVFormat, vbuffer, ibuffer);
		return mesh;
		break;
	}
	va_end(arguments);


	
	return nullptr;
}
TriMesh * Hikari::StandardMesh::Box(float xExtent, float yExtent, float zExtent)
{
	int numVertices = 8;
	int numTriangles = 12;
	int numIndices = 3 * numTriangles;
	int stride = mVFormat->GetStride();

	// Create a vertex buffer.
	VertexBuffer* vbuffer = new VertexBuffer(numVertices, stride, mUsage);
	VertexBufferAccessor vba(mVFormat, vbuffer);

	// Generate geometry.
	vba.Position<Float3>(0) = Float3(-xExtent, -yExtent, -zExtent);
	vba.Position<Float3>(1) = Float3(+xExtent, -yExtent, -zExtent);
	vba.Position<Float3>(2) = Float3(+xExtent, +yExtent, -zExtent);
	vba.Position<Float3>(3) = Float3(-xExtent, +yExtent, -zExtent);
	vba.Position<Float3>(4) = Float3(-xExtent, -yExtent, +zExtent);
	vba.Position<Float3>(5) = Float3(+xExtent, -yExtent, +zExtent);
	vba.Position<Float3>(6) = Float3(+xExtent, +yExtent, +zExtent);
	vba.Position<Float3>(7) = Float3(-xExtent, +yExtent, +zExtent);


	for (int unit = 0; unit < MAX_UNITS; ++unit)
	{
		if (mHasTCoords[unit])
		{
			vba.TCoord<Float2>(unit, 0) = Float2(0.25f,0.75f);
			vba.TCoord<Float2>(unit, 1) = Float2(0.75f, 0.75f);
			vba.TCoord<Float2>(unit, 2) = Float2(0.75f, 0.25f);
			vba.TCoord<Float2>(unit, 3) = Float2(0.25f, 0.25f);
			vba.TCoord<Float2>(unit, 4) = Float2(0.0f, 1.0f);
			vba.TCoord<Float2>(unit, 5) = Float2(1.0f, 1.0f);
			vba.TCoord<Float2>(unit, 6) = Float2(1.0f, 0.0f);
			vba.TCoord<Float2>(unit, 7) = Float2(0.0f, 0.0f);
		}
	}
	TransformData(vba);

	// Generate indices (outside view).
	IndexBuffer* ibuffer = new IndexBuffer(numIndices, 4, mUsage);
	int* indices = (int*)ibuffer->GetData();
	indices[0] = 0;  indices[1] = 2;  indices[2] = 1;
	indices[3] = 0;  indices[4] = 3;  indices[5] = 2;
	indices[6] = 0;  indices[7] = 1;  indices[8] = 5;
	indices[9] = 0;  indices[10] = 5;  indices[11] = 4;
	indices[12] = 0;  indices[13] = 4;  indices[14] = 7;
	indices[15] = 0;  indices[16] = 7;  indices[17] = 3;
	indices[18] = 6;  indices[19] = 4;  indices[20] = 5;
	indices[21] = 6;  indices[22] = 7;  indices[23] = 4;
	indices[24] = 6;  indices[25] = 5;  indices[26] = 1;
	indices[27] = 6;  indices[28] = 1;  indices[29] = 2;
	indices[30] = 6;  indices[31] = 2;  indices[32] = 3;
	indices[33] = 6;  indices[34] = 3;  indices[35] = 7;

	if (mInside)
	{
		ReverseTriangleOrder(numTriangles, indices);
	}

	TriMesh* mesh = new TriMesh(mVFormat, vbuffer, ibuffer);
	if (mHasNormals)
	{
		mesh->UpdateModelSpace(Visual::GU_NORMALS);
	}
	return mesh;
}

void Hikari::StandardMesh::TransformData(VertexBufferAccessor & vba)
{
	if (mTransform.IsIdentity())
	{
		return;
	}

	const int numVertices = vba.GetNumVertices();
	int i;
	for (i = 0; i < numVertices; ++i)
	{
		APoint position = vba.Position<Float3>(i);
		vba.Position<Float3>(i) = mTransform*position;
	}

	if (mHasNormals)
	{
		for (i = 0; i < numVertices; ++i)
		{
			vba.Normal<AVector>(i).Normalize();
		}
	}
}

void Hikari::StandardMesh::ReverseTriangleOrder(int numTriangle, int * indices)
{
}
