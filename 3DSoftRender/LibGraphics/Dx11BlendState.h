#pragma once
#include "Graphics\GraphicsLib.h"
#include <BlendState.h>
#include "Dx11RenderLIB.h"
#include "Math\Base\Float4.h"
namespace Hikari
{

	class BlendStateDX11 : public BlendState
	{
	public:
		BlendStateDX11(ID3D11Device* pDevice);
		BlendStateDX11(const BlendStateDX11& copy);

		virtual ~BlendStateDX11();

		const BlendStateDX11& operator=(const BlendStateDX11& other);

	
		virtual void SetBlendMode(const BlendMode& blendMode);
		virtual void SetBlendModes(const std::vector<BlendMode>& blendModes);
		virtual const std::vector<BlendMode>& GetBlendModes() const;


		virtual void SetConstBlendFactor(Float4& constantBlendFactor) override;
		virtual const Float4& GetConstBlendFactor() const;

	
		virtual void SetSampleMask(uint32_t sampleMask);
		virtual uint32_t GetSampleMask() const;

	
		virtual void SetAlphaCoverage(bool enabled);
		virtual bool GetAlphaCoverage() const;

	
		virtual void SetIndependentBlend(bool enabled);
		virtual bool GetIndependentBlend() const;

		virtual void Bind();

	protected:

		D3D11_BLEND TranslateBlendFactor(BlendState::BlendFactor blendFactor) const;
		D3D11_BLEND_OP TranslateBlendOp(BlendState::BlendOperation blendOperation) const;
		UINT8 TranslateWriteMask(bool red, bool green, bool blue, bool alpha) const;
		D3D11_LOGIC_OP TranslateLogicOperator(LogicOperator logicOp) const;

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11BlendState* m_pBlendState;

		typedef std::vector<BlendMode> BlendModeList;
		// A vector of blend modes. One for each render target view that is bound
		// to the output merger stage.
		BlendModeList m_BlendModes;

		bool m_bAlphaToCoverageEnabled;
		bool m_bIndependentBlendEnabled;
		uint32_t m_SampleMask;

		Float4 m_ConstBlendFactor;

		// Set to true if we need to recreate the blend state object.
		bool m_bDirty;
	};
}