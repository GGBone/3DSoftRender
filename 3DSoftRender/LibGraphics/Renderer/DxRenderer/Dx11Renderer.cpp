#include "GraphicsPCH.h"
#include "Dx11Renderer.h"
#include "Dx11Buffer.h"
#include "Dx11StructureBuffer.h"
#include "Dx11SamplerState.h"
#include "Dx11Scene.h"
#include "Dx11PipelineState.h"
#include "Dx11ConstantBuffer.h"
#include "Dx11Buffer.h"
#include "Dx11Mesh.h"
#include "Dx11RenderTarget.h"
#include "Dx11Query.h"
#include "Dx11VertexIndexBuffer.h"
#include <sstream>
#include "WindowApplicationBase.h"
#include "Base/Float3.h"
#include "SceneGraph/Material.h"
#include "Dx11Texture.h"

namespace Hikari
{
	class ShaderDx;

	inline Float4 RotationFromTwoVectors(const AVector& u, const AVector& v)
	{
		float normUV = sqrtf(u.Dot(u)) * (v.Dot(v));
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

		return Float4(real, vec.X(), vec.Y(), vec.Z());
	}


	void DirectRenderer::CreateDevice(HINSTANCE hInstance)
	{
		HRESULT hr = S_OK;

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

		D3D_FEATURE_LEVEL featureLevel;
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pDeviceContext;
		hr = D3D11CreateDevice(nullptr, driverTypes[0], nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
		                       D3D11_SDK_VERSION, &pDevice, &featureLevel, &pDeviceContext);

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			hr = D3D11CreateDevice(nullptr, driverTypes[driverTypeIndex], nullptr, createDeviceFlags, featureLevels,
			                       numFeatureLevels,
			                       D3D11_SDK_VERSION, &pDevice, &featureLevel, &pDeviceContext);
			if (SUCCEEDED(hr))
				break;
		}
		if (FAILED(hr))
		{
			ReportError("Failed to create device");
			return;
		}
		if (FAILED(pDevice->QueryInterface<ID3D11Device2>(&m_pDevice)))
		{
			ReportError("Failed to create device2");
			return;
		}
		m_pDevice->GetImmediateContext2(&m_pDeviceContext);

		if (SUCCEEDED(m_pDevice->QueryInterface<ID3D11Debug>(&m_pDebugLayer)))
		{
			ID3D11InfoQueue* d3dInfoQueue;
			if (SUCCEEDED(m_pDebugLayer->QueryInterface<ID3D11InfoQueue>(&d3dInfoQueue)))
			{
#if _DEBUG
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, TRUE);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, TRUE);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, TRUE);
				D3D11_MESSAGE_ID hide[] =
				{
					D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
				};
				D3D11_INFO_QUEUE_FILTER filter;

				memset(&filter, 0, sizeof(filter));
				filter.DenyList.NumIDs = _countof(hide);
				filter.DenyList.pIDList = hide;
				d3dInfoQueue->AddStorageFilterEntries(&filter);

#endif
			}
		}
		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		DXGI_ADAPTER_DESC adapterDescription = {};

		if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
		{
			ReportError("Failed to create factory");
		}
		if (FAILED(factory->EnumAdapters(0,&adapter)))
		{
			ReportError("Failed to create adapter");
		}
		if (FAILED(adapter->GetDesc(&adapterDescription)))
		{
			ReportError("Failed to create adapter description");
		}

		m_DeviceName = ConvertString(adapterDescription.Description);
	}


	DirectRenderer::DirectRenderer(WindowApplicationBase& application)
	{
		CreateDevice(application.GetModuleHandle());
		application.mInitialize += boost::bind(&DirectRenderer::OnInitialize, this, _1);
	}

	DirectRenderer::~DirectRenderer()
	{
		m_Materials.clear();
		m_Scenes.clear();
		m_Meshes.clear();
		m_Buffers.clear();
		m_Shaders.clear();
		m_Textures.clear();
		m_Samplers.clear();
		m_Pipelines.clear();
		m_Queries.clear();

#if defined(_DEBUG)
		if (m_pDebugLayer)
			m_pDebugLayer->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
#endif
	}

	void DirectRenderer::OnInitialize(EventArgs& e)
	{
	}

	void DirectRenderer::OnLoadingProgress(ProgressEventArgs& e)
	{
		Renderer::OnLoadingProgress(e);
	}

	const std::string& DirectRenderer::get_device_name() const
	{
		return m_DeviceName;
	}

	ID3D11Device2* DirectRenderer::GetDevice() const
	{
		return m_pDevice;
	}

	ID3D11DeviceContext2* DirectRenderer::GetDeviceContext() const
	{
		return m_pDeviceContext;
	}

	void DirectRenderer::DestroyVertexBuffer(std::shared_ptr<VertexIndexBuffer> buffer)
	{
		DestroyBuffer(buffer);
	}

	void DirectRenderer::DestroyBuffer(std::shared_ptr<BufferBase> buffer)
	{
		BufferList::iterator iter = std::find(m_Buffers.begin(), m_Buffers.end(), buffer);
		if (iter != m_Buffers.end())
		{
			m_Buffers.erase(iter);
		}
	}

	void DirectRenderer::DestroyIndexBuffer(std::shared_ptr<VertexIndexBuffer> buffer)
	{
		DestroyBuffer(buffer);
	}

	void DirectRenderer::destroy_constant_buffer(std::shared_ptr<ConstantBuffer> buffer)
	{
		DestroyBuffer(buffer);
	}

	void DirectRenderer::DestroyStructuredBuffer(std::shared_ptr<StructuredBuffer> buffer)
	{
		DestroyBuffer(buffer);
	}

	void DirectRenderer::DestroyBuffer(std::shared_ptr<Buffer> buffer)
	{
		DestroyBuffer(buffer);
	}

	std::shared_ptr<Scene> DirectRenderer::CreateScene()
	{
		auto scene = std::make_shared<SceneDX11>(shared_from_this());
		scene->LoadingProgress += boost::bind(&DirectRenderer::OnLoadingProgress, this, _1);
		m_Scenes.push_back(scene);

		return scene;
	}

	std::shared_ptr<Scene> DirectRenderer::CreatePlane(float size, const AVector& N)
	{
		auto halfSize = size * 0.5f;
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

		if (N[0] == 0.0f && N[1] == 0.0f && N[2] == 1.0f)
		{
			p[0] = Float3(halfSize, halfSize, 0);
			p[1] = Float3(-halfSize, halfSize, 0);
			p[2] = Float3(-halfSize, -halfSize, 0);
			p[3] = Float3(halfSize, -halfSize, 0);
		}
		/*for (int i = 0; i < 4; i++)
		{
			p[i] = rot * p[i];
		}*/

		// Now create the plane polygon from the transformed vertices.
		std::shared_ptr<Scene> scene = CreateScene();

		std::stringstream ss;

		// Create a white diffuse material for the plane.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 1 1 0 1 0 0 0 0" << std::endl;

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
	}

	std::shared_ptr<Scene> DirectRenderer::CreateScreenQuad(float left, float right, float bottom, float top, float z)
	{
		return nullptr;
	}

	std::shared_ptr<Scene> DirectRenderer::CreateSphere(float radius, float tesselation)
	{
		std::shared_ptr<Scene> scene = CreateScene();
		std::stringstream ss;
		ss << "f 1 1 1 1 0 0 0.5 0" << std::endl;
		ss << "tess" << tesselation << std::endl;

		ss << "s 0 0 0" << radius << std::endl;

		if (scene->LoadFromString(ss.str(), "nff"))
		{
			return scene;
		}

		// An error occurred while loading the scene.
		DestroyScene(scene);
		return nullptr;
	}

	std::shared_ptr<Scene> DirectRenderer::CreateCube(float size)
	{
		std::shared_ptr<Scene> scene = CreateScene();
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

	std::shared_ptr<PipelineState> DirectRenderer::CreatePipelineState()
	{
		std::shared_ptr<PipelineState> pPipeline = std::make_shared<PipelineStateDX11>(m_pDevice);
		m_Pipelines.push_back(pPipeline);

		return pPipeline;
	}

	void DirectRenderer::DestoryPipelineState(std::shared_ptr<PipelineState> pipeline)
	{
		const auto iter = std::find(m_Pipelines.begin(), m_Pipelines.end(), pipeline);
		if (iter != m_Pipelines.end())
		{
			m_Pipelines.erase(iter);
		}
	}


	std::shared_ptr<VertexIndexBuffer> DirectRenderer::CreateFloatVertexBuffer(
		const float* data, unsigned int count, unsigned int stride)
	{
		auto buffer = std::make_shared<VertexIndexBufferDx11>(shared_from_this(), D3D11_BIND_VERTEX_BUFFER, data, count,
		                                                      stride);
		m_Buffers.push_back(buffer);
		return buffer;
	}

	std::shared_ptr<VertexIndexBuffer> DirectRenderer::CreateDoubleVertexBuffer(
		const double* data, unsigned int count, unsigned int stride)
	{
		auto buffer = std::make_shared<VertexIndexBufferDx11>(shared_from_this(), D3D11_BIND_VERTEX_BUFFER, data, count,
		                                                      stride);
		m_Buffers.push_back(buffer);
		return buffer;
	}

	std::shared_ptr<VertexIndexBuffer> DirectRenderer::CreateUINTVertexBuffer(
		const UINT* data, unsigned int count, unsigned int stride)
	{
		auto buffer = std::make_shared<VertexIndexBufferDx11>(shared_from_this(), D3D11_BIND_VERTEX_BUFFER, data, count,
		                                                      (UINT)sizeof(unsigned int));
		m_Buffers.push_back(buffer);
		return buffer;
	}

	std::shared_ptr<VertexIndexBuffer> DirectRenderer::CreateUIntIndexBuffer(
		const unsigned int* data, unsigned int sizeInBytes)
	{
		auto buffer = std::make_shared<VertexIndexBufferDx11>(shared_from_this(), D3D11_BIND_INDEX_BUFFER, data,
		                                                      sizeInBytes, (UINT)sizeof(unsigned int));
		m_Buffers.push_back(buffer);
		return buffer;
	}

	std::shared_ptr<ConstantBuffer> DirectRenderer::CreateConstantBuffer(const void* data, size_t size)
	{
		std::shared_ptr<ConstantBuffer> buffer = std::make_shared<ConstantBufferDX11>(m_pDevice, size);
		if (data)
			buffer->set(data, size);
		m_Buffers.push_back(buffer);
		return buffer;
	}


	std::shared_ptr<StructuredBuffer> DirectRenderer::CreateStructuredBuffer(
		const void* data, unsigned int count, unsigned int stride, ShaderParameter::ShaderInputParameter param)
	{
		std::shared_ptr<StructuredBuffer> buffer = std::make_shared<StructuredBufferDX11>(
			m_pDevice, data, count, stride, param);
		m_Buffers.push_back(buffer);
		return buffer;
	}

	std::shared_ptr<Buffer> DirectRenderer::CreateBuffer(const void* data, unsigned int count, unsigned int stride,
	                                                     ShaderParameter::ShaderInputParameter param)
	{
		std::shared_ptr<Buffer> buffer = std::make_shared<BufferDX11>(shared_from_this(), data, count, stride, param);
		m_Buffers.push_back(buffer);

		return buffer;
	}

	std::shared_ptr<Query> DirectRenderer::CreateQuery(Query::QueryType queryType, uint8_t numBuffers)
	{
		std::shared_ptr<Query> query = std::make_shared<QueryDX11>(m_pDevice, queryType, numBuffers);
		m_Queries.push_back(query);

		return query;
	}

	void DirectRenderer::LoadDefaultResources()
	{
		std::shared_ptr<Shader> pDefaultVertexShader = CreateShader();
		std::ifstream ins("DefaultShader.hlsl");
		std::streamoff length = ins.tellg();
		ins.seekg(0, std::ios::end);
		std::streamoff m = ins.tellg();
		char* buffer = new char[m];
		ins.seekg(0, std::ios::beg);
		ins.read(buffer, m);
		ins.close();

		std::string Filebyte(buffer);
		pDefaultVertexShader->LoadShaderFromString(Shader::VertexShader, Filebyte, "DefaultShader.hlsl",
		                                           Shader::ShaderMacros(), "VS_main", "vs_4_0");

		std::shared_ptr<Shader> pDefaultPixelShader = CreateShader();
		pDefaultPixelShader->LoadShaderFromString(Shader::PixelShader, Filebyte, "DefaultShader.hlsl",
		                                          Shader::ShaderMacros(), "PS_main", "ps_4_0");

		// Create a magenta texture if a texture defined in the shader is not bound.
		m_pDefaultTextures = CreateTexture2D(1, 1, 1, Texture::TextureFormat());
		m_pDefaultTextures->Clear(ClearFlags::Color, Float4(1, 0, 1, 1));

		m_pDefaultPipeline = CreatePipelineState();

		m_pDefaultPipeline->SetShader(Shader::VertexShader, pDefaultVertexShader);
		m_pDefaultPipeline->SetShader(Shader::PixelShader, pDefaultPixelShader);
		// TODO: Default pipeline state must be assigned to a renderwindow
		// because the RenderWindow has a default render target that must be bound to the pipeline.
	}

	std::shared_ptr<Scene> DirectRenderer::CreateAxis(float radius, float length)
	{
		std::shared_ptr<Scene> scene = CreateScene();
		std::stringstream ss;

		// Create a red material for the +X axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 1 0 0 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the +X axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << length << " 0 0 " << radius << std::endl;

		// Create a cone for the +X axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << length << " 0 0 " << radius * 2.0f << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << length * 1.5f << " 0 0 0" << std::endl;

		// Create a green material for the +Y axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 0 1 0 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the +Y axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 " << length << " 0 " << radius << std::endl;

		// Create a cone for the +Y axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 " << length << " 0 " << radius * 2.0f << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 " << length * 1.5f << " 0 0" << std::endl;

		// Create a blue material for the +Z axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 0 0 1 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the +Z axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 0 " << length << " " << radius << std::endl;

		// Create a cone for the +Z axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 " << length << " " << radius * 2.0f << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 0 " << length * 1.5f << " 0" << std::endl;

		// Create a cyan material for the -X axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 0 1 1 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the -X axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << -length << " 0 0 " << radius << std::endl;

		// Create a cone for the -X axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << -length << " 0 0 " << radius * 2.0f << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << -length * 1.5f << " 0 0 0" << std::endl;

		// Create a yellow material for the -Y axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 1 0 1 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the -Y axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 " << -length << " 0 " << radius << std::endl;

		// Create a cone for the -Y axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 " << -length << " 0 0" << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 " << -length * 1.5f << " 0 " << radius * 2.0f << std::endl;

		// Create a magenta material for the -Z axis.
		// f red green blue Kd Ks Shine transmittance indexOfRefraction
		ss << "f 1 1 0 1 0 0 0 0" << std::endl;

		// Create a cylinder aligned to the -Z axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << radius << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 0 " << -length << " " << radius << std::endl;

		// Create a cone for the -Z axis.
		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 " << -length << " " << radius * 2.0f << std::endl;
		// apex.x apex.y apex.z apexRadius
		ss << "0 0 " << -length * 1.5f << " 0" << std::endl;

		if (scene->LoadFromString(ss.str(), "nff"))
		{
			return scene;
		}

		// An error occurred while loading the scene.
		DestroyScene(scene);
		return nullptr;
	}

	void DirectRenderer::DestroyScene(std::shared_ptr<Scene> scene)
	{
		const auto iter = std::find(m_Scenes.begin(), m_Scenes.end(), scene);
		if (iter != m_Scenes.end())
		{
			m_Scenes.erase(iter);
		}
	}

	std::shared_ptr<Mesh> DirectRenderer::CreateMesh()
	{
		const auto mesh = std::make_shared<MeshDx>(shared_from_this());
		m_Meshes.push_back(mesh);
		return mesh;
	}

	void DirectRenderer::DestroyMesh(std::shared_ptr<Mesh> mesh)
	{
		auto iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
		if (iter != m_Meshes.end())
		{
			m_Meshes.erase(iter);
		}
	}

	shared_ptr<ShaderDx> DirectRenderer::CreateShader()
	{
		auto shader = std::make_shared<ShaderDx>(shared_from_this());

		return shader;
	}

	void DirectRenderer::DestroyShader(std::shared_ptr<Shader> shader)
	{
		const auto iter = std::find(m_Shaders.begin(), m_Shaders.end(), shader);
		if (iter != m_Shaders.end())
		{
			m_Shaders.erase(iter);
		}
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTexture(const std::wstring& fileName)
	{
		const auto iter = m_TextureByName.find(fileName);
		if (iter != m_TextureByName.end())
		{
			return iter->second;
		}

		std::shared_ptr<Texture> texture = std::make_shared<TextureDX11>(m_pDevice);


		texture->LoadTexture2D(fileName);

		m_Textures.push_back(texture);
		m_TextureByName.insert(TextureMap::value_type(fileName, texture));
		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTextureCube(const std::wstring& fileName)
	{
		const auto iter = m_TextureByName.find(fileName);
		if (iter != m_TextureByName.end())
		{
			return iter->second;
		}

		std::shared_ptr<Texture> texture = std::make_shared<TextureDX11>(m_pDevice);


		texture->LoadTextureCube(fileName);

		m_Textures.push_back(texture);
		m_TextureByName.insert(TextureMap::value_type(fileName, texture));

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTexture1D(uint16_t width, uint16_t slices,
	                                                         const Texture::TextureFormat& format,
	                                                         ShaderParameter::ShaderInputParameter param_)
	{
		const auto texture = std::make_shared<TextureDX11>(m_pDevice, width, slices, format, param_);
		m_Textures.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTexture2D(uint16_t width, uint16_t height, uint16_t slices,
	                                                         const Texture::TextureFormat& format,
	                                                         ShaderParameter::ShaderInputParameter param_)
	{
		const auto texture = std::make_shared<TextureDX11>(m_pDevice, width, height, slices, format, param_);
		m_Textures.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTexture3D(uint16_t width, uint16_t height, uint16_t depth,
	                                                         const Texture::TextureFormat& format,
	                                                         ShaderParameter::ShaderInputParameter param_)
	{
		const auto texture = std::make_shared<TextureDX11>(TextureDX11::Tex3d, m_pDevice, width, height, depth, format,
		                                                   param_);
		m_Textures.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTextureCube(uint16_t size, uint16_t numCubes,
	                                                           const Texture::TextureFormat& format,
	                                                           ShaderParameter::ShaderInputParameter param_)
	{
		const auto texture = std::make_shared<TextureDX11
		>(TextureDX11::Cube, m_pDevice, size, numCubes, format, param_);
		m_Textures.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::CreateTexture()
	{
		const auto texture = std::make_shared<TextureDX11>(m_pDevice);
		m_Textures.push_back(texture);

		return texture;
	}

	std::shared_ptr<Texture> DirectRenderer::GetDefaultTexture() const
	{
		return m_pDefaultTextures;
	}

	void DirectRenderer::DestroyTexture(std::shared_ptr<Texture> texture)
	{
		const auto iter = std::find(m_Textures.begin(), m_Textures.end(), texture);
		if (iter != m_Textures.end())
		{
			m_Textures.erase(iter);
		}

		TextureMap::iterator iter2 = std::find_if(m_TextureByName.begin(), m_TextureByName.end(),
		                                          [=](TextureMap::value_type val) { return (val.second == texture); });
		if (iter2 != m_TextureByName.end())
		{
			m_TextureByName.erase(iter2);
		}
	}

	std::shared_ptr<RenderTarget> DirectRenderer::CreateRenderTarget()
	{
		const auto renderTarget = std::make_shared<RenderTargetDX11>(m_pDevice);
		m_RenderTargets.push_back(renderTarget);

		return renderTarget;
	}

	void DirectRenderer::DestroyRenderTarget(std::shared_ptr<RenderTarget> renderTarget)
	{
		const auto iter = std::find(m_RenderTargets.begin(), m_RenderTargets.end(), renderTarget);
		if (iter != m_RenderTargets.end())
		{
			m_RenderTargets.erase(iter);
		}
	}

	std::shared_ptr<SamplerState> DirectRenderer::CreateSamplerState()
	{
		const auto sampler = std::make_shared<SamplerStateDX11>(m_pDevice);
		m_Samplers.push_back(sampler);

		return sampler;
	}

	void DirectRenderer::DestroySampler(std::shared_ptr<SamplerState> sampler)
	{
		const auto iter = std::find(m_Samplers.begin(), m_Samplers.end(), sampler);
		if (iter != m_Samplers.end())
		{
			m_Samplers.erase(iter);
		}
	}

	std::shared_ptr<Material> DirectRenderer::CreateMaterial()
	{
		const auto pMaterial = std::make_shared<Material>(shared_from_this());
		m_Materials.push_back(pMaterial);
		return pMaterial;
	}

	void DirectRenderer::DestroyMaterial(std::shared_ptr<Material> material)
	{
		const auto iter = std::find(m_Materials.begin(), m_Materials.end(), material);
		if (iter != m_Materials.end())
		{
			m_Materials.erase(iter);
		}
	}

	std::shared_ptr<Scene> DirectRenderer::CreateCylinder(float baseRadius, float apexRadius, float height,
	                                                      const AVector& axis)
	{
		const auto scene = CreateScene();
		std::stringstream ss;
		ss << "f 1 1 1 1 0 0 0 0" << std::endl;

		ss << "c" << std::endl;
		// base.x base.y base.z baseRadius
		ss << "0 0 0 " << baseRadius << std::endl;

		auto apex = axis * height;
		// apex.x apex.y apex.z apexRadius
		ss << apex.X() << " " << apex.Y() << " " << apex.Z() << " " << apexRadius << std::endl;
		if (scene->LoadFromString(ss.str(), "nff"))
		{
			return scene;
		}
		DestroyScene(scene);
		return nullptr;
	}

	std::shared_ptr<Scene> DirectRenderer::CreateCone(float baseRadius, float height)
	{
		return nullptr;
	}

	std::shared_ptr<Scene> DirectRenderer::CreateArrow(const AVector& tail, const AVector& head, float radius)
	{
		return nullptr;
	}
}
