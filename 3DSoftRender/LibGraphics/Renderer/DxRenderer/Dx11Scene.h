#pragma once
#include "Dx11RenderLIB.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/SceneBase.h"

namespace Hikari
{
	class DirectRenderer;

	class SceneDX11 : public SceneBase
	{
	public:
		explicit SceneDX11(const std::shared_ptr<DirectRenderer>& pDevice);
		virtual ~SceneDX11();
	protected:
		std::shared_ptr<VertexIndexBuffer> CreateFloatVertexBuffer(const float* data, unsigned int count,
		                                                           unsigned int stride) const override;
		std::shared_ptr<VertexIndexBuffer> CreateUIntIndexBuffer(const unsigned int* data, unsigned int count) const
		override;

		std::shared_ptr<Mesh> CreateMesh() const override;
		std::shared_ptr<Material> CreateMaterial() const override;
		std::shared_ptr<Texture> CreateTexture(const std::wstring& fileName) const override;
		std::shared_ptr<Texture> CreateTexture2D(uint16_t width, uint16_t height) override;
		std::shared_ptr<Texture> GetDefaultTexture() override;

	private:
		std::shared_ptr<DirectRenderer> m_Renderer;
	};
}
