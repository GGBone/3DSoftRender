#pragma once
#include "GraphicsLib.h"
#include "Scene.h"
#include "Resource/VertexIndexBuffer.h"
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace Hikari
{
	class Material;
	class BufferBase;
	class Mesh;
	class Texture;
	class Camera;
	class SceneNode;

	class SceneBase : public Scene
	{
	public:
		typedef Scene base;

		bool LoadFromFile(const std::wstring& fileName) override;
		bool LoadFromString(const std::string& scene, const std::string& format) override;
		void Render(RenderEventArgs& renderArgs) override;

		std::shared_ptr<Node> GetRootNode() override;

		void Accept(Visitor& visitor) override;

		void OnLoadingProgress(ProgressEventArgs& e) override;
	protected:
		SceneBase() = default;
		virtual ~SceneBase();


		virtual std::shared_ptr<VertexIndexBuffer> CreateFloatVertexBuffer(
			const float* data, unsigned int count, unsigned int stride) const = 0;
		virtual std::shared_ptr<VertexIndexBuffer> CreateUIntIndexBuffer(
			const unsigned int* data, unsigned int sizeInBytes) const = 0;

		virtual std::shared_ptr<Mesh> CreateMesh() const = 0;
		virtual std::shared_ptr<Material> CreateMaterial() const = 0;
		virtual std::shared_ptr<Texture> CreateTexture(const std::wstring& fileName) const = 0;
		virtual std::shared_ptr<Texture> CreateTexture2D(uint16_t width, uint16_t height) = 0;

		virtual std::shared_ptr<Texture> GetDefaultTexture() = 0;

	private:
		typedef std::map<std::string, std::shared_ptr<Material>> MaterialMap;
		typedef std::vector<std::shared_ptr<Material>> MaterialList;
		typedef std::vector<std::shared_ptr<Mesh>> MeshList;

		MaterialMap m_MaterialMap{};
		MaterialList m_Materials{};
		MeshList m_Meshes{};

		std::shared_ptr<Node> m_pRootNode{};

		void ImportMaterial(const aiMaterial& material, fs::path parentPath);
		void ImportMesh(const aiMesh& mesh);
		std::shared_ptr<Node> ImportSceneNode(std::shared_ptr<Node> parent, aiNode* aiNode);

		std::wstring m_SceneFile;
	};
}
