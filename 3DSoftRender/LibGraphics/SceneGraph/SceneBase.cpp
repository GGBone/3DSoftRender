#include "GraphicsPCH.h"
#define ENABLE_BOOST
#define ENABLE_ASSIMP
#include "SceneBase.h"
#include <assimp/ProgressHandler.hpp>
#include "Algebra/HMatrix.h"
#include "Node.h"
#include "Material.h"
#include "Mesh.h"
#include <d3d11.h>
#include "SimpleMath.h"
using namespace SimpleMath;
#define EXPORT_FORMAT "assbin"
#define EXPORT_EXTENSION "assbin"

using namespace Hikari;

class ProgressHandler : public Assimp::ProgressHandler
{
public:
	ProgressHandler(SceneBase& scene, const std::wstring& filename)
		: m_Scene(scene),
		  m_Filename(filename)
	{
	}

	bool Update(float percentage) override
	{
		ProgressEventArgs progessEventArgs(m_Scene, m_Filename, percentage);
		m_Scene.OnLoadingProgress(progessEventArgs);
		return !progessEventArgs.Cancel;
	}

private:
	SceneBase& m_Scene;
	std::wstring m_Filename;
};

bool SceneBase::LoadFromFile(const std::wstring& fileName)
{
	fs::path filePath(fileName);
	fs::path parentPath;
	m_SceneFile = fileName;

	if (filePath.has_parent_path())
	{
		parentPath = filePath.parent_path();
	}
	else
	{
		parentPath = fs::current_path();
	}
	const aiScene* scene;
	Assimp::Importer importer;

	importer.SetProgressHandler(new ProgressHandler(*this, fileName));

	fs::path exportPath = filePath;

	if (exists(exportPath) && is_regular_file(exportPath))
	{
		scene = importer.ReadFile(exportPath.string(), 0);
	}
	else
	{
		importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0f);
		importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);

		unsigned int preprocessFlags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_OptimizeGraph | aiProcess_FlipWindingOrder;
		scene = importer.ReadFile(filePath.string(), preprocessFlags);


		if (scene)
		{
			// Now export the preprocessed scene so we can load it faster next time.
			Assimp::Exporter exporter;
			exporter.Export(scene, EXPORT_FORMAT, exportPath.string(), preprocessFlags);
		}
	}


	if (!scene)
	{
		ReportError(importer.GetErrorString());
		return false;
	}
	// If we have a previously loaded scene, delete it.
	HMatrix localTransform(false);
	if (m_pRootNode)
	{
		// Save the root nodes local transform
		// so it can be restored on reload.
		localTransform = m_pRootNode->GetLocalTransform();
		m_pRootNode = nullptr;
	}
	// Delete the previously loaded assets.
	m_MaterialMap.clear();
	m_Materials.clear();
	m_Meshes.clear();

	// Import scene materials.
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
	{
		ImportMaterial(*scene->mMaterials[i], parentPath);
	}
	// Import meshes
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		ImportMesh(*scene->mMeshes[i]);
	}

	m_pRootNode = ImportSceneNode(m_pRootNode, scene->mRootNode);
	m_pRootNode->SetLocalTransform(localTransform);

	return true;
}

bool SceneBase::LoadFromString(const std::string& sceneStr, const std::string& format)
{
	Assimp::Importer importer;
	const aiScene* scene = nullptr;

	importer.SetProgressHandler(new ProgressHandler(*this, L"String"));

	importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0f);
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);

	unsigned int preprocessFlags = aiProcess_OptimizeMeshes | aiProcess_MakeLeftHanded;

	scene = importer.ReadFileFromMemory(sceneStr.data(), sceneStr.size(), preprocessFlags, format.c_str());

	if (!scene)
	{
		//ReportError(importer.GetErrorString());
		return false;
	}
	// If we have a previously loaded scene, delete it.
	if (m_pRootNode)
	{
		m_pRootNode = nullptr;
	}

	// Import scene materials.
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
	{
		ImportMaterial(*scene->mMaterials[i], fs::current_path());
	}
	// Import meshes
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		ImportMesh(*scene->mMeshes[i]);
	}

	m_pRootNode = ImportSceneNode(m_pRootNode, scene->mRootNode);

	return true;
}

void SceneBase::Render(RenderEventArgs& renderArgs)
{
	if (m_pRootNode)
	{
		m_pRootNode->Render(renderArgs);
	}
}

std::shared_ptr<Node> SceneBase::GetRootNode()
{
	return m_pRootNode;
}

void SceneBase::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
	if (m_pRootNode)
		m_pRootNode->Accept(visitor);
}

void SceneBase::OnLoadingProgress(ProgressEventArgs& e)
{
	base::OnLoadingProgress(e);
}


SceneBase::~SceneBase()
{
}

void SceneBase::ImportMaterial(const aiMaterial& material, fs::path parentPath)
{
	aiString materialName;
	aiString aiTexturePath;
	aiTextureOp aiBlendOperation;
	float blendFactor;
	aiColor4D diffuseColor;
	aiColor4D specularColor;
	aiColor4D ambientColor;
	aiColor4D emissiveColor;
	float opacity;
	float indexOfRefraction;
	float reflectivity;
	float shininess;
	float bumpIntensity;

	std::shared_ptr<Material> pMaterial = CreateMaterial();

	if (material.Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == aiReturn_SUCCESS)
	{
		pMaterial->SetAmbientColor(Float4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));
	}
	if (material.Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor) == aiReturn_SUCCESS)
	{
		pMaterial->SetEmissiveColor(Float4(emissiveColor.r, emissiveColor.g, emissiveColor.b, emissiveColor.a));
	}
	if (material.Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == aiReturn_SUCCESS)
	{
		pMaterial->SetDiffuseColor(Float4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a));
	}
	else
	{
		pMaterial->SetDiffuseColor(Float4(0.0, 0.0, 0.45, 1.0));
	}
	if (material.Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == aiReturn_SUCCESS)
	{
		pMaterial->SetSpecularColor(Float4(specularColor.r, specularColor.g, specularColor.b, specularColor.a));
	}
	if (material.Get(AI_MATKEY_SHININESS, shininess) == aiReturn_SUCCESS)
	{
		pMaterial->SetSpecularPower(shininess);
	}
	if (material.Get(AI_MATKEY_OPACITY, opacity) == aiReturn_SUCCESS)
	{
		pMaterial->SetOpacity(opacity);
	}
	if (material.Get(AI_MATKEY_REFRACTI, indexOfRefraction))
	{
		pMaterial->SetIndexOfRefraction(indexOfRefraction);
	}
	if (material.Get(AI_MATKEY_REFLECTIVITY, reflectivity) == aiReturn_SUCCESS)
	{
		pMaterial->SetReflectance(Float4(reflectivity, reflectivity, reflectivity, reflectivity));
	}
	if (material.Get(AI_MATKEY_BUMPSCALING, bumpIntensity) == aiReturn_SUCCESS)
	{
		pMaterial->SetBumpIntensity(bumpIntensity);
	}

	// Load ambient textures.
	if (material.GetTextureCount(aiTextureType_AMBIENT) > 0 &&
		material.GetTexture(aiTextureType_AMBIENT, 0, &aiTexturePath, nullptr, nullptr, &blendFactor, &aiBlendOperation)
		== aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());
		pMaterial->SetTexture(Material::TextureType::Ambient, pTexture);
	}

	// Load emissive textures.
	if (material.GetTextureCount(aiTextureType_EMISSIVE) > 0 &&
		material.GetTexture(aiTextureType_EMISSIVE, 0, &aiTexturePath, nullptr, nullptr, &blendFactor,
		                    &aiBlendOperation) == aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());
		pMaterial->SetTexture(Material::TextureType::Emissive, pTexture);
	}

	// Load diffuse textures.
	if (material.GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
		material.GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath, nullptr, nullptr, &blendFactor, &aiBlendOperation)
		== aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());
		pMaterial->SetTexture(Material::TextureType::Diffuse, pTexture);
	}

	// Load specular texture.
	if (material.GetTextureCount(aiTextureType_SPECULAR) > 0 &&
		material.GetTexture(aiTextureType_SPECULAR, 0, &aiTexturePath, nullptr, nullptr, &blendFactor,
		                    &aiBlendOperation) == aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());
		pMaterial->SetTexture(Material::TextureType::Specular, pTexture);
	}


	// Load specular power texture.
	if (material.GetTextureCount(aiTextureType_SHININESS) > 0 &&
		material.GetTexture(aiTextureType_SHININESS, 0, &aiTexturePath, nullptr, nullptr, &blendFactor,
		                    &aiBlendOperation) == aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());

		pMaterial->SetTexture(Material::TextureType::SpecularPower, pTexture);
	}

	if (material.GetTextureCount(aiTextureType_OPACITY) > 0 &&
		material.GetTexture(aiTextureType_OPACITY, 0, &aiTexturePath, nullptr, nullptr, &blendFactor, &aiBlendOperation)
		== aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());

		pMaterial->SetTexture(Material::TextureType::Opacity, pTexture);
	}

	// Load normal map texture.
	if (material.GetTextureCount(aiTextureType_NORMALS) > 0 &&
		material.GetTexture(aiTextureType_NORMALS, 0, &aiTexturePath) == aiReturn_SUCCESS)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());

		pMaterial->SetTexture(Material::TextureType::Normal, pTexture);
	}
		// Load bump map (only if there is no normal map).
	else if (material.GetTextureCount(aiTextureType_HEIGHT) > 0 &&
		material.GetTexture(aiTextureType_HEIGHT, 0, &aiTexturePath, nullptr, nullptr, &blendFactor) == aiReturn_SUCCESS
	)
	{
		fs::path texturePath(aiTexturePath.C_Str());
		std::shared_ptr<Texture> pTexture = CreateTexture((parentPath / texturePath).wstring());

		Material::TextureType textureType = (pTexture->GetBpp() >= 24)
			                                    ? Material::TextureType::Normal
			                                    : Material::TextureType::Bump;

		pMaterial->SetTexture(textureType, pTexture);
	}

	//m_MaterialMap.insert( MaterialMap::value_type( materialName.C_Str(), pMaterial ) );
	m_Materials.push_back(pMaterial);
}

void SceneBase::ImportMesh(const aiMesh& mesh)
{
	std::shared_ptr<Mesh> pMesh = CreateMesh();


	pMesh->SetMaterial(m_Materials[mesh.mMaterialIndex]);

	if (mesh.HasPositions())
	{
		const auto positions = CreateFloatVertexBuffer(&(mesh.mVertices[0].x), mesh.mNumVertices, sizeof(aiVector3D));
		pMesh->AddVertexBuffer(BufferBinding("POSITION", 0), positions);
	}

	if (mesh.HasNormals())
	{
		const auto normals = CreateFloatVertexBuffer(&(mesh.mNormals[0].x), mesh.mNumVertices, sizeof(aiVector3D));
		pMesh->AddVertexBuffer(BufferBinding("NORMAL", 0), normals);
	}
	else
	{
		//Calculate the normal by cross the nearby verticals
		std::vector<SimpleMath::Vector3> vecRes = {};
		for (auto verIndics = 0; verIndics < mesh.mNumVertices; ++verIndics)
		{
			auto vertical1 = mesh.mVertices[verIndics];
			auto lastIndics = verIndics - 1;
			if (lastIndics < 0)
				lastIndics = mesh.mNumVertices - 1;
			auto vertical0 = mesh.mVertices[lastIndics];
			auto nextIndics = verIndics + 1;
			nextIndics %= mesh.mNumVertices;
			auto vertical2 = mesh.mVertices[nextIndics];
			auto temp1 = vertical0 - vertical1;
			auto temp2 = vertical2 - vertical1;
			SimpleMath::Vector3 xmftemp1(temp1[0], temp1[1], temp1[2]);
			vecRes.push_back(xmftemp1.Cross({ temp2[0],temp2[1],temp2[2] }));
		}
		const auto normals = CreateFloatVertexBuffer(&vecRes.data()[0].x, vecRes.size(), sizeof(aiVector3D));
		pMesh->AddVertexBuffer(BufferBinding("NORMAL", 0), normals);

	}

	if (mesh.HasTangentsAndBitangents())
	{
		const auto tangents = CreateFloatVertexBuffer(&(mesh.mTangents[0].x), mesh.mNumVertices, sizeof(aiVector3D));
		pMesh->AddVertexBuffer(BufferBinding("TANGENT", 0), tangents);

		const auto bitangents =
			CreateFloatVertexBuffer(&(mesh.mBitangents[0].x), mesh.mNumVertices, sizeof(aiVector3D));
		pMesh->AddVertexBuffer(BufferBinding("BINORMAL", 0), bitangents);
	}

	for (unsigned int i = 0; mesh.HasVertexColors(i); ++i)
	{
		const auto colors = CreateFloatVertexBuffer(&(mesh.mColors[i][0].r), mesh.mNumVertices, sizeof(aiColor4D));
		pMesh->AddVertexBuffer(BufferBinding("COLOR", i), colors);
	}

	for (unsigned int i = 0; mesh.HasTextureCoords(i); ++i)
	{
		switch (mesh.mNumUVComponents[i])
		{
		case 1: // 1-component texture coordinates (U)
			{
				std::vector<float> texcoods1D(mesh.mNumVertices);
				for (unsigned int j = 0; j < mesh.mNumVertices; ++j)
				{
					texcoods1D[j] = mesh.mTextureCoords[i][j].x;
				}
				const auto texcoords = CreateFloatVertexBuffer(texcoods1D.data(), (unsigned int)texcoods1D.size(),
				                                               sizeof(float));
				pMesh->AddVertexBuffer(BufferBinding("TEXCOORD", i), texcoords);
			}
			break;
		case 2: // 2-component texture coordinates (U,V)
			{
				std::vector<aiVector2D> texcoods2D(mesh.mNumVertices);
				for (unsigned int j = 0; j < mesh.mNumVertices; ++j)
				{
					texcoods2D[j] = aiVector2D(mesh.mTextureCoords[i][j].x, mesh.mTextureCoords[i][j].y);
				}
				const auto texcoords = CreateFloatVertexBuffer(&(texcoods2D[0].x), (unsigned int)texcoods2D.size(),
				                                               sizeof(aiVector2D));
				pMesh->AddVertexBuffer(BufferBinding("TEXCOORD", i), texcoords);
			}
			break;
		case 3: // 3-component texture coordinates (U,V,W)
			{
				std::vector<aiVector3D> texcoods3D(mesh.mNumVertices);
				for (unsigned int j = 0; j < mesh.mNumVertices; ++j)
				{
					texcoods3D[j] = mesh.mTextureCoords[i][j];
				}
				const auto texcoords = CreateFloatVertexBuffer(&(texcoods3D[0].x), (unsigned int)texcoods3D.size(),
				                                               sizeof(aiVector3D));
				pMesh->AddVertexBuffer(BufferBinding("TEXCOORD", i), texcoords);
			}
			break;
		}
	}

	// Extract the index buffer.
	if (mesh.HasFaces())
	{
		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < mesh.mNumFaces; ++i)
		{
			const aiFace& face = mesh.mFaces[i];
			// Only extract triangular faces
			if (face.mNumIndices == 3)
			{
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}
			else if (face.mNumIndices == 4)
			{
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[2]);
				indices.push_back(face.mIndices[3]);

			}
		}
		if (indices.size() > 0)
		{
			auto indexBuffer = CreateUIntIndexBuffer(indices.data(), (unsigned int)indices.size());
			pMesh->SetIndexBuffer(indexBuffer);
		}
	}


	m_Meshes.push_back(pMesh);
}

std::shared_ptr<Node> SceneBase::ImportSceneNode(std::shared_ptr<Node> parent, aiNode* aiNode)
{
	if (!aiNode)
	{
		return nullptr;
	}

	// Assimp stores its matrices in row-major but GLM uses column-major.
	// We have to transpose the matrix before using it to construct a glm matrix.
	aiMatrix4x4 mat = aiNode->mTransformation;
	HMatrix localTransform(mat.a1, mat.b1, mat.c1, mat.d1,
	                       mat.a2, mat.b2, mat.c2, mat.d2,
	                       mat.a3, mat.b3, mat.c3, mat.d3,
	                       mat.a4, mat.b4, mat.c4, mat.d4);

	std::shared_ptr<Node> pNode = std::make_shared<Node>(localTransform);
	pNode->SetParent(parent);

	std::string nodeName(aiNode->mName.C_Str());
	if (!nodeName.empty())
	{
		pNode->SetName(nodeName);
	}

	// Add meshes to scene node
	for (unsigned int i = 0; i < aiNode->mNumMeshes; ++i)
	{
		assert(aiNode->mMeshes[i] < m_Meshes.size());

		std::shared_ptr<Mesh> pMesh = m_Meshes[aiNode->mMeshes[i]];
		pNode->AddMesh(pMesh);
	}

	// Recursively Import children
	for (unsigned int i = 0; i < aiNode->mNumChildren; ++i)
	{
		std::shared_ptr<Node> pChild = ImportSceneNode(pNode, aiNode->mChildren[i]);
		pNode->AttachChild(pChild);
	}

	return pNode;
}
