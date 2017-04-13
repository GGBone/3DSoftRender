#pragma once
#include "Renderer.h"
#include "Dx11RenderData.h"
#include "Dx11Shader.h"
#include "Dx11Buffer.h"
namespace Hikari
{
	class DirectRenderer : public Renderer
	{
		//============================================================================
		// Platform-dependent portion of the interface.
	public:
		DirectRenderData* mData;
	public:
		DirectRenderer(int width, int height, int numMultisamples, HWND handle);
		~DirectRenderer();


		void SetViewport(int xPosition, int yPosition, int width,
			int height);
		void GetViewport(int& xPosition, int& yPosition, int& width,
			int& height) const;
		void SetDepthRange(float zMin, float zMax);
		void GetDepthRange(float& zMin, float& zMax) const;
		void Resize(int width, int height);

		// Support for clearing the color, depth, and stencil buffers
		virtual void ClearBackBuffer();
		virtual void ClearDepthBuffer();
		virtual void ClearStencilBuffer();
		virtual void ClearBuffers();

		virtual void ClearDepthBuffer(int x, int y, int w, int h);
		virtual void ClearStencilBuffer(int x, int y, int w, int h);
		virtual void ClearBuffers(int x, int y, int w, int h);
		virtual void ClearBackBuffer(int x, int y, int w, int h);
		virtual void SetClearColor(const Float4& color) override;
		virtual void DisplayBackBuffer() override;
		void SetColorMask(bool allowRed, bool allowGreen,
			bool allowBlue, bool allowAlpha);


		bool PreDraw();
		void PostDraw();


		void Draw(const unsigned char* screenBuffer, bool reflectY = false);
		void DrawPrimitive(const Visual* visual);
		// The entry point for drawing 2D text.
		void Draw(int x, int y, const Float4& color,
			const std::string& message);


		// Get the name of the primary graphics device.
		virtual const std::string& GetDeviceName() const override;

		// Create an vertex buffer.

		virtual void DestroyVertexBuffer(Buffer* buffer) override;

		virtual void DestroyBuffer(Buffer* buffer);
		// Create an index buffer.

		virtual void DestroyIndexBuffer(Buffer* buffer) override;



		virtual void DestroyConstantBuffer(ConstantBuffer* buffer) override;

		virtual void DestroyStructuredBuffer(StructuredBuffer* buffer) override;

		virtual Scene* CreateScene() override;


		virtual Scene* CreatePlane(float size, const AVector& N = AVector(0, 1, 0)) override;


		virtual Scene* CreateScreenQuad(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float z = 0.0f) override;


		virtual Scene* CreateSphere(float radius, float tesselation = 4) override;

		// Create a cube in 3D.
		// The cube will be centered at the origin.
		// @param size The length of each edge of the cube.
		virtual Scene* CreateCube(float size) override;

		// Create a cylinder that is aligned to a particular axis.
		// @param baseRadius The radius of the base (bottom) of the cylinder.
		// @param apexRadius The radius of the apex (top) of the cylinder.
		// @param height The height of the sphere along the axis of the cylinder.
		// @param axis The axis to align the cylinder. Default to the global Y axis.
		virtual Scene* CreateCylinder(float baseRadius, float apexRadius, float height, const AVector& axis = AVector(0, 1, 0)) override;

		// Create a cone.
		// Cones are always aligned to (0, 1, 0) with the base of the cone 
		// centered at (0, 0, 0) and apex at (0, height, 0).
		// A cone is just a cylinder with an apex radius of 0.
		// @param baseRadius The radius of the base of the cone.
		// @param height The height of the cone.
		virtual Scene* CreateCone(float baseRadius, float height) override;

		// Create a 3D arrow.
		// Arrows can be used to represent the direction an object or light is pointing.
		// @param tail The tail (begin point) of the arrow.
		// @param head The head (end point) of the arrow.
		// @param radius The radius of the body of the arrow.
		virtual Scene* CreateArrow(const AVector& tail = AVector(0, 0, 0), const AVector& head = AVector(0, 0, 1), float radius = .05f) override;

		// Create a 3D axis with X, -X, Y, -Y, Z, -Z axes.
		// Primarily used to debug an object's position and direction in 3D space.
		// The axis is aligned to 0,0,0 and the global X, Y, Z axes.
		// @param radius is the radius of the axis arms.
		// @param length is the length is the length of each axis arm.
		virtual Scene* CreateAxis(float radius = 0.05f, float length =0.5f) override;

		virtual void DestroyScene(Scene* scene) override;

		virtual Mesh* CreateMesh() override;
		virtual void DestroyMesh(Mesh* mesh) override;

		virtual Shader* CreateShader() override;
		virtual void DestroyShader(Shader* shader) override;

		// Create a texture from a file.
		virtual Texture* CreateTexture(const std::wstring& fileName) override;
		virtual Texture* CreateTextureCube(const std::wstring& fileName) override;

		virtual Texture* CreateTexture1D(uint16_t width, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual Texture* CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual Texture* CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;
		virtual Texture* CreateTextureCube(uint16_t size, uint16_t numCubes = 1, const Texture::TextureFormat& format = Texture::TextureFormat(), CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;

		// Create an null texture (can be loaded later using Texture::LoadTexture2D function.
		virtual Texture* CreateTexture() override;

		// Release a texture.
		virtual void DestroyTexture(Texture* texture) override;

		// Create a render target
		virtual RenderTarget* CreateRenderTarget() override;
		virtual void DestroyRenderTarget(RenderTarget* renderTarget) override;

		//// Create a GPU query object. Used for performance profiling, occlusion queries,
		//// or primitive output queries.
		//virtual std::shared_ptr<Query> CreateQuery(Query::QueryType queryType = Query::QueryType::Timer, uint8_t numBuffers = 3) override;
		//virtual void DestoryQuery(std::shared_ptr<Query> query) override;


		virtual SamplerState* CreateSamplerState() override;
		virtual void DestroySampler(SamplerState* sampler) override;

		virtual Material* CreateMaterial() override;
		virtual void DestroyMaterial(Material* material) override;

		virtual PipelineState* CreatePipelineState() override;
		virtual void DestoryPipelineState(PipelineState* pipeline) override;

		virtual Buffer* CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) override;
		virtual Buffer* CreateDoubleVertexBuffer(const double* data, unsigned int count, unsigned int stride) override;
		virtual Buffer* CreateUIntIndexBuffer(const unsigned int* data, unsigned int sizeInBytes) override;
		virtual ConstantBuffer* CreateConstantBuffer(const void* data, size_t size) override;
		virtual StructuredBuffer* CreateStructuredBuffer(void* data, unsigned int count, unsigned int stride, CPUAccess cpuAccess = CPUAccess::None, bool gpuWrite = false) override;

	private:
		ID3D11Debug* m_pDebugLayer;
		
		std::string m_pDeviceName;

		typedef std::vector<Scene*> SceneList;
		SceneList m_Scene;

		typedef std::vector<Buffer*> BufferList;
		BufferList m_Buffer;

		typedef std::vector<Mesh*> MeshList;
		MeshList m_Meshes;

		typedef std::vector<Shader*> ShaderList;
		ShaderList m_Shaders;

		typedef std::vector<Texture*> TextureList;
		TextureList m_Texture;

		typedef std::map<std::wstring, Texture*> TextureMap;
		TextureMap m_TextureByName;

		typedef std::vector<RenderTarget*> RenderTargetList;
		RenderTargetList m_RenderTargets;

		Texture* m_pDefaultTextures;

		typedef std::vector<SamplerState*> SamplerList;
		SamplerList m_Samplers;

		typedef std::vector<Material*> MaterialList;
		MaterialList* m_Materials;

		typedef std::vector<PipelineState*> PipelineList;
		PipelineList m_Pilelines;

		PipelineState* m_pDefaultPipeline;

		void LoadDefaultResources();
	
	};

	

}