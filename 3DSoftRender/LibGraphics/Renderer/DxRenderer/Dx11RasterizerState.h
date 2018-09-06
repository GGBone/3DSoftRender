#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/RasterizerState.h"

namespace Hikari
{
	class RasterizerStateDX11 : public RasterizerState
	{
	public:

		RasterizerStateDX11(ID3D11Device* pDevice);
		RasterizerStateDX11(const RasterizerStateDX11& copy);
		virtual ~RasterizerStateDX11();

		const RasterizerStateDX11& operator=(const RasterizerStateDX11& other);

		void SetFillMode(FillMode frontFace = FillMode::Solid, FillMode backFace = FillMode::Solid) override;
		void GetFillMode(FillMode& frontFace, FillMode& backFace) const override;

		void SetPirmitiveMode(PrimitiveMode mode = PrimitiveMode::TRIANGLE_LIST) override;

		void GetPrimitiveMode(PrimitiveMode& primitiveMode) const override;

		void SetCullMode(CullMode cullMode = CullMode::Back) override;
		CullMode GetCullMode() const override;

		void SetFrontFacing(FrontFace frontFace = FrontFace::CounterClockwise) override;
		FrontFace GetFrontFacing() const override;

		void SetDepthBias(float depthBias = 0.0f, float slopeBias = 0.0f, float biasClamp = 0.0f) override;
		void GetDepthBias(float& depthBias, float& slopeBias, float& biasClamp) const override;

		void SetDepthClipEnabled(bool depthClipEnabled = true) override;
		bool GetDepthClipEnabled() const override;

		void SetViewport(const Viewport& viewport) override;
		void SetViewports(const std::vector<Viewport>& viewports) override;
		const std::vector<Viewport>& GetViewports() override;

		void SetScissorEnabled(bool scissorEnable = false) override;
		bool GetScissorEnabled() const override;

		void SetScissorRect(const Rect& rect) override;
		void SetScissorRects(const std::vector<Rect>& rects) override;
		const std::vector<Rect>& GetScissorRects() const override;

		void SetMultisampleEnabled(bool multisampleEnabled = false) override;
		bool GetMultisampleEnabled() const override;

		void SetAntialiasedLineEnable(bool antialiasedLineEnabled) override;
		bool GetAntialiasedLineEnable() const override;

		void SetForcedSampleCount(uint8_t sampleCount) override;
		uint8_t GetForcedSampleCount() override;

		void SetConservativeRasterizationEnabled(bool conservativeRasterizationEnabled = false) override;
		bool GetConservativeRasterizationEnabled() const override;

		// Can only be invoked by the pipeline state
		virtual void Bind();
	protected:

		D3D11_FILL_MODE TranslateFillMode(FillMode fillMode) const;
		D3D11_CULL_MODE TranslateCullMode(CullMode cullMode) const;
		bool TranslateFrontFace(FrontFace frontFace) const;

		std::vector<D3D11_RECT> TranslateRects(const std::vector<Rect>& rects) const;
		std::vector<D3D11_VIEWPORT> TranslateViewports(const std::vector<Viewport>& viewports) const;

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11RasterizerState* m_pRasterizerState{};

		std::vector<D3D11_RECT> m_d3dRects{};
		std::vector<D3D11_VIEWPORT> m_d3dViewports{};

		FillMode m_FrontFaceFillMode{};
		FillMode m_BackFaceFillMode{};
		PrimitiveMode m_PrimitiveMode{};
		CullMode m_CullMode{};

		FrontFace m_FrontFace{};

		float m_DepthBias;
		float m_SlopeBias;
		float m_BiasClamp;

		bool m_DepthClipEnabled;
		bool m_ScissorEnabled;

		bool m_MultisampleEnabled;
		bool m_AntialiasedLineEnabled;

		bool m_ConservativeRasterization;

		uint8_t m_ForcedSampleCount;

		typedef std::vector<Rect> RectList;
		RectList m_ScissorRects{};

		typedef std::vector<Viewport> ViewportList;
		ViewportList m_Viewports{};

		// set to true when the rasterizer state needs to be recreated.
		bool m_StateDirty;
		bool m_ViewportsDirty;
		bool m_ScissorRectsDirty;
	};
}
