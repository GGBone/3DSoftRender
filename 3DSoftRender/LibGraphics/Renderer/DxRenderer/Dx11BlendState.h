#pragma once
#include <Resource/BlendState.h>
#include "Dx11RenderLIB.h"
#include "Base/Float4.h"

namespace Hikari
{
	class BlendStateDX11 : public BlendState
	{
	public:
		BlendStateDX11(ID3D11Device* pDevice);
		BlendStateDX11(const BlendStateDX11& copy);

		virtual ~BlendStateDX11();

		BlendStateDX11& operator=(const BlendStateDX11& other);


		void set_blend_mode(const BlendMode& blendMode) override;
		void set_blend_modes(const std::vector<BlendMode>& blendModes) override;
		const std::vector<BlendMode>& get_blend_modes() const override;


		void set_const_blend_factor(Float4& constantBlendFactor) override;
		const Float4& get_const_blend_factor() const override;


		void set_sample_mask(uint32_t sampleMask) override;
		uint32_t get_sample_mask() const override;


		void set_alpha_coverage(bool enabled) override;
		bool get_alpha_coverage() const override;


		void set_independent_blend(bool enabled) override;
		bool get_independent_blend() const override;

		virtual void bind();

	protected:

		static D3D11_BLEND translate_blend_factor(BlendFactor blend_factor);
		static D3D11_BLEND_OP translate_blend_op(BlendOperation blend_operation);
		static UINT8 translate_write_mask(bool red, bool green, bool blue, bool alpha);
		static D3D11_LOGIC_OP translate_logic_operator(LogicOperator logic_op);

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};
		ID3D11BlendState* m_pBlendState;

		typedef std::vector<BlendMode> BlendModeList;
		// A vector of blend modes. One for each render target view that is bound
		// to the output merger stage.
		BlendModeList m_BlendModes;

		bool m_bAlphaToCoverageEnabled;
		bool m_bIndependentBlendEnabled;
		uint32_t m_SampleMask;

		Float4 m_ConstBlendFactor;

		// set to true if we need to recreate the blend state object.
		bool m_bDirty;
	};
}
