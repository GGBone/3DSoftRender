#pragma once
#include "Dx11RenderLIB.h"
#include "SceneBase.h"

namespace Hikari
{
	class DirectRenderer;
	class SceneDX11 : public SceneBase
	{
	public:
		SceneDX11(DirectRenderer* pDevice);
		virtual ~SceneDX11();
	protected:
		virtual Buffer* CreateFloatVertexBuffer(const float* data, unsigned int count, unsigned int stride) const;
		virtual Buffer* CreateUIntIndexBuffer(const unsigned int* data, unsigned int count) const;

		virtual Mesh* CreateMesh() const;
		virtual Material* CreateMaterial() const;
		virtual Texture* CreateTexture(const std::string& fileName) const override;
		virtual Texture* CreateTexture2D(uint16_t width, uint16_t height);
		virtual Texture* GetDefaultTexture();

	private:
		DirectRenderer* m_Renderer;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pContext;

	};
}