#pragma once
#include "Graphics\Renderer.h"

namespace Hikari
{
	class WindowApplicationBase;
	class Renderer;
	class DirectRenderer : public Renderer, public std::enable_shared_from_this<DirectRenderer>
	{
		//============================================================================
		// Platform-dependent portion of the interface.
	protected:
		virtual void CreateDevice(HINSTANCE hInstance);

		virtual void OnInitialize(EventArgs& e) override;

		virtual void OnLoadingProgress(ProgressEventArgs& e);
	public:
		DirectRenderer(WindowApplicationBase& application);
		~DirectRenderer();



		// Get the name of the primary graphics device.
		virtual const std::string& GetDeviceName() const override;

		ID3D11Device2* GetDevice() const;
		ID3D11DeviceContext2* GetDeviceContext() const;

		// Create an vertex buffer.

		virtual void DestroyVertexBuffer(std::shared_ptr<Buffer> buffer) override;

		virtual void DestroyBuffer(std::shared_ptr<Buffer> buffer);
		// Create an index buffer.

		virtual void DestroyIndexBuffer(std::shared_ptr<Buffer> buffer) override;

		virtual void DestroyConstantBuffer(std::shared_ptr<ConstantBuffer> buffer) override;

		virtual void DestroyStructuredBuffer(std::shared_ptr<StructuredBuffer> buffer) override;

		virtual void DestroyRWBuffer(std::shared_ptr<RWBuffer> buffer) override;

		virtual std::shared_ptr<Scene> CreateScene() override;


		virtual std::shared_ptr<Scene> CreatePlane(float size, const AVector& N = AVector(0, 1, 0)) override;


		virtual  std::shared_ptr<Scene> CreateScreenQuad(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float z = 0.0f) override;


		virtual  std::shared_ptr<Scene> CreateSphere(float radius, float tesselation = 4.0f) override;

		// Create a cube in 3D.
		// The cube will be centered at the origin.
		// @param size The length of each edge of the cube.
		virtual  std::shared_ptr<Scene> CreateCube(float size) override;

		// Create a cylinder that is aligned to a particular axis.
		// @param baseRadius The radius of the base (bottom) of the cylinder.
		// @param apexRadius The radius of the apex (top) of the cylinder.
		// @param height The height of the sphere along the axis of the cylinder.
		// @param axis The axis to align the cylinder. Default to the global Y axis.
		virtual  std::shared_ptr<Scene> CreateCylinder(float baseRadius, float apexRadius, float height, const AVector& axis = AVector(0, 1, 0)) override;

		// Create a cone.
		// Cones are always aligned to (0, 1, 0) with the base of the cone 
		// centered at (0, 0, 0) and apex at (0, height, 0).
		// A cone is just a cylinder with an apex radius of 0.
		// @param baseRadius The radius of the base of the cone.
		// @param height The height of the cone.
		virtual  std::shared_ptr<Scene> CreateCone(float baseRadius, float height) override;

		// Create a 3D arrow.
		// Arrows can be used to represent the direction an object or light is pointing.
		// @param tail The tail (begin point) of the arrow.
		// @param head The head (end point) of the arrow.
		// @param radius The radius of the body of the arrow.
		virtual  std::shared_ptr<Scene> CreateArrow(const AVector& tail = AVector(0, 0, 0), const AVector& head = AVector(0, 0, 1), float radius = .05f) override;

		// Create a 3D axis with X, -X, Y, -Y, Z, -Z axes.
		// Primarily used to debug an object's position and direction in 3D space.
		// The axis is aligned to 0,0,0 and the global X, Y, Z axes.
		// @param radius is the radius of the axis arms.
		// @param length is the length is the length of each axis arm.
		virtual  std::shared_ptr<Scene> CreateAxis(float radius = 0.05f, float length =0.5f) override;

		virtual void DestroyScene(std::shared_ptr<Scene> scene) override;

		virtual  std::shared_ptr<Mesh> CreateMesh() override;
		virtual void DestroyMesh(std::shared_ptr<Mesh> mesh) override;

		virtual  std::shared_ptr<Shader> CreateShader() override;
		virtual void DestroyShader(std::shared_ptr<Shader> shader) override;

		// Create a texture from a file.
		virtual  std::shared_ptr<Texture> CreateTexture(const std::wstring& fileName) override;
		virtual  std::shared_ptr<Texture> CreateTextureCube(const std::wstring& fileName) override;

		virtual  std::shared_ptr<Texture> CreateTexture1D(uint16_t width, uint16_t slices = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual  std::shared_ptr<Texture> CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual  std::shared_ptr<Texture> CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual  std::shared_ptr<Texture> CreateTextureCube(uint16_t size, uint16_t numCubes = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;

		// Create an null texture (can be loaded later using Texture::LoadTexture2D function.
		virtual  std::shared_ptr<Texture> CreateTexture() override;

		virtual  std::shared_ptr<Texture> GetDefaultTexture() const;

		// Release a texture.
		virtual void DestroyTexture(std::shared_ptr<Texture> texture) override;

		// Create a render target
		virtual  std::shared_ptr<RenderTarget> CreateRenderTarget() override;
		virtual void DestroyRenderTarget(std::shared_ptr<RenderTarget> renderTarget) override;

		//// Create a GPU query object. Used for performance profiling, occlusion queries,
		//// or primitive output queries.
		//virtual std::shared_ptr<Query> CreateQuery(Query::QueryType queryType = Query::QueryType::Timer, uint8_t numBuffers = 3) override;
		//virtual void DestoryQuery(std::shared_ptr<Query> query) override;


		virtual  std::shared_ptr<SamplerState> CreateSamplerState() override;
		virtual void DestroySampler(std::shared_ptr<SamplerState> sampler) override;

		virtual  std::shared_ptr<Material> CreateMaterial() override;
		virtual void DestroyMaterial(std::shared_ptr<Material> material) override;

		virtual  std::shared_ptr<PipelineState> CreatePipelineState() override;
		virtual void DestoryPipelineState(std::shared_ptr<PipelineState> pipeline) override;

		virtual  std::shared_ptr<Buffer> CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) override;
		virtual  std::shared_ptr<Buffer> CreateDoubleVertexBuffer(const double* data, unsigned int count, unsigned int stride) override;
		virtual  std::shared_ptr<Buffer> CreateUINTVertexBuffer(const UINT* data, unsigned int count, unsigned int stride) override;
		virtual  std::shared_ptr<Buffer> CreateUIntIndexBuffer(const unsigned int* data, unsigned int sizeInBytes) override;
		virtual  std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const void* data, size_t size) override;
		virtual  std::shared_ptr<StructuredBuffer> CreateStructuredBuffer(void* data, unsigned int count, unsigned int stride, CPUAccess cpuAccess = CPUAccess::None,
			bool bSRV = true,bool bUAV = false,bool appendFlag = false) override;
		virtual  std::shared_ptr<RWBuffer> CreateRWBuffer(void* data, unsigned int count, unsigned int stride,CPUAccess cpuAccess = CPUAccess::None) override;
		virtual std::shared_ptr<Query> CreateQuery(Query::QueryType queryType = Query::QueryType::Timer, uint8_t numBuffers = 3) override;

	private:
		ID3D11Debug* m_pDebugLayer;
		ID3D11Device2* m_pDevice;
		ID3D11DeviceContext2* m_pDeviceContext;

		std::string m_DeviceName;

		typedef std::vector<std::shared_ptr<Scene>> SceneList;
		SceneList m_Scenes;

		typedef std::vector<std::shared_ptr<Buffer>> BufferList;
		BufferList m_Buffers;

		typedef std::vector<std::shared_ptr<Mesh>> MeshList;
		MeshList m_Meshes;

		typedef std::vector<std::shared_ptr<Shader>> ShaderList;
		ShaderList m_Shaders;

		typedef std::vector<std::shared_ptr<Texture>> TextureList;
		TextureList m_Textures;

		typedef std::map<std::wstring, std::shared_ptr<Texture>> TextureMap;
		TextureMap m_TextureByName;

		typedef std::vector<std::shared_ptr<RenderTarget>> RenderTargetList;
		RenderTargetList m_RenderTargets;

		std::shared_ptr<Texture> m_pDefaultTextures;

		typedef std::vector<std::shared_ptr<SamplerState>> SamplerList;
		SamplerList m_Samplers;

		typedef std::vector<std::shared_ptr<Material>> MaterialList;
		MaterialList m_Materials;

		typedef std::vector<std::shared_ptr<PipelineState>> PipelineList;
		PipelineList m_Pipelines;

		typedef std::vector<std::shared_ptr<Query>> QueryList;
		QueryList m_Queries;
		std::shared_ptr<PipelineState> m_pDefaultPipeline;

		void LoadDefaultResources();
	
	};

	

}