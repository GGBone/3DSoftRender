#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/SamplerState.h"
#include "Shader/ShaderParameter.h"
#include "Base/Float4.h"
#include "Resource/SamplerState.h"

namespace Hikari
{
	class Shader;

	class SamplerStateDX11 : public SamplerState
	{
	public:
		SamplerStateDX11(ID3D11Device* pDevice);
		virtual ~SamplerStateDX11();

		void SetFilter(MinFilter minFilter, MagFilter magFilter, MipFilter mipFilter) override;
		void GetFilter(MinFilter& minFilter, MagFilter& magFilter, MipFilter& mipFilter) const override;

		void SetWrapMode(WrapMode u = Repeat, WrapMode v = Repeat, WrapMode w = Repeat) override;
		void GetWrapMode(WrapMode& u, WrapMode& v, WrapMode& w) const override;

		void SetCompareFunction(CompareFunc compareFunc) override;
		CompareFunc GetCompareFunc() const override;

		void SetLODBias(float lodBias) override;
		float GetLODBias() const override;

		void SetMinLOD(float minLOD) override;
		float GetMinLOD() const override;

		void SetMaxLOD(float maxLOD) override;
		float GetMaxLOD() const override;

		void SetBorderColor(const Float4& borderColor) override;
		const Float4& GetBorderColor() const override;

		void EnableAnisotropicFiltering(bool enabled) override;
		bool IsAnisotropicFilteringEnabled() const override;

		void SetMaxAnisotropy(uint8_t maxAnisotropy) override;
		uint8_t GetMaxAnisotropy() const override;

		void bind(uint32_t ID, Shader::ShaderType shaderType) override;
		void unbind(uint32_t ID, Shader::ShaderType shaderType) override;

	protected:

		D3D11_FILTER TranslateFilter() const;
		static D3D11_TEXTURE_ADDRESS_MODE TranslateWrapMode(WrapMode wrapMode);
		static D3D11_COMPARISON_FUNC TranslateComparisonFunction(CompareFunc compareFunc);

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11SamplerState* m_pSamplerState;

		MinFilter m_MinFilter;
		MagFilter m_MagFilter;
		MipFilter m_MipFilter;
		WrapMode m_WrapModeU, m_WrapModeV, m_WrapModeW;
		CompareMode m_CompareMode;
		CompareFunc m_CompareFunc;

		float m_fLODBias;
		float m_fMinLOD;
		float m_fMaxLOD;

		Float4 m_BorderColor;

		bool m_bIsAnisotropicFilteringEnabled;
		uint8_t m_AnisotropicFiltering;

		// set to true if the sampler state needs to be recreated.
		bool m_bIsDirty;
	};
}
