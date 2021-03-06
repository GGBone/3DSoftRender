#include "GraphicsPCH.h"
#include "Renderer.h"
#include "Visual.h"
#include "RenderData.h"
#include "SoftRenderData.h"
#include "SoftRenderer.h"

using namespace Hikari;
void SoftRenderer::DrawPrimitive(const Visual* visual)
{
	//Retrive the Vertex Buffer Data

	//Transform to Screen Space
	//Store in mainFrameBuffer 
	//Display
	Visual::PrimitiveType type = visual->GetPrimitiveType();
	const VertexBuffer* vbuffer = visual->GetVertexBuffer();
	int numPrimitive, numVertices;

	switch (type)
	{
	case Visual::PT_TRIANGLES:
	case Visual::PT_TRIMESH:
		//Draw Triangle
		numVertices = vbuffer->GetNumElements();
		numPrimitive = numVertices / 3;

		//Transflate the data from Visual to mainFrameBuffer;
		DrawTriMesh();
		break;
	default:
		break;
	}
	DisplayBackBuffer();
}

void Hikari::SoftRenderer::DrawTriMesh()
{

	VertexPos* vertexPtr = (VertexPos*)mVertexBuffer[0]->GetData();
	HPoint v1, v2, v3;
	XMFLOAT2 o1, o2, o3;
	int numPrimitive = mVertexBuffer[0]->GetNumElements() / 3;
	std::vector<VInput> vInputVec(mVertexBuffer[0]->GetNumElements());

	for (int i = 0; i < numPrimitive; ++i)
	{
		//Call WinSoftRenderer DrawLine
		v1 = (*vertexPtr++).pos;
		v2 = (*vertexPtr++).pos;
		v3 = (*vertexPtr++).pos;
		vInputVec[i * 3 + 0].position = v1;
		vInputVec[i * 3 + 1].position = v2;
		vInputVec[i * 3 + 2].position = v3;
		mVertexShader->Process(vInputVec);
		o1 = XMFLOAT2(vInputVec[i * 3 + 0].position.X(), vInputVec[i * 3 + 0].position.Y());
		o2 = XMFLOAT2(vInputVec[i * 3 + 1].position.X(), vInputVec[i * 3 + 1].position.Y());
		o3 = XMFLOAT2(vInputVec[i * 3 + 2].position.X(), vInputVec[i * 3 + 2].position.Y());

		//SoftVertexShader Process

		RasterizeTriangle(o1, o2, o3);
		//  // Cull the triangles based on culling state.
		//  if (pkCullState->Enabled)
		//  {
		//      // Get the clip-space coordinates (r'[i],u'[i],d'[i],w'[i]).
		//      const float* afV0 = GetOutputVertex(iV0);
		//      const float* afV1 = GetOutputVertex(iV1);
		//      const float* afV2 = GetOutputVertex(iV2);

		//      // The visibility test is applied to clip-space coordinates
		//      // (r'[i],u'[i],w'[i]).  The d'[i] term cannot be used as the
		//      // third component since it contains a translation from the
		//      // projection matrix that maps view coordinates to clip
		//      // coordinates.  The normal vector is fine to compute with the
		//      // d'[i] term, but the dot product of the normal with one of the
		//      // vertices is not
		//      Vector3f kE1(afV1[0] - afV0[0], afV1[1] - afV0[1], afV1[3] - afV0[3]);
		//      Vector3f kE2(afV2[0] - afV0[0], afV2[1] - afV0[1], afV2[3] - afV0[3]);
		//      Vector3f kN = kE1.Cross(kE2);

		//      // NOTE:  The camera coordinates are E+r*R+u*U+d*D, but {R,U,D}
		//      // is a left-handed system.  The visibility test must be computed
		//      // accordingly.  The handedness is absorbed into the computation
		//      // of m_iCullSignAdjust.  The default sign adjustment is +1 for
		//      // counterclockwise triangles and back face culling.
		//      float fVisibility = m_iCullSignAdjust*(kN[0] * afV0[0] +
		//          kN[1] * afV0[1] + kN[2] * afV0[3]);
		//      if (fVisibility <= 0.0f)
		//      {
		//          // The triangle is potentially back facing, but an incorrect
		//          // classification can occur due to round-off errors.  Try a
		//          // more detailed test to decide if the triangle really should
		//          // be rejected.

		//          // The visibility test is applied to the window coordinates of
		//          // the points.  If any of the w-components of the points are
		//          // negative, the points are behind the viewer.  Triangles
		//          // with any such vertices are sent to the clipper because
		//          // parts of the triangle are potentially visible.
		//          if (afV0[3] > 0.0f && afV1[3] > 0.0f && afV2[3] > 0.0f)
		//          {
		//              int aiX[3], aiY[3];
		//              ClipToWindowXY(afV0, aiX[0], aiY[0]);
		//              ClipToWindowXY(afV1, aiX[1], aiY[1]);
		//              ClipToWindowXY(afV2, aiX[2], aiY[2]);
		//              int iVisibility = m_iCullSignAdjust*(
		//                  (aiX[2] - aiX[0])*(aiY[1] - aiY[0]) -
		//                  (aiX[1] - aiX[0])*(aiY[2] - aiY[0]));

		//              if (iVisibility <= 0)
		//              {
		//                  // The triangle is back facing.
		//                  continue;
		//              }
		//          }
		//      }
		//  }

		//  // The triangle is visible.  Clip it against the view frustum.
		//  int aiIndex[SOFT_MAX_CLIP_INDICES];
		//  int aiEdge[SOFT_MAX_CLIP_INDICES];
		//  int iQuantity = 3;
		//  aiIndex[0] = iV0;
		//  aiIndex[1] = iV1;
		//  aiIndex[2] = iV2;
		//  aiEdge[0] = 0;
		//  aiEdge[1] = 1;
		//  aiEdge[2] = 2;
		//  ClipPolygon(iQuantity, aiIndex, aiEdge);
		//  if (iQuantity < 3)
		//  {
		//      // The entire triangle was outside the view frustum.
		//      continue;
		//  }

		//  // Rasterize the triangles and call the pixel shaders.
		//  int iVQuantity = m_pkVBResource->VQuantity;
		//  if (pkWireframeState->Enabled)
		//  {
		//      // Draw only the polygon boundary edges, but not any diagonals
		//      // generated by clipping or edges whose end points are both clip
		//      // vertices.
		//      for (int j0 = iQuantity - 1, j1 = 0; j1 < iQuantity; j0 = j1++)
		//      {
		//          if (aiIndex[j0] < iVQuantity
		//              || aiIndex[j1] < iVQuantity
		//              || aiEdge[j0] == aiEdge[j1])
		//          {
		//              RasterizeEdge(aiIndex[j0], aiIndex[j1]);
		//          }
		//      }
		//  }
		//  else
		//  {
		//      int iNumTriangles = iQuantity - 2;
		//      for (int j = 1; j <= iNumTriangles; j++)
		//      {
		//          RasterizeTriangle(aiIndex[0], aiIndex[j], aiIndex[j + 1]);
		//      }
		//  }
		//}

	}
}

void Hikari::SoftRenderer::RasterizeEdge(XMFLOAT2 iV0, XMFLOAT2 iV1)
{
	//Brethenham
	int x0 = (int)(iV0.x * 100 + 100);
	int y0 = (int)(iV0.y * 100 + 100);
	int x1 = (int)(iV1.x * 100 + 100);
	int y1 = (int)(iV1.y * 100 + 100);
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int direction = 0;
	if (dx < dy)
	{
		direction = 1; //大于45°
		swap_int(&x1, &y1);
		swap_int(&x0, &y0);
		swap_int(&dx, &dy);
	}
	int ix = (x1 - x0) > 0 ? 1 : -1;
	int iy = (y1 - y0) > 0 ? 1 : -1;
	int p0 = 2 * dy - dx;

	int n2dy = 2 * dy;
	int n2dydx = (dy - dx) * 2;
	int x = x0;
	int y = y0;
	if (direction)
	{
		while (x != x1)
		{
			if (p0 < 0)
			{
				p0 += n2dy;
			}
			else
			{
				y += iy;
				p0 += n2dydx;
			}
			RasterizePoint(XMFLOAT2((float)y, (float)x), 255);
			x += ix;
		}
	}
	else
	{
		RasterizePoint(XMFLOAT2((float)x, (float)y), 255);
		while (x != x1)
		{
			if (p0 > 0)
			{

				y += iy;
				p0 += n2dydx;
			}
			else
			{
				p0 += n2dy;
			}
			RasterizePoint(XMFLOAT2((float)x, (float)y), 255);
			x += ix;
		}
	}
}
void Hikari::SoftRenderer::RasterizePoint(XMFLOAT2 iV0, int Vcolor)
{
	Buffer* colorBuffer = mainFrameBuffer.GetColorBuffer();
	void* color = colorBuffer->mData;

	unsigned char ucR = (unsigned char)(255.0f*0.0f);
	unsigned char ucG = (unsigned char)(255.0f*1.0f);
	unsigned char ucB = (unsigned char)(255.0f*0.5f);
	unsigned char ucA = (unsigned char)(255.0f*1.0f);
	unsigned int m_uiBackgroundColor = (ucB | (ucG << 8) | (ucR << 16) | (ucA << 24));

	*((unsigned int*)color + (int)iV0.y* mWidth + (int)iV0.x) =
		m_uiBackgroundColor;
}

void Hikari::SoftRenderer::RasterizeTriangle(XMFLOAT2 iV0, XMFLOAT2 iV1, XMFLOAT2 iV2)
{
	RasterizeEdge(iV0, iV1);
	RasterizeEdge(iV1, iV2);
	RasterizeEdge(iV2, iV0);
}

Hikari::SoftRenderer::SoftRenderer(SoftRenderData* input, int width, int height, int numMultisamples, HWND handle)
	:
	Renderer(new RendererData(width, height, handle)),
	mainFrameBuffer(width, height),
	mVertexBuffer(nullptr),
	mVertexShader(nullptr)
{
	Initialize(width, height, Texture::Format(), Texture::Format(), numMultisamples);
	mData = input;
}

void Hikari::SoftRenderer::SetCullState(CullState * cullState)
{
}

void Hikari::SoftRenderer::SetRenderTarget(SoftFrameBuffer * frameBuffer)
{
}

SoftRenderData * Hikari::SoftRenderer::GetRendererData()
{
	return mData;
}

Hikari::SoftRenderer::~SoftRenderer()
{
}

void Hikari::SoftRenderer::Bind(const VertexFormat * vFormat)
{

}

void Hikari::SoftRenderer::ClearBuffers(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::IASetVertexBuffers(UINT startSlot, UINT numBuffers, Buffer** buffer, UINT stride, UINT offset)
{
	if (mVertexBuffer == nullptr)
	{
		mVertexBuffer = new VertexBuffer*[numBuffers];
		for (UINT i = 0; i < numBuffers; i++)
		{
			*(mVertexBuffer + i) = new VertexBuffer((*(buffer + i))->GetNumElements(), (*(buffer + i))->GetElementSize(), (*(buffer + i))->GetUsage());
			memcpy_s((*(mVertexBuffer + startSlot))->mData, (*(mVertexBuffer + startSlot))->GetNumBytes(), (*(buffer + i))->GetData(), (*(buffer + i))->GetNumBytes());
		}
	}
	for (UINT i = 0; i < numBuffers; i++)
	{
		if ((*(buffer + i))->GetUsage() == Buffer::BU_STATIC)
			return;
		else if ((*(buffer + i))->GetUsage() == Buffer::BU_DYNAMIC)
			memcpy_s((*(mVertexBuffer + startSlot))->mData, (*(mVertexBuffer + startSlot))->GetNumBytes(), (*(buffer + i))->GetData(), (*(buffer + i))->GetNumBytes());
	}
	//mVertexBuffer is in VRAM
	//mainFrameBuffer.mColorBuffer = *buffer;
}

void Hikari::SoftRenderer::VSSetConstantBuffers(UINT startSlot, UINT numBuffers, Buffer** cbuffer)
{
	Cell* cell = mVertexShader->GetCell(startSlot);
	ConstantBuffer* c;
	if (cbuffer != nullptr)
	{
		for (UINT i = 0; i < numBuffers; i++)
		{
			c = (ConstantBuffer*)(cbuffer[i]->GetData());
			cell->UpdateConstantBuffer(c);
		}
	}

}

void Hikari::SoftRenderer::Bind(const VertexBuffer * vFormat)
{
}

void Hikari::SoftRenderer::Unbind(const VertexBuffer * vFormat)
{
}

void Hikari::SoftRenderer::Unbind(const VertexFormat * vFormat)
{
}

void Hikari::SoftRenderer::Enable(const VertexBuffer* vBuffer)
{
	static SoftVertexBuffer* softVertexBuffer;
	if (softVertexBuffer == nullptr)
		softVertexBuffer = new SoftVertexBuffer(this, vBuffer);

	//not complete
	softVertexBuffer->Enable(this, 0, 0);
}

void Hikari::SoftRenderer::Enable(const VertexFormat * vFormat)
{
}

void Hikari::SoftRenderer::Enable(const VertexShader * vShader)
{
	if (mVertexShader == nullptr)
	{
		mVertexShader = new SoftVertexShader(this, vShader);
		//insert it
	}
	ConstantBuffer buffer;
	float m[] = { 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	buffer.model = HMatrix(m);
	Buffer* constantBuffer = new Buffer(3, sizeof(HMatrix));
}

void Hikari::SoftRenderer::Disable(const VertexBuffer * vFormat)
{
}

void Hikari::SoftRenderer::Disable(const VertexFormat * vFormat)
{
}

void Hikari::SoftRenderer::Disable(const VertexShader * vShader)
{
	if (mVertexShader != nullptr)
		delete mVertexBuffer;
	delete vShader;
}

void Hikari::SoftRenderer::ClearDepthBuffer()
{
}

void Hikari::SoftRenderer::ClearStencilBuffer()
{
}

void Hikari::SoftRenderer::ClearBuffers()
{
}

void Hikari::SoftRenderer::ClearBackBuffer(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::ClearDepthBuffer(int x, int y, int w, int h)
{
}

void Hikari::SoftRenderer::ClearStencilBuffer(int x, int y, int w, int h)
{
}

