#pragma once

#include "GraphicsLIB.h"

#include "Float4.h"

#include "Buffer.h"

#include "Visual.h"

#include <DirectXMath.h>
#include "HPoint.h"
#include "RenderData.h"
#include "Texture.h"
#include "CPUAccess.h"
using namespace DirectX;

namespace Hikari
{
	class Mesh;
	class Scene;
	class Material;
	class RenderTarget;
	class Texture;
	class StructuredBuffer;
	class PipelineState;
	class Camera;
	class Renderer
	{
	public:

		// Get the name of the primary graphics device.
		virtual const std::string& GetDeviceName() const = 0;

		// Create an vertex buffer.
		template<typename T>
		Buffer* CreateVertexBuffer(const T& data);
		virtual void DestroyVertexBuffer(Buffer* buffer) = 0;

		// Create an index buffer.
		template<typename T>
		Buffer* CreateIndexBuffer(const T& data);
		virtual void DestroyIndexBuffer(Buffer* buffer) = 0;

	
		template<typename T>
		ConstantBuffer* CreateConstantBuffer(const T& data);
		virtual void DestroyConstantBuffer(ConstantBuffer* buffer) = 0;

		
		template<typename T>
		StructuredBuffer* CreateStructuredBuffer(const std::vector<T>& data, CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false);
		virtual void DestroyStructuredBuffer(StructuredBuffer* buffer) = 0;

		virtual Scene* CreateScene() = 0;

	
		virtual Scene* CreatePlane(float size, const AVector& N = AVector(0, 1, 0)) = 0;

	
		virtual Scene* CreateScreenQuad(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float z = 0.0f) = 0;

	
		virtual Scene* CreateSphere(float radius, float tesselation = 4) = 0;

		// Create a cube in 3D.
		// The cube will be centered at the origin.
		// @param size The length of each edge of the cube.
		virtual Scene* CreateCube(float size) = 0;

		// Create a cylinder that is aligned to a particular axis.
		// @param baseRadius The radius of the base (bottom) of the cylinder.
		// @param apexRadius The radius of the apex (top) of the cylinder.
		// @param height The height of the sphere along the axis of the cylinder.
		// @param axis The axis to align the cylinder. Default to the global Y axis.
		virtual Scene* CreateCylinder(float baseRadius, float apexRadius, float height, const AVector& axis = AVector(0, 1, 0)) = 0;

		// Create a cone.
		// Cones are always aligned to (0, 1, 0) with the base of the cone 
		// centered at (0, 0, 0) and apex at (0, height, 0).
		// A cone is just a cylinder with an apex radius of 0.
		// @param baseRadius The radius of the base of the cone.
		// @param height The height of the cone.
		virtual Scene* CreateCone(float baseRadius, float height) = 0;

		// Create a 3D arrow.
		// Arrows can be used to represent the direction an object or light is pointing.
		// @param tail The tail (begin point) of the arrow.
		// @param head The head (end point) of the arrow.
		// @param radius The radius of the body of the arrow.
		virtual Scene* CreateArrow(const AVector& tail = AVector(0, 0, 0), const AVector& head = AVector(0, 0, 1), float radius = 0.05f) = 0;

		// Create a 3D axis with X, -X, Y, -Y, Z, -Z axes.
		// Primarily used to debug an object's position and direction in 3D space.
		// The axis is aligned to 0,0,0 and the global X, Y, Z axes.
		// @param radius is the radius of the axis arms.
		// @param length is the length is the length of each axis arm.
		virtual Scene* CreateAxis(float radius = 0.05f, float length = 0.5f) = 0;

		virtual void DestroyScene(Scene* scene) = 0;

		virtual Mesh* CreateMesh() = 0;
		virtual void DestroyMesh(Mesh* mesh) = 0;

		virtual Shader* CreateShader() = 0;
		virtual void DestroyShader(Shader* shader) = 0;

		// Create a texture from a file.
		virtual Texture* CreateTexture(const std::string& fileName) = 0;
		virtual Texture* CreateTextureCube(const std::string& fileName) = 0;

		// Create an empty texture of a predefined size.
		virtual Texture* CreateTexture1D(uint16_t width, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual Texture* CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual Texture* CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual Texture* CreateTextureCube(uint16_t size, uint16_t numCubes = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;

		// Create an null texture (can be loaded later using Texture::LoadTexture2D function.
		virtual Texture* CreateTexture() = 0;

		// Release a texture.
		virtual void DestroyTexture(Texture* texture) = 0;

		// Create a render target
		virtual RenderTarget* CreateRenderTarget() = 0;
		virtual void DestroyRenderTarget(RenderTarget* renderTarget) = 0;

		//// Create a GPU query object. Used for performance profiling, occlusion queries,
		//// or primitive output queries.
		//virtual std::shared_ptr<Query> CreateQuery(Query::QueryType queryType = Query::QueryType::Timer, uint8_t numBuffers = 3) = 0;
		//virtual void DestoryQuery(std::shared_ptr<Query> query) = 0;
		

		virtual SamplerState* CreateSamplerState() = 0;
		virtual void DestroySampler(SamplerState* sampler) = 0;

		virtual Material* CreateMaterial() = 0;
		virtual void DestroyMaterial(Material* material) = 0;

		virtual PipelineState* CreatePipelineState() = 0;
		virtual void DestoryPipelineState(PipelineState* pipeline) = 0;

		virtual Buffer* CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) = 0;
		virtual Buffer* CreateDoubleVertexBuffer(const double* data, unsigned int count, unsigned int stride) = 0;
		virtual Buffer* CreateUIntIndexBuffer(const unsigned int* data, unsigned int sizeInBytes) = 0;
		virtual ConstantBuffer* CreateConstantBuffer(const void* data, size_t size) = 0;
		virtual StructuredBuffer* CreateStructuredBuffer(void* data, unsigned int count, unsigned int stride, CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		void Initialize(int width, int height, Texture::TextureFormat colorFormat,

			Texture::TextureFormat depthStencilFormat, int numMultisamples);

		void Terminate();

		inline int GetWidth() const;

		inline int GetHeight() const;


		inline int GetNumMultisamples() const;


		inline void SetCamera(Camera* camera)
		{
			mCamera = camera;
		}


		inline const Camera* GetCamera() const
		{
			return mCamera;
		}

		inline const HMatrix& GetViewMatrix() const;

		inline const HMatrix& GetProjectionMatrix() const;

		inline const HMatrix& GetPostProjectionMatrix() const;

		bool GetPickRay(int x, int y, APoint& origin, AVector& direction) const;

		virtual void SetClearColor(const Float4& color);
		

		inline const Float4& GetClearColor() const;

		inline void swap_int(int *a, int*b)
		{
			*a ^= *b;
			*b ^= *a;
			*a ^= *b;
		}
		
		// The entry points for drawing a single object.
		void Draw(const Visual* visual);
		void Draw(const Visual* visual, const VisualEffectInstance* instance);
	protected:
		int mWidth;
		int mHeight;
		Camera* mCamera;
		Texture::TextureFormat mColorFormat;
		Texture::TextureFormat mDepthStencilFormat;
		int mNumMultisamples;
	
		//Camera* mCamera;
		Float4 mClearColor;
		float mClearDepth;
		unsigned int mClearStencil;
	
		// The main entry point to drawing in the derived-class renderers.
		//dependence in Device
		//Same as DrawPrimitive in WM5
		//Call Sequence
		//DrawScene()               (etc.Draw(VisibleSet))
		//->DrawGeometry(Geometry)  (etc.Draw(Visiable))
		//->ApplyEffect()           (etc.Draw(Effect))
		//-> DrawElements();        (etc.DrawPrimitive(Visiable))
		virtual void DrawPrimitive(const Visual* visual) = 0;
	public:
		virtual void ClearBackBuffer() = 0;
		virtual void ClearDepthBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;
		virtual void ClearBackBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearDepthBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearStencilBuffer(int x, int y, int w, int h) = 0;
		virtual void ClearBuffers(int x, int y, int w, int h) = 0;
		virtual void DisplayBackBuffer() = 0;
		RendererData* mData;
		Renderer(RendererData* data);
	};

	// Template specializations for vertex buffers.
	template<>
	Buffer* Renderer::CreateVertexBuffer< std::vector<float> >(const std::vector<float>& data);
	template<>
	Buffer* Renderer::CreateVertexBuffer< std::vector<Float2> >(const std::vector<Float2>& data);
	template<>
	Buffer* Renderer::CreateVertexBuffer< std::vector<Float3> >(const std::vector<Float3>& data);
	template<>
	Buffer* Renderer::CreateVertexBuffer< std::vector<Float4> >(const std::vector<Float4>& data);
	//template<>
	//const Buffer* Renderer::CreateVertexBuffer< std::vector< aiVector3D > >( const std::vector< aiVector3D >& data );

	// Template specializations for index buffers.
	template<>
	Buffer* Renderer::CreateIndexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data);


	template< typename T >
	ConstantBuffer* Renderer::CreateConstantBuffer(const T& data)
	{
		return CreateConstantBuffer(&data, sizeof(T));
	}

	template<typename T>
	StructuredBuffer* Renderer::CreateStructuredBuffer(const std::vector<T>& data, CPUAccess cpuAccess, bool gpuWrite)
	{
		size_t stride = sizeof(T);
		size_t numElements = data.size();
		return CreateStructuredBuffer((void*)data.data(), (unsigned int)numElements, (unsigned int)stride, cpuAccess, gpuWrite);
	}
}