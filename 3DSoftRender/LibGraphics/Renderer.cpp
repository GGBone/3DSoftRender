#include "GraphicsPCH.h"
#include "Renderer.h"

using namespace Hikari;

void Hikari::Renderer::Initialize(int width, int height, Texture::Format colorFormat, Texture::Format depthStencilFormat, int numMultisamples)
{
	mWidth = width;
	mHeight = height;
	mColorFormat = colorFormat;
	mDepthStencilFormat = depthStencilFormat;
	mNumMultisamples = numMultisamples;


}

void Hikari::Renderer::Terminate()
{
}

inline int Hikari::Renderer::GetWidth() const
{
	return mWidth;
}

inline int Hikari::Renderer::GetHeight() const
{
	return mHeight;
}

inline Texture::Format Hikari::Renderer::GetColorFormat() const
{
	return mColorFormat;
}

inline Texture::Format Hikari::Renderer::GetDepthStencilFormat() const
{
	return mDepthStencilFormat;
}

inline int Hikari::Renderer::GetNumMultisamples() const
{
	return mNumMultisamples;
}

void Hikari::Renderer::Bind(const VertexFormat* vFormat)
{

}

void Hikari::Renderer::BindAll(const VertexFormat * vformat)
{
}

void Hikari::Renderer::Unbind(const VertexFormat * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const VertexFormat * vFormat)
{
}


void Hikari::Renderer::Draw(const Visual * visual, const VisualEffectInstance* instance)
{
	const VertexFormat* vFormat = visual->GetVertexFormat();
	const VertexBuffer* vBuffer = visual->GetVertexBuffer();
	const IndexBuffer* iBuffer = visual->GetIndexBuffer();
	Enable(vBuffer);
	Enable(iBuffer);

	const int numPasses = instance->GetNumPasses();
	for (int i = 0; i < numPasses; ++i)
	{
		const VisualPass* pass = instance->GetPass(i);
		ShaderParameters* vParam = instance->GetVertexShaderParam(i);
		ShaderParameters* pParam = instance->GetPixelShaderParam(i);
		VertexShader* vShader = pass->GetVertexShader();
		PixelShader* pShader = pass->GetPixelShader();
		//ShaderParamter vParam
		vParam->UpdateConstants(visual, nullptr);
		pParam->UpdateConstants(visual, nullptr);

		//Enable shaders
		Enable(vShader, vParam);
		Enable(pShader, pParam);

		DrawPrimitive(visual);
	}
}
Hikari::Renderer::Renderer(RendererData* data)
{
	mData = data;
	mWidth = data->mWidth;
	mHeight = data->mHeight;
}

void Hikari::Renderer::Bind(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::BindAll(const IndexBuffer * vformat)
{
}

void Hikari::Renderer::Unbind(const IndexBuffer * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const IndexBuffer * vFormat)
{
}
void Hikari::Renderer::Disable(const IndexBuffer * vFormat)
{
}

void * Hikari::Renderer::Lock(const IndexBuffer * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const IndexBuffer * vbBuffer)
{
}

void Hikari::Renderer::Update(const IndexBuffer * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const IndexBuffer * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture1D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture1D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture1D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture1D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture1D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture1D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture1D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture1D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture1D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture1D * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture2D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture2D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture2D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture2D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture2D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture2D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture2D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture2D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture2D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture2D * vbuffer)
{
}

void Hikari::Renderer::Bind(const Texture3D * vFormat)
{
}

void Hikari::Renderer::BindAll(const Texture3D * vformat)
{
}

void Hikari::Renderer::Unbind(const Texture3D * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const Texture3D * vFormat)
{
}

void Hikari::Renderer::Enable(const Texture3D * vFormat)
{
}

void Hikari::Renderer::Disable(const Texture3D * vFormat)
{
}

void * Hikari::Renderer::Lock(const Texture3D * vbuffer, Buffer::Locking mode)
{
	return nullptr;
}

void Hikari::Renderer::UnLock(const Texture3D * vbBuffer)
{
}

void Hikari::Renderer::Update(const Texture3D * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const Texture3D * vbuffer)
{
}

void Hikari::Renderer::Bind(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::BindAll(const RenderTarget * vformat)
{
}

void Hikari::Renderer::Unbind(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const RenderTarget * vFormat)
{
}

void Hikari::Renderer::Draw(const VisibleSet & visibleSet, GlobalEffect * globalEffect)
{
}

inline Camera * Hikari::Renderer::GetCamera()
{
	return nullptr;
}

inline const HMatrix & Hikari::Renderer::GetViewMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

inline const HMatrix & Hikari::Renderer::GetPostProjectionMatrix() const
{
	// TODO: 在此处插入 return 语句
}

bool Hikari::Renderer::GetPickRay(int x, int y, APoint & origin, AVector & direction) const
{
	return false;
}

inline void Hikari::Renderer::SetClearColor(const Float4 & color)
{
}

inline const Float4 & Hikari::Renderer::GetClearColor() const
{
	// TODO: 在此处插入 return 语句
}

inline void Hikari::Renderer::SetClearDepth(float clearDepth)
{
}

inline float Hikari::Renderer::GetClearDepth() const
{
	return 0.0f;
}

inline void Hikari::Renderer::SetClearStencil(unsigned int clearStencil)
{
}

inline unsigned int Hikari::Renderer::GetClearStencil() const
{
	return 0;
}

inline void Hikari::Renderer::GetColorMask(bool & allowRed, bool & allowGreen, bool & allowBlue, bool & allowAlpha) const
{
}

inline void Hikari::Renderer::SetOverrideAlphaState(const AlphaState * alphaState)
{
}

inline void Hikari::Renderer::SetOverrideCullState(const CullState * cullState)
{
}

inline void Hikari::Renderer::SetOverrideDepthState(const DepthState * depthState)
{
}

inline void Hikari::Renderer::SetOverrideOffsetState(const OffsetState * offsetState)
{
}

inline void Hikari::Renderer::SetOverrideStencilState(const StencilState * stencilState)
{
}

inline void Hikari::Renderer::SetOverrideWireState(const WireState * wireState)
{
}

inline const AlphaState * Hikari::Renderer::GetOverrideAlphaState() const
{
	return nullptr;
}

inline const CullState * Hikari::Renderer::GetOverrideCullState() const
{
	return nullptr;
}


inline bool Hikari::Renderer::InTexture2DMap(const Texture2D * texture)
{
	return false;
}
void Hikari::Renderer::Bind(const VertexShader * vFormat)
{
}

void Hikari::Renderer::Unbind(const VertexShader * vFormat)
{
}



void Hikari::Renderer::Bind(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Unbind(const PixelShader * vFormat)
{
}

void Hikari::Renderer::UnBindAll(const PixelShader * vFormat)
{
}

void Hikari::Renderer::Update(const PixelShader * vbuffer)
{
}

void Hikari::Renderer::UpdateAll(const PixelShader * vbuffer)
{
}

void Hikari::Renderer::BindAll(const VertexBuffer * vformat)
{
}

void Hikari::Renderer::UnBindAll(const VertexBuffer * vFormat)
{
}



////Rotate和Translate是对于Object矩阵的变化
//void RotateByAix(int x, int y, int z, float angle)
//{
//      //绕任意轴旋转的时候，先将该轴转到与坐标轴重合，然后旋转，然后乘以逆矩阵再返回去
//      float M[3][3];
//      M[0][0] = x * x * (1 - cos(angle)) + cos(angle);
//      M[0][1] = x * y * (1 - cos(angle)) - z*sin(angle);
//      M[0][2] = x * z * (1 - cos(angle)) + y * sin(angle);
//
//      M[1][0] = y*x*(1 - cos(angle)) + z*sin(angle);
//      M[1][1] = y*y*(1 - cos(angle)) + cos(angle);
//      M[1][2] = y*z*(1 - cos(angle)) - x*sin(angle);
//
//      M[2][0] = x*z*(1 - cos(angle)) - y*sin(angle);
//      M[2][1] = y*z*(1 - cos(angle)) + x*sin(angle);
//      M[2][2] = z*z*(1 - cos(angle)) + cos(angle);
//
//      Matrix4X4 temp;
//      temp = Matrix3X3(&M[0][0]);
//      OBJECT = temp * OBJECT;
//}
//
//void Translate(Vector3D direction, float distance)
//{
//
//      float Object[][4] =
//      {
//               1.0f, 0.0f, 0.0f, direction.Normal()[0] * distance,
//               0.0f, 1.0f, 0.0f, direction.Normal()[1] * distance,
//               0.0f, 0.0f, 1.0f, direction.Normal()[2] * distance,
//               0.0f, 0.0f, 0.0f, 1.0f,
//      };
//      Matrix4X4 temp;
//      temp = Matrix4X4(&Object[0][0]);
//      OBJECT = temp * OBJECT;
//}


//void WorldToView(Point3D* point, int size)
//{
//      //平移观察坐标原点到世界坐标原点
//      //进行旋转，分别让xview ,yview,zview对应为世界坐标的x,y,z
//      //p0为观察原点 
//      /*
//      //u,v,n是uvn轴的分量
//      M(WC,VC) = R * T
//      */
//}

//void NDC2DC(RenderList& rendlist, int width, int height, float pr, float pe, float pb, float pt, float pf, float pn)
//{
//      float dc[][4] =
//      {
//               width*(pr - pe) / 2.0f, 0.0f, 0.0f, width*(pr + pe) / 2.0f,
//               0.0f, height*(pb - pt) / 2.0f, 0, height*(2.0f - pt - pb) / 2.0f,
//               0, 0, pf - pn, pn,
//               0, 0, 0, 1
//      };
//      Matrix4X4 d(&dc[0][0]);
//      PolyF4DV1* curr_poly;
//      for (int i = 0; i < rendlist.num_polys; i++)
//      {
//               curr_poly = rendlist.poly_ptrs[i];
//               if (curr_poly == nullptr)
//                         continue;
//               for (int index = 0; index < 3; index++)
//               {
//                         curr_poly->tvlist[index] = d* Point3D(curr_poly->tvlist[index][0],curr_poly->tvlist[index][1],1.0f);
//               }
//      }
//}

//void NDC2DC(Object* object, int width, int height, float pr, float pe, float pb, float pt, float pf, float pn)
//{
//      float dc[][4] =
//      {
//               width*(pr - pe) / 2.0f, 0.0f, 0.0f, width*(pr + pe) / 2.0f,
//               0.0f, height*(pb - pt) / 2.0f, 0, height*(2.0f - pt - pb) / 2.0f,
//               0, 0, pf - pn, pn,
//               0, 0, 0, 1
//      };
//      Matrix4X4 d(&dc[0][0]);
//      Object4DV1* curr_poly = static_cast<Object4DV1*>(object);
//
//               for (int j = 0; j < curr_poly->num_vertices; j++)
//               {
//                         curr_poly->vlist_trans[j] = d * Point3D(curr_poly->vlist_trans[j][0], curr_poly->vlist_trans[j][1], 1.0f);
//               }   
//}
////这里指定的裁剪窗口转换后的坐标是世界坐标系下-1~1
//void Ortho(Vector3D& p, float znear, float zfar, float xmax, float xmin, float ymax, float ymin)
//{
//      float PROJECTION_M[4][4];
//      PROJECTION_M[0][0] = 2.0f / (xmax - xmin);
//      PROJECTION_M[1][1] = 2.0f / (ymax - ymin);
//      PROJECTION_M[2][2] = -2.0f / (znear - zfar);
//      PROJECTION_M[0][3] = -(xmax + xmin) / (xmax - xmin);
//      PROJECTION_M[1][3] = -(ymax + ymin) / (ymax - ymin);
//      PROJECTION_M[2][3] = (znear + zfar) / (znear - zfar);
//      PROJECTION_M[3][3] = 1;
//
//      PROJECTION = Matrix4X4(&PROJECTION_M[0][0]);
//      PROJECTION * p;
//}

//void lineScan(Cell a, void* data)//需要传递一个包含所有图元的容器，然后在其中遍历，并取出图元的类型，例如点，线，三角等，然后将它的数据部分取出，进行插值
//{
//      Point3D p1;
//      Point3D p2;
//      Point3D p3;
//
//      float vmin;
//      float vmax;
//      float temp;
//      vmin = p3[2] < (temp = (p1[2] < p2[2]) ? p1[2] : p2[2]) ? p3[2] : temp;
//      vmax = p3[2] > (temp = (p1[2] > p2[2]) ? p1[2] : p2[2]) ? p3[2] : temp;
//      std::vector<std::list<EDGE>> s(vmax - vmin + 1);
//      if (a = POINT_TYPE)
//      {
//
//      }
//      else if (a = LINE_TYPE)
//      {
//
//      }
//      else if (a = TRIANGLE_TYPE)
//      {
//               //data里面包含有定点位置，法线，颜色，正切值，uv坐标等
//               //对于所有的属性都需要插值计算
//
//      }
//}
//
//int Load_Object_PLG(Object4DV1* obj, char* filename, Vector4D& scale, Vector4D& pos, Vector4D& rot)
//{
//      FILE * fp = nullptr;
//      char buffer[256];
//      char* token_string;
//      memset(obj, 0, sizeof(Object4DV1));
//      obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;
//      obj->world_pos = pos;
//      if (!(fp = fopen(filename, "r")))
//      {
//               return 0;
//      }
//      
//      if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//      {
//               return 0;
//      }
//      sscanf(token_string, "%s %d %d", obj->name, &obj->num_vertices, &obj->num_polys);
//      for (int vertex = 0; vertex < obj->num_vertices;vertex++)
//      {
//               if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//               {
//                         return 0;
//               }
//               sscanf(token_string, "%f %f %f", &obj->vlist_local[vertex][0],
//                         &obj->vlist_local[vertex][1],
//                         &obj->vlist_local[vertex][2]);
//               obj->vlist_local[vertex][3] = 1;
//               obj->vlist_local[vertex][0] *= scale[0];
//               obj->vlist_local[vertex][1] *= scale[1];
//               obj->vlist_local[vertex][2] *= scale[2];
//      
//      }
//      Compute_Object4DV1_Radius(obj);
//      int poly_surface_desc = 0;
//      int poly_num_verts = 0;
//      char temp_string[8];
//      //Assemble the primitive
//      for (int poly = 0; poly < obj->num_polys; poly++)
//      {
//               if (!(token_string = Get_Line_PLG(buffer, 255, fp)))
//               {
//                         return 0;
//               }
//               sscanf(token_string, "%s %d %d %d %d", temp_string, &poly_num_verts, &obj->plist[poly].vert[0],
//                         &obj->plist[poly].vert[1], &obj->plist[poly].vert[2]);
//               if (temp_string[0] == '0' && toupper(temp_string[1] == 'x'))
//                         sscanf(temp_string, "%x", &poly_surface_desc);
//               else
//                         poly_surface_desc = atoi(temp_string);
//
//               obj->plist[poly].vlist = obj->vlist_local;
//
//               if ((poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG))
//               {
//                         //SET_BIT(obj->plist[poly].attr, POLY3DV1_ATTR_2SIDED);
//                         int red = ((poly_surface_desc & 0x0f00) >> 8);
//                         int green = (poly_surface_desc & 0x00f0) >> 4;
//                         int blue = (poly_surface_desc & 0x000f);
//                         
//                         obj->plist[poly].color = RGB16Bit(red, green, blue);
//
//               }
//               else
//               {
//                         //8bit Color Now has beed Dispatch
//               }
//               int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);
//               //Set Shade Attr
//               obj->plist[poly].state = POLY4DV1_STATE_ACTIVE; 
//      }
//      fclose(fp);
//      return 1;
//}