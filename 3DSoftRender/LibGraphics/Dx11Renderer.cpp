#include "GraphicsPCH.h"
#include "RenderData.h"
#include "Dx11Renderer.h"
#include "Dx11RenderData.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11StructureBuffer.h"
#include "Dx11Texture.h"
#include "Material.h"
#include "Dx11Scene.h"
#include "Dx11Mesh.h"
#include "Dx11Shader.h"
#include "Dx11RenderTarget.h"
#include "Dx11SamplerState.h"
#include "Dx11PipelineState.h"
#include "Dx11SamplerState.h"
#include "RenderEventArgs.h"
#include "VisualEffect.h"
#include "Dx11RWBuffer.h"
#include <sstream>

using namespace Hikari;

inline Float4 RotationFromTwoVectors(const AVector& u, const AVector& v)
{
	float normUV = sqrtf(u.Dot(u)) * (v.Dot( v));
	float real = normUV + u.Dot(v);

	AVector vec;

	if (real < 1.e-6f * normUV)
	{
		real = 0.0f;
		vec = (abs(u[0]) > abs(u[2])) ? Float3(-u[1], u[0], 0.0f) : Float3(0.0f, -u[2], u[1]);
	}
	else
	{
		vec = u.Cross(v);
	}

	return Float4(real, vec.X(),vec.Y(),vec.Z());
}


DirectRenderer::DirectRenderer(int width, int height, int numMultisamples, HWND handle)
	:Renderer(new RendererData(width,height,handle))
{
	mData = new DirectRenderData(width, height, numMultisamples, handle);
	Initialize();

}
DirectRenderer::~DirectRenderer()
{
	delete mData;
	Terminate();
}


void DirectRenderer::GetViewport(int& xPosition, int& yPosition, int& width,
	int& height) const
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports = 0;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	xPosition = viewports[0].TopLeftX;
	yPosition = mHeight - viewports[0].Height - viewports[0].TopLeftY;
	width = viewports[0].Width;
	height = viewports[0].Height;
}

void DirectRenderer::SetDepthRange(float zMin, float zMax)
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports = 0;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	zMin = viewports[0].MinDepth;
	zMax = viewports[0].MaxDepth;
}

void DirectRenderer::GetDepthRange(float& zMin, float& zMax) const
{
	D3D11_VIEWPORT* viewports = 0;
	UINT* numofViewports;
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->RSGetViewports(numofViewports, viewports);
	if (viewports == nullptr)
		MessageBoxA(0, "ERROR", "GetViewportError", MB_OK);
	zMin = viewports[0].MinDepth;
	zMax = viewports[0].MaxDepth;
}
void Hikari::DirectRenderer::Resize(int width, int height)
{
}
//// Support for clearing the color, depth, and stencil buffers.
void DirectRenderer::ClearBackBuffer()
{
	//FLOAT color[] = { 0,0,0,1 };
	//mData->mImmediateContext->ClearRenderTargetView(mData->g_pRenderTargetView, color);
}

void DirectRenderer::ClearDepthBuffer()
{
	//D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_DEPTH;
	//mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 1, 0);
}
void DirectRenderer::ClearStencilBuffer()
{
	/*D3D11_CLEAR_FLAG clearFlag = D3D11_CLEAR_STENCIL;
	mData->mImmediateContext->ClearDepthStencilView(mData->g_pDepthStencilView, clearFlag, 0, 0);*/
}
void DirectRenderer::ClearBuffers()
{
	ClearBackBuffer();
	
}
void Hikari::DirectRenderer::ClearDepthBuffer(int x, int y, int w, int h)
{
}
void Hikari::DirectRenderer::ClearStencilBuffer(int x, int y, int w, int h)
{
}
void Hikari::DirectRenderer::ClearBuffers(int x, int y, int w, int h)
{
}
void DirectRenderer::ClearBackBuffer(int x, int y, int w, int h)
{
	/*D3D11_RECT rect;
	rect.left = (long)x;
	rect.top = (long)y;

	rect.right = (long)(x + w - 1);
	rect.bottom = (long)(y + h - 1);

	FLOAT clearColor[] = { mClearColor[0],mClearColor[1],mClearColor[2],mClearColor[3] };
	(static_cast<DirectRenderData*>(mData))->mImmediateContext->ClearRenderTargetView((static_cast<DirectRenderData*>(mData))->g_pRenderTargetView, clearColor);*/

}
void Hikari::DirectRenderer::SetClearColor(const Float4 & color)
{
	mClearColor = color;
}
void Hikari::DirectRenderer::DisplayBackBuffer()
{
}
bool Hikari::DirectRenderer::PreDraw()
{
	return false;
}
void Hikari::DirectRenderer::PostDraw()
{
}
void Hikari::DirectRenderer::Initialize()
{
	HRESULT hr = S_OK;

	D3D_DRIVER_TYPE	g_driverType;
	D3D_FEATURE_LEVEL g_featureLevel;

	RECT rc;
	GetClientRect(mData->mHwnd, &rc);
	mWidth = rc.right - rc.left;
	mHeight = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = mWidth;
	sd.BufferDesc.Height = mHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mData->mHwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mData->g_pSwapChain, &mData->mDevice, &g_featureLevel, &mData->mImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	
	mData->renderTarget = CreateRenderTarget();


	hr = mData->g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mData->pBackBuffer);

	//hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	Texture::TextureFormat depthStencilTextureFormat(
		Texture::Components::DepthStencil,
		Texture::Type::UnsignedNormalized,
		1, 0, 0, 0, 0, 24, 8
	);
	Texture* depthStencilTexture = CreateTexture2D(mWidth, mHeight,
		1, depthStencilTextureFormat);

	Texture::TextureFormat colorTextureFormat(
		Texture::Components::RGBA,
		Texture::Type::UnsignedNormalized,
		1, 8, 8, 8, 8, 0, 0);
	Texture* colorTexture = CreateTexture2D(mWidth, mHeight, 1, colorTextureFormat);

	mData->renderTarget->AttachTexture(RenderTarget::AttachmentPoint::Color0, colorTexture);
	mData->renderTarget->AttachTexture(RenderTarget::AttachmentPoint::DepthStencil, depthStencilTexture);
}
void Hikari::DirectRenderer::Draw(const unsigned char * screenBuffer, bool reflectY)
{
}
void Hikari::DirectRenderer::Draw(int x, int y, const Float4 & color, const std::string & message)
{
}

const std::string & Hikari::DirectRenderer::GetDeviceName() const
{
	// TODO: 在此处插入 return 语句
	return "";
}

void Hikari::DirectRenderer::DestroyVertexBuffer(Buffer * buffer)
{
	DestroyBuffer(buffer);
}

void Hikari::DirectRenderer::DestroyBuffer(Buffer * buffer)
{
	BufferList::iterator iter = std::find(m_Buffer.begin(), m_Buffer.end(), buffer);
	if (iter != m_Buffer.end())
	{
		m_Buffer.erase(iter);
	}
}

void Hikari::DirectRenderer::DestroyIndexBuffer(Buffer * buffer)
{
	DestroyBuffer(buffer);
}

void Hikari::DirectRenderer::DestroyConstantBuffer(ConstantBuffer * buffer)
{
	DestroyBuffer(buffer);
}

void Hikari::DirectRenderer::DestroyStructuredBuffer(StructuredBuffer * buffer)
{
	DestroyBuffer(buffer);
}

void Hikari::DirectRenderer::DestroyRWBuffer(RWBuffer * buffer)
{
	DestroyBuffer(buffer);
}

Scene * Hikari::DirectRenderer::CreateScene()
{
	Scene* scene = new SceneDX11(this);

	m_Scene.push_back(scene);

	return scene;
}

Scene * Hikari::DirectRenderer::CreatePlane(float size, const AVector & N)
{
	float halfSize = size * 0.5f;
	Float3 p[4];
	// Crate the 4 points of the plane aligned to the X,Z plane.
	// Vertex winding is assuming a right-handed coordinate system 
	// (counter-clockwise winding order for front-facing polygons)
	p[0] = Float3(halfSize, 0, halfSize);
	p[1] = Float3(-halfSize, 0, halfSize);
	p[2] = Float3(-halfSize, 0, -halfSize);
	p[3] = Float3(halfSize, 0, -halfSize);

	// Rotate the plane vertices in the direction of the surface normal.
	Float4 rot = RotationFromTwoVectors(Float3(0, 1, 0), N);

	for (int i = 0; i < 4; i++)
	{
		//p[i] = rot * p[i];
	}

	// Now create the plane polygon from the transformed vertices.
	Scene* scene = CreateScene();

	std::stringstream ss;

	// Create a white diffuse material for the plane.
	// f red green blue Kd Ks Shine transmittance indexOfRefraction
	ss << "f 1 1 1 1 0 0 0 0" << std::endl;

	// Create a 4-point polygon
	ss << "p 4" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		ss << p[i][0] << " " << p[i][1] << " " << p[i][2] << std::endl;
	}

	if (scene->LoadFromString(ss.str(), "nff"))
	{
		return scene;
	}

	// An error occurred while loading the scene.
	DestroyScene(scene);
	return nullptr;
	return nullptr;
}

Scene * Hikari::DirectRenderer::CreateScreenQuad(float left, float right, float bottom, float top, float z)
{
	return nullptr;
}

Scene * Hikari::DirectRenderer::CreateSphere(float radius, float tesselation)
{
	return nullptr;
}

Scene * Hikari::DirectRenderer::CreateCube(float size)
{
	Scene* scene = CreateScene();
	std::stringstream ss;

	ss << "f 1 1 1 1 0 0 0 0" << std::endl;

	// hex x y z size
	ss << "dec 0 0 0 " << size;

	if (scene->LoadFromString(ss.str(), "nff"))
	{
		return scene;
	}

	// An error occurred while loading the scene.
	DestroyScene(scene);
	return nullptr;
}

void DirectRenderer::DrawPrimitive(const Visual * visual,VisualEffect* effect)
{
	RenderEventArgs eve(*this,0,0,0,mCamera);
	
	int index = 0;
	int count = effect->GetTechniqueSize();
	do
	{
		effect->GetTechnique(index++)->Render(eve);


	} while (index<count);
	
	mData->renderTarget->Bind();

	TextureDX11* colorBuffer = static_cast<TextureDX11*>(mData->renderTarget->GetTexture(RenderTarget::AttachmentPoint::Color0));
	if (colorBuffer)
	{
		mData->mImmediateContext->CopyResource(mData->pBackBuffer, colorBuffer->GetTextureResource());
	}
	mData->g_pSwapChain->Present(0, 0);
}

PipelineState* Hikari::DirectRenderer::CreatePipelineState()
{
	PipelineState* pPipeline = new PipelineStateDX11(mData->mDevice);
	m_Pipelines.push_back(pPipeline);

	return pPipeline;
}

void Hikari::DirectRenderer::DestoryPipelineState(PipelineState* pipeline)
{
	PipelineList::iterator iter = std::find(m_Pipelines.begin(), m_Pipelines.end(), pipeline);
	if (iter != m_Pipelines.end())
	{
		m_Pipelines.erase(iter);
	}
}

Buffer * Hikari::DirectRenderer::CreateFloatVertexBuffer(const float * data, unsigned int count, unsigned int stride)
{
	Buffer* buffer = new BufferDx(this, D3D11_BIND_VERTEX_BUFFER, data, count, stride);
	m_Buffer.push_back(buffer);
	return buffer;
}

Buffer * Hikari::DirectRenderer::CreateDoubleVertexBuffer(const double * data, unsigned int count, unsigned int stride)
{
	Buffer* buffer = new BufferDx(this, D3D11_BIND_VERTEX_BUFFER, data, count, stride);
	m_Buffer.push_back(buffer);
	return buffer;
}

Buffer * Hikari::DirectRenderer::CreateUINTVertexBuffer(const UINT * data, unsigned int count, unsigned int stride)
{
	Buffer* buffer = new BufferDx(this, D3D11_BIND_VERTEX_BUFFER, data, count, (UINT)sizeof(unsigned int));
	m_Buffer.push_back(buffer);
	return buffer;
}

Buffer * Hikari::DirectRenderer::CreateUIntIndexBuffer(const unsigned int * data, unsigned int sizeInBytes)
{
	Buffer* buffer = new BufferDx(this, D3D11_BIND_INDEX_BUFFER, data, sizeInBytes, (UINT)sizeof(unsigned int));
	m_Buffer.push_back(buffer);
	return buffer;
}

ConstantBuffer * Hikari::DirectRenderer::CreateConstantBuffer(const void * data, size_t size)
{
	ConstantBuffer* buffer = new ConstantBufferDX11(this->mData->mDevice, size);
	if (data)
		buffer->Set(data, size);
	m_Buffer.push_back(buffer);
	return buffer;
}


StructuredBuffer * Hikari::DirectRenderer::CreateStructuredBuffer(void * data, unsigned int count, unsigned int stride, CPUAccess cpuAccess,  bool bSRV, bool bUAV, bool appendFlag)
{
	StructuredBuffer* buffer = new StructuredBufferDX11(mData->mDevice, 0, data, count, stride, cpuAccess, bSRV, bUAV,appendFlag);
	m_Buffer.push_back(buffer);
	return buffer;
}

RWBuffer * Hikari::DirectRenderer::CreateRWBuffer(void * data, unsigned int count, unsigned int stride, CPUAccess cpuAccess)
{
	RWBuffer* buffer = new RWBufferDX11(mData->mDevice, 0, data, count, stride);
	m_Buffer.push_back(buffer);

	return buffer;
}

void Hikari::DirectRenderer::LoadDefaultResources()
{

	Shader* pDefaultVertexShader = CreateShader();
	std::ifstream ins("DefaultShader.hlsl");
	long length = ins.tellg();
	ins.seekg(0, std::ios::end);
	long m = ins.tellg();
	char* buffer = new char[m];
	ins.seekg(0, std::ios::beg);
	ins.read(buffer, m);
	ins.close();
	
	std::string Filebyte(buffer);
	pDefaultVertexShader->LoadShaderFromString(Shader::VertexShader, Filebyte, "DefaultShader.hlsl", Shader::ShaderMacros(), "VS_main", "vs_4_0");

	Shader* pDefaultPixelShader = CreateShader();
	pDefaultPixelShader->LoadShaderFromString(Shader::PixelShader, Filebyte, "DefaultShader.hlsl", Shader::ShaderMacros(), "PS_main", "ps_4_0");

	// Create a magenta texture if a texture defined in the shader is not bound.
	m_pDefaultTextures = CreateTexture2D(1, 1, 1, Texture::TextureFormat());
	m_pDefaultTextures->Clear(ClearFlags::Color, Float4(1, 0, 1, 1));

	m_pDefaultPipeline = CreatePipelineState();

	m_pDefaultPipeline->SetShader(Shader::VertexShader, pDefaultVertexShader);
	m_pDefaultPipeline->SetShader(Shader::PixelShader, pDefaultPixelShader);
	// TODO: Default pipeline state must be assigned to a renderwindow
	// because the RenderWindow has a default render target that must be bound to the pipeline.

}

Scene * Hikari::DirectRenderer::CreateAxis(float radius, float length)
{
	return nullptr;
}

void Hikari::DirectRenderer::DestroyScene(Scene * scene)
{
	SceneList::iterator iter = std::find(m_Scene.begin(), m_Scene.end(), scene);
	if (iter != m_Scene.end())
	{
		m_Scene.erase(iter);
	}
}

Mesh * Hikari::DirectRenderer::CreateMesh()
{
	Mesh* mesh = new MeshDx(this);
	m_Meshes.push_back(mesh);
	return mesh;
}

void Hikari::DirectRenderer::DestroyMesh(Mesh * mesh)
{
	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
	if (iter != m_Meshes.end())
	{
		m_Meshes.erase(iter);
	}
}

Shader * Hikari::DirectRenderer::CreateShader()
{
	Shader* shader = new ShaderDx(this);
	m_Shaders.push_back(shader);
	return shader;
}

void Hikari::DirectRenderer::DestroyShader(Shader * shader)
{
	ShaderList::iterator iter = std::find(m_Shaders.begin(), m_Shaders.end(), shader);
	if (iter != m_Shaders.end())
	{
		m_Shaders.erase(iter);
	}
}
Texture * Hikari::DirectRenderer::CreateTexture(const std::wstring & fileName)
{
	TextureMap::iterator iter = m_TextureByName.find(fileName);
	if (iter != m_TextureByName.end())
	{
		return iter->second;
	}

	Texture* texture = new TextureDX11(mData->mDevice);


	texture->LoadTexture2D(fileName);

	m_Texture.push_back(texture);
	m_TextureByName.insert(TextureMap::value_type(fileName, texture));
	return texture;
}

Texture * Hikari::DirectRenderer::CreateTextureCube(const std::wstring & fileName)
{
	TextureMap::iterator iter = m_TextureByName.find(fileName);
	if (iter != m_TextureByName.end())
	{
		return iter->second;
	}

	Texture* texture =new TextureDX11(mData->mDevice);


	texture->LoadTextureCube(fileName);

	m_Texture.push_back(texture);
	m_TextureByName.insert(TextureMap::value_type(fileName, texture));

	return texture;
}

Texture * Hikari::DirectRenderer::CreateTexture1D(uint16_t width, uint16_t slices, const Texture::TextureFormat & format, CPUAccess cpuAccess, bool gpuWrite)
{
	Texture* texture = new TextureDX11(mData->mDevice, width, slices, format, cpuAccess, gpuWrite);
	m_Texture.push_back(texture);

	return texture;
}

Texture * Hikari::DirectRenderer::CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices, const Texture::TextureFormat & format, CPUAccess cpuAccess, bool gpuWrite)
{
	Texture* texture = new TextureDX11(mData->mDevice, width, height, slices, format, cpuAccess, gpuWrite);
	m_Texture.push_back(texture);

	return texture;
}

Texture * Hikari::DirectRenderer::CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth, const Texture::TextureFormat & format, CPUAccess cpuAccess, bool gpuWrite)
{
	Texture* texture = new TextureDX11(TextureDX11::Tex3d, mData->mDevice, width, height, depth, format, cpuAccess, gpuWrite);
	m_Texture.push_back(texture);

	return texture;
}

Texture * Hikari::DirectRenderer::CreateTextureCube(uint16_t size, uint16_t numCubes, const Texture::TextureFormat & format, CPUAccess cpuAccess, bool gpuWrite)
{
	Texture* texture = new TextureDX11(TextureDX11::Cube, mData->mDevice, size, numCubes, format, cpuAccess, gpuWrite);
	m_Texture.push_back(texture);

	return texture;
}

Texture * Hikari::DirectRenderer::CreateTexture()
{
	Texture* texture = new TextureDX11(mData->mDevice);
	m_Texture.push_back(texture);

	return texture;
}

Texture * Hikari::DirectRenderer::GetDefaultTexture() const
{
	return m_pDefaultTextures;
}

void Hikari::DirectRenderer::DestroyTexture(Texture * texture)
{
	TextureList::iterator iter = std::find(m_Texture.begin(), m_Texture.end(), texture);
	if (iter != m_Texture.end())
	{
		m_Texture.erase(iter);
	}

	TextureMap::iterator iter2 = std::find_if(m_TextureByName.begin(), m_TextureByName.end(), [=](TextureMap::value_type val) { return (val.second == texture); });
	if (iter2 != m_TextureByName.end())
	{
		m_TextureByName.erase(iter2);
	}
}

RenderTarget * Hikari::DirectRenderer::CreateRenderTarget()
{
	RenderTargetDX11* renderTarget =  new RenderTargetDX11(mData->mDevice);
	m_RenderTargets.push_back(renderTarget);

	return renderTarget;
}

void Hikari::DirectRenderer::DestroyRenderTarget(RenderTarget * renderTarget)
{
	RenderTargetList::iterator iter = std::find(m_RenderTargets.begin(), m_RenderTargets.end(), renderTarget);
	if (iter != m_RenderTargets.end())
	{
		m_RenderTargets.erase(iter);
	}
}

SamplerState * Hikari::DirectRenderer::CreateSamplerState()
{
	SamplerState* sampler = new SamplerStateDX11(mData->mDevice);
	m_Samplers.push_back(sampler);

	return sampler;
}

void Hikari::DirectRenderer::DestroySampler(SamplerState * sampler)
{
	SamplerList::iterator iter = std::find(m_Samplers.begin(), m_Samplers.end(), sampler);
	if (iter != m_Samplers.end())
	{
		m_Samplers.erase(iter);
	}
}

Material * Hikari::DirectRenderer::CreateMaterial()
{
	Material* pMaterial = new Material(this);
	m_Materials.push_back(pMaterial);
	return pMaterial;
}

void Hikari::DirectRenderer::DestroyMaterial(Material * material)
{
	MaterialList::iterator iter = std::find(m_Materials.begin(), m_Materials.end(), material);
	if (iter != m_Materials.end())
	{
		m_Materials.erase(iter);
	}
}

Scene * Hikari::DirectRenderer::CreateCylinder(float baseRadius, float apexRadius, float height, const AVector & axis)
{
	return nullptr;
}

Scene * Hikari::DirectRenderer::CreateCone(float baseRadius, float height)
{
	return nullptr;
}

Scene * Hikari::DirectRenderer::CreateArrow(const AVector & tail, const AVector & head, float radius)
{
	return nullptr;
}
