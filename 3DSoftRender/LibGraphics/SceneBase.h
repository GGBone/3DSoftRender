#pragma once
#include "GraphicsLib.h"
#include <Scene.h>
namespace Hikari
{
	class Material;
	class Buffer;
	class Mesh;
	class Texture;
	class Camera;
	class SceneNode;
	
	class SceneBase : public Scene
	{
	public:
		typedef Scene base;

		virtual bool LoadFromFile(const std::wstring& fileName) override;
		virtual bool LoadFromString(const std::string& scene, const std::string& format) override;
		virtual void Render(RenderEventArgs& renderArgs) override;

		virtual Node* GetRootNode() const override;

		virtual void Accept(Visitor& visitor) override;

	protected:

		SceneBase();
		virtual ~SceneBase();


		virtual Buffer* CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) const = 0;
		virtual Buffer* CreateUIntIndexBuffer(const unsigned int* data, unsigned int sizeInBytes) const = 0;

		virtual Mesh* CreateMesh() const = 0;
		virtual Material* CreateMaterial() const = 0;
		virtual Texture* CreateTexture(const std::wstring& fileName) const = 0;
		virtual Texture* CreateTexture2D(uint16_t width, uint16_t height) = 0;

		virtual Texture* GetDefaultTexture() = 0;

	private:
		typedef std::map<std::string, Material*> MaterialMap;
		typedef std::vector< Material*> MaterialList;
		typedef std::vector<Mesh*> MeshList;

		MaterialMap m_MaterialMap;
		MaterialList m_Materials;
		MeshList m_Meshes;

		Node* m_pRootNode;

		void ImportMaterial(const aiMaterial& material, fs::path parentPath);
		void ImportMesh(const aiMesh& mesh);
		Node* ImportSceneNode(Node* parent, aiNode* aiNode);

		std::wstring m_SceneFile;

	};

}