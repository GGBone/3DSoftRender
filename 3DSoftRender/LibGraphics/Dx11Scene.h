#pragma once
#include "Graphics\Dx11RenderLIB.h"
#include "Graphics\SceneBase.h"

namespace Hikari
{
	class DirectRenderer;
	class SceneDX11 : public SceneBase
	{
	public:
		SceneDX11(std::shared_ptr<DirectRenderer>& pDevice);
		virtual ~SceneDX11();
	protected:
		virtual std::shared_ptr<BufferBase> CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) const;
		virtual std::shared_ptr<BufferBase> CreateUIntIndexBuffer(const unsigned int* data, unsigned int count) const;

		virtual std::shared_ptr<Mesh> CreateMesh() const;
		virtual std::shared_ptr<Material> CreateMaterial() const;
		virtual std::shared_ptr<Texture> CreateTexture(const std::wstring& fileName) const override;
		virtual std::shared_ptr<Texture> CreateTexture2D(uint16_t width, uint16_t height);
		virtual std::shared_ptr<Texture> GetDefaultTexture();

	private:
		std::shared_ptr<DirectRenderer> m_Renderer;
	};
}