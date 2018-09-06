#include "GraphicsPCH.h"
#include "Dx11BlendState.h"

using namespace Hikari;

BlendStateDX11::BlendStateDX11(ID3D11Device* pDevice)
	: m_pDevice(pDevice)
	  , m_pBlendState(nullptr), m_bAlphaToCoverageEnabled(false)
	  , m_bIndependentBlendEnabled(false)
	  , m_SampleMask(0xffffffff)
	  , m_ConstBlendFactor(Float4(1.0f, 1.0f, 1.0f, 1.0f))
	  , m_bDirty(true)
{
	if (m_pDevice)
	{
		m_pDevice->GetImmediateContext(&m_pDeviceContext);
	}

	m_BlendModes.resize(8, BlendMode());
}

BlendStateDX11::BlendStateDX11(const BlendStateDX11& copy)
	: m_pDevice(copy.m_pDevice)
	  , m_pDeviceContext(copy.m_pDeviceContext)
	  , m_pBlendState(nullptr), m_BlendModes(copy.m_BlendModes)
	  , m_bAlphaToCoverageEnabled(copy.m_bAlphaToCoverageEnabled)
	  , m_bIndependentBlendEnabled(copy.m_bIndependentBlendEnabled)
	  , m_SampleMask(copy.m_SampleMask)
	  , m_ConstBlendFactor(copy.m_ConstBlendFactor)
	  , m_bDirty(true)
{
}

BlendStateDX11::~BlendStateDX11()
= default;

BlendStateDX11& BlendStateDX11::operator=(const BlendStateDX11& other)
{
	// Avoid copy to self..
	if (this != &other)
	{
		m_BlendModes = other.m_BlendModes;
		m_bAlphaToCoverageEnabled = other.m_bAlphaToCoverageEnabled;
		m_bIndependentBlendEnabled = other.m_bIndependentBlendEnabled;
		m_SampleMask = other.m_SampleMask;
		m_ConstBlendFactor = other.m_ConstBlendFactor;

		m_bDirty = true;
	}

	return *this;
}

void BlendStateDX11::set_blend_mode(const BlendMode& blendMode)
{
	m_BlendModes[0] = blendMode;
	m_bDirty = true;
}

void BlendStateDX11::set_blend_modes(const std::vector<BlendMode>& blendModes)
{
	m_BlendModes = blendModes;
	m_bDirty = true;
}

const std::vector<BlendState::BlendMode>& BlendStateDX11::get_blend_modes() const
{
	return m_BlendModes;
}

void BlendStateDX11::set_alpha_coverage(bool enabled)
{
	if (m_bAlphaToCoverageEnabled != enabled)
	{
		m_bAlphaToCoverageEnabled = enabled;
		m_bDirty = true;
	}
}

bool BlendStateDX11::get_alpha_coverage() const
{
	return m_bAlphaToCoverageEnabled;
}

void BlendStateDX11::set_independent_blend(bool enabled)
{
	if (m_bAlphaToCoverageEnabled != enabled)
	{
		m_bAlphaToCoverageEnabled = enabled;
		m_bDirty = true;
	}
}

bool BlendStateDX11::get_independent_blend() const
{
	return m_bIndependentBlendEnabled;
}

void BlendStateDX11::set_const_blend_factor(Float4& constant_blend_factor)
{
	m_ConstBlendFactor = constant_blend_factor;
	// No need to set the dirty flag as this value is not used to create the blend state object.
	// It is only used when activating the blend state of the output merger.
}

const Float4& BlendStateDX11::get_const_blend_factor() const
{
	return m_ConstBlendFactor;
}

void BlendStateDX11::set_sample_mask(uint32_t sampleMask)
{
	m_SampleMask = sampleMask;
	// No need to set the dirty flag as this value is not used to create the blend state object.
	// It is only used when activating the blend state of the output merger.
}

uint32_t BlendStateDX11::get_sample_mask() const
{
	return m_SampleMask;
}

D3D11_BLEND BlendStateDX11::translate_blend_factor(BlendFactor blendFactor)
{
	D3D11_BLEND result = D3D11_BLEND_ONE;

	switch (blendFactor)
	{
	case BlendFactor::Zero:
		result = D3D11_BLEND_ZERO;
		break;
	case BlendFactor::One:
		result = D3D11_BLEND_ONE;
		break;
	case BlendFactor::SrcColor:
		result = D3D11_BLEND_SRC_COLOR;
		break;
	case BlendFactor::OneMinusSrcColor:
		result = D3D11_BLEND_INV_SRC_COLOR;
		break;
	case BlendFactor::DstColor:
		result = D3D11_BLEND_DEST_COLOR;
		break;
	case BlendFactor::OneMinusDstColor:
		result = D3D11_BLEND_INV_DEST_COLOR;
		break;
	case BlendFactor::SrcAlpha:
		result = D3D11_BLEND_SRC_ALPHA;
		break;
	case BlendFactor::OneMinusSrcAlpha:
		result = D3D11_BLEND_INV_SRC_ALPHA;
		break;
	case BlendFactor::DstAlpha:
		result = D3D11_BLEND_DEST_ALPHA;
		break;
	case BlendFactor::OneMinusDstAlpha:
		result = D3D11_BLEND_INV_DEST_ALPHA;
		break;
	case BlendFactor::SrcAlphaSat:
		result = D3D11_BLEND_SRC_ALPHA_SAT;
		break;
	case BlendFactor::ConstBlendFactor:
		result = D3D11_BLEND_BLEND_FACTOR;
		break;
	case BlendFactor::OneMinusBlendFactor:
		result = D3D11_BLEND_INV_BLEND_FACTOR;
		break;
	case BlendFactor::Src1Color:
		result = D3D11_BLEND_SRC1_COLOR;
		break;
	case BlendFactor::OneMinusSrc1Color:
		result = D3D11_BLEND_INV_SRC1_COLOR;
		break;
	case BlendFactor::Src1Alpha:
		result = D3D11_BLEND_INV_SRC1_ALPHA;
		break;
	case BlendFactor::OneMinusSrc1Alpha:
		result = D3D11_BLEND_INV_SRC1_ALPHA;
		break;
	default:

		break;
	}

	return result;
}

D3D11_BLEND_OP BlendStateDX11::translate_blend_op(BlendOperation blendOperation)
{
	D3D11_BLEND_OP result = D3D11_BLEND_OP_ADD;
	switch (blendOperation)
	{
	case BlendOperation::Add:
		result = D3D11_BLEND_OP_ADD;
		break;
	case BlendOperation::Subtract:
		result = D3D11_BLEND_OP_SUBTRACT;
		break;
	case BlendOperation::ReverseSubtract:
		result = D3D11_BLEND_OP_REV_SUBTRACT;
		break;
	case BlendOperation::Min:
		result = D3D11_BLEND_OP_MIN;
		break;
	case BlendOperation::Max:
		result = D3D11_BLEND_OP_MAX;
		break;
	default:

		break;
	}

	return result;
}

UINT8 BlendStateDX11::translate_write_mask(bool red, bool green, bool blue, bool alpha)
{
	UINT8 writeMask = 0;
	if (red)
	{
		writeMask |= D3D11_COLOR_WRITE_ENABLE_RED;
	}
	if (green)
	{
		writeMask |= D3D11_COLOR_WRITE_ENABLE_GREEN;
	}
	if (blue)
	{
		writeMask |= D3D11_COLOR_WRITE_ENABLE_BLUE;
	}
	if (alpha)
	{
		writeMask |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
	}

	return writeMask;
}

D3D11_LOGIC_OP BlendStateDX11::translate_logic_operator(LogicOperator logicOp)
{
	D3D11_LOGIC_OP result = D3D11_LOGIC_OP_NOOP;

	switch (logicOp)
	{
	case LogicOperator::None:
		result = D3D11_LOGIC_OP_NOOP;
		break;
	case LogicOperator::Clear:
		result = D3D11_LOGIC_OP_CLEAR;
		break;
	case LogicOperator::set:
		result = D3D11_LOGIC_OP_SET;
		break;
	case LogicOperator::Copy:
		result = D3D11_LOGIC_OP_SET;
		break;
	case LogicOperator::CopyInverted:
		result = D3D11_LOGIC_OP_COPY_INVERTED;
		break;
	case LogicOperator::Invert:
		result = D3D11_LOGIC_OP_INVERT;
		break;
	case LogicOperator::And:
		result = D3D11_LOGIC_OP_AND;
		break;
	case LogicOperator::Nand:
		result = D3D11_LOGIC_OP_NAND;
		break;
	case LogicOperator::Or:
		result = D3D11_LOGIC_OP_OR;
		break;
	case LogicOperator::Nor:
		result = D3D11_LOGIC_OP_NOR;
		break;
	case LogicOperator::Xor:
		result = D3D11_LOGIC_OP_XOR;
		break;
	case LogicOperator::Equiv:
		result = D3D11_LOGIC_OP_EQUIV;
		break;
	case LogicOperator::AndReverse:
		result = D3D11_LOGIC_OP_AND_REVERSE;
		break;
	case LogicOperator::AndInverted:
		result = D3D11_LOGIC_OP_AND_INVERTED;
		break;
	case LogicOperator::OrReverse:
		result = D3D11_LOGIC_OP_OR_REVERSE;
		break;
	case LogicOperator::OrInverted:
		result = D3D11_LOGIC_OP_OR_INVERTED;
		break;
	default:
		break;
	}

	return result;
}

void BlendStateDX11::bind()
{
	if (m_bDirty)
	{
		// (Re)create the blend state object.
		D3D11_BLEND_DESC blendDesc;

		blendDesc.AlphaToCoverageEnable = m_bAlphaToCoverageEnabled;
		blendDesc.IndependentBlendEnable = m_bIndependentBlendEnabled;
		for (unsigned int i = 0; i < 8 && i < m_BlendModes.size(); i++)
		{
			D3D11_RENDER_TARGET_BLEND_DESC& rtBlendDesc = blendDesc.RenderTarget[i];
			BlendMode& blendMode = m_BlendModes[i];

			rtBlendDesc.BlendEnable = blendMode.BlendEnabled;

			//rtBlendDesc.LogicOpEnable = blendMode.LogicOpEnabled;
			rtBlendDesc.SrcBlend = translate_blend_factor(blendMode.SrcFactor);
			rtBlendDesc.DestBlend = translate_blend_factor(blendMode.DstFactor);
			rtBlendDesc.BlendOp = translate_blend_op(blendMode.BlendOp);
			rtBlendDesc.SrcBlendAlpha = translate_blend_factor(blendMode.SrcAlphaFactor);
			rtBlendDesc.DestBlendAlpha = translate_blend_factor(blendMode.DstAlphaFactor);
			rtBlendDesc.BlendOpAlpha = translate_blend_op(blendMode.AlphaOp);
			//rtBlendDesc.LogicOp = TranslateLogicOperator(blendMode.LogicOp);
			rtBlendDesc.RenderTargetWriteMask = translate_write_mask(blendMode.WriteRed, blendMode.WriteGreen,
			                                                         blendMode.WriteBlue, blendMode.WriteAlpha);
		}

		m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState);

		m_bDirty = false;
	}

	// Now activate the blend state:
	m_pDeviceContext->OMSetBlendState(m_pBlendState, m_ConstBlendFactor, m_SampleMask);
}
