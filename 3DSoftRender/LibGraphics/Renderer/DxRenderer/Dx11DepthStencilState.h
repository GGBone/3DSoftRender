#pragma once
#include "Dx11RenderLIB.h"

#include "Resource/DepthStencilState.h"

namespace Hikari
{
	class DepthStencilStateDX11 : public DepthStencilState
	{
	public:
		DepthStencilStateDX11(ID3D11Device* pDevice);
		DepthStencilStateDX11(const DepthStencilStateDX11& copy);

		virtual ~DepthStencilStateDX11();

		const DepthStencilStateDX11& operator=(const DepthStencilStateDX11& other);

		void SetDepthMode(const DepthMode& depthMode) override;
		const DepthMode& GetDepthMode() const override;

		void SetStencilMode(const StencilMode& stencilMode) override;
		const StencilMode& GetStencilMode() const override;

		// Can only be called by the pipeline state.
		void Bind();
	protected:

		D3D11_DEPTH_WRITE_MASK TranslateDepthWriteMask(DepthWrite depthWrite) const;
		D3D11_COMPARISON_FUNC TranslateCompareFunc(CompareFunction compareFunc) const;
		D3D11_STENCIL_OP TranslateStencilOperation(StencilOperation stencilOperation) const;
		D3D11_DEPTH_STENCILOP_DESC TranslateFaceOperation(FaceOperation faceOperation) const;
		D3D11_DEPTH_STENCIL_DESC TranslateDepthStencilState(const DepthMode& depthMode,
		                                                    const StencilMode& stencilMode) const;

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11DepthStencilState* m_pDepthStencilState{};

		DepthMode m_DepthMode;
		StencilMode m_StencilMode;

		bool m_bDirty;
	};
}
