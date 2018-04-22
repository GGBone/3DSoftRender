#pragma once

#include "GraphicsLIB.h"
#include "Loader\Loader.h"
#include "Graphics\Query.h"
#include "Math\Base\Float4.h"
#include "Application\Application.h"
#include "Graphics\CPUAccess.h"
#include "Graphics\Texture.h"
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
	class VisualEffect;
	class Application;
	class Renderer : public Object
	{
	public:
		ProgressEvent mLoadingProgress;
		// Get the name of the primary graphics device.
		virtual const std::string& GetDeviceName() const = 0;

		virtual ~Renderer() 
		{
			int a = 3;
		};

		// Create an vertex buffer.
		template<typename T>
		std::shared_ptr<Buffer> CreateVertexBuffer(const T& data);
		virtual void DestroyVertexBuffer(std::shared_ptr<Buffer> buffer) = 0;

		// Create an index buffer.
		template<typename T>
		std::shared_ptr<Buffer> CreateIndexBuffer(const T& data);
		virtual void DestroyIndexBuffer(std::shared_ptr<Buffer> buffer) = 0;

	
		template<typename T>
		std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const T& data);
		virtual void DestroyConstantBuffer(std::shared_ptr<ConstantBuffer> buffer) = 0;

		
		template<typename T>
		std::shared_ptr<StructuredBuffer> CreateStructuredBuffer(const std::vector<T>& data, CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false);
		virtual void DestroyStructuredBuffer(std::shared_ptr<StructuredBuffer> buffer) = 0;

		template<typename T>
		std::shared_ptr<RWBuffer> CreateRWBuffer(const T& data);
		virtual void DestroyRWBuffer(std::shared_ptr<RWBuffer> buffer) = 0;
		virtual std::shared_ptr<Scene> CreateScene() = 0;

	
		virtual std::shared_ptr<Scene> CreatePlane(float size, const AVector& N = AVector(0, 1, 0)) = 0;

	
		virtual std::shared_ptr<Scene> CreateScreenQuad(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float z = 0.0f) = 0;

	
		virtual std::shared_ptr<Scene> CreateSphere(float radius, float tesselation = 4) = 0;

	
		virtual std::shared_ptr<Scene> CreateCube(float size) = 0;

		virtual std::shared_ptr<Scene> CreateCylinder(float baseRadius, float apexRadius, float height, const AVector& axis = AVector(0, 1, 0)) = 0;

	
		virtual std::shared_ptr<Scene> CreateCone(float baseRadius, float height) = 0;

	
		virtual std::shared_ptr<Scene> CreateArrow(const AVector& tail = AVector(0, 0, 0), const AVector& head = AVector(0, 0, 1), float radius = 0.05f) = 0;


		virtual std::shared_ptr<Scene> CreateAxis(float radius = 0.05f, float length = 0.5f) = 0;

		virtual std::shared_ptr<Query> CreateQuery(Query::QueryType queryType = Query::QueryType::Timer, uint8_t numBuffers = 3) = 0;

		virtual void DestroyScene(std::shared_ptr<Scene> scene) = 0;

		virtual std::shared_ptr<Mesh> CreateMesh() = 0;
		virtual void DestroyMesh(std::shared_ptr<Mesh> mesh) = 0;

		virtual std::shared_ptr<Shader> CreateShader() = 0;
		virtual void DestroyShader(std::shared_ptr<Shader> shader) = 0;

		// Create a texture from a file.
		virtual std::shared_ptr<Texture> CreateTexture(const std::wstring& fileName) = 0;
		virtual std::shared_ptr<Texture> CreateTextureCube(const std::wstring& fileName) = 0;

		// Create an empty texture of a predefined size.
		virtual std::shared_ptr<Texture> CreateTexture1D(uint16_t width, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual std::shared_ptr<Texture> CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual std::shared_ptr<Texture> CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;
		virtual std::shared_ptr<Texture> CreateTextureCube(uint16_t size, uint16_t numCubes = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) = 0;

		// Create an null texture (can be loaded later using Texture::LoadTexture2D function.
		virtual std::shared_ptr<Texture> CreateTexture() = 0;

		// Release a texture.
		virtual void DestroyTexture(std::shared_ptr<Texture> texture) = 0;

		// Create a render target
		virtual std::shared_ptr<RenderTarget> CreateRenderTarget() = 0;
		virtual void DestroyRenderTarget(std::shared_ptr<RenderTarget> renderTarget) = 0;

		virtual std::shared_ptr<SamplerState> CreateSamplerState() = 0;
		virtual void DestroySampler(std::shared_ptr<SamplerState> sampler) = 0;

		virtual std::shared_ptr<Material> CreateMaterial() = 0;
		virtual void DestroyMaterial(std::shared_ptr<Material> material) = 0;

		virtual std::shared_ptr<PipelineState> CreatePipelineState() = 0;
		virtual void DestoryPipelineState(std::shared_ptr<PipelineState> pipeline) = 0;

		virtual std::shared_ptr<Buffer> CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) = 0;
		virtual std::shared_ptr<Buffer> CreateUINTVertexBuffer(const UINT* data, unsigned int count, unsigned int stride) = 0;

		virtual std::shared_ptr<Buffer> CreateDoubleVertexBuffer(const double* data, unsigned int count, unsigned int stride) = 0;
		virtual std::shared_ptr<Buffer> CreateUIntIndexBuffer(const unsigned int* data, unsigned int sizeInBytes) = 0;
		virtual std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const void* data, size_t size) = 0;
		virtual std::shared_ptr<StructuredBuffer> CreateStructuredBuffer(void* data, unsigned int count, unsigned int stride, CPUAccess cpuAccess = CPUAccess::None,
			bool bSRV = true, bool bUAV = false, bool appendFlag  = false) = 0;
		virtual void OnInitialize(EventArgs& e) = 0;
		virtual std::shared_ptr<RWBuffer> CreateRWBuffer(void* data, unsigned int count, unsigned int stride, CPUAccess cpuAccess = CPUAccess::None) = 0;

		inline void swap_int(int *a, int*b)
		{
			*a ^= *b;
			*b ^= *a;
			*a ^= *b;
		}
	protected:	
		virtual void OnLoadingProgress(ProgressEventArgs& e);
	};

	// Template specializations for vertex buffers.
	template<>
	std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<float> >(const std::vector<float>& data);
	template<>
	std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<Float2> >(const std::vector<Float2>& data);
	template<>
	std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<Float3> >(const std::vector<Float3>& data);
	template<>
	std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<Float4> >(const std::vector<Float4>& data);
	//template<>
	//const Buffer* Renderer::CreateVertexBuffer< std::vector< aiVector3D > >( const std::vector< aiVector3D >& data );

	// Template specializations for index buffers.
	template<>
	std::shared_ptr<Buffer> Renderer::CreateIndexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data);

	template<>
	std::shared_ptr<Buffer> Renderer::CreateVertexBuffer< std::vector<unsigned int> >(const std::vector<unsigned int>& data);


	template< typename T >
	std::shared_ptr<ConstantBuffer> Renderer::CreateConstantBuffer(const T& data)
	{
		return CreateConstantBuffer(&data, sizeof(T));
	}

	template<typename T>
	std::shared_ptr<StructuredBuffer> Renderer::CreateStructuredBuffer(const std::vector<T>& data, CPUAccess cpuAccess, bool gpuWrite)
	{
		size_t stride = sizeof(T);
		size_t numElements = data.size();
		return CreateStructuredBuffer((void*)data.data(), (unsigned int)numElements, (unsigned int)stride, cpuAccess, true,gpuWrite);
	}
	template<typename T>
	inline std::shared_ptr<RWBuffer> Renderer::CreateRWBuffer(const T & data)
	{
		return CreateRWBuffer(&data,1,sizeof(T));
	}
}