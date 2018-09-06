#pragma once

#include "Object.h"

namespace Hikari
{
	class Float4;

	class BlendState : public Object
	{
	public:

		enum class BlendOperation // could also be called BlendOperand
		{
			Add,
			// Add source and destination ( s + d ).
			Subtract,
			// Subtract source from destination ( d - s )
			ReverseSubtract,
			// Subtract destination from source ( s - s )
			Min,
			// The minimum of source and destination ( min( s, d ) )
			Max // The maximum of source and destination ( max( s, d ) )
		};

		enum class BlendFactor
		{
			Zero,
			// Multiply the pixel operand by 0 before applying the blend operation.
			One,
			// Multiply the pixel operand by 1 before applying the blend operation.
			SrcColor,
			// Multiply the pixel operand by the source color (Cs) before applying the blend operation.
			OneMinusSrcColor,
			// Multiply the pixel operand by ( 1 - Cs ) before applying the blend operation.
			DstColor,
			// Multiply the pixel operand by the destination color (Cd) before applying the blend operation.
			OneMinusDstColor,
			// Multiply the pixel operand by ( 1 - Cd ) before applying the blend operation.
			SrcAlpha,
			// Multiply the pixel operand by the source alpha ( As ) before applying the blend operation.
			OneMinusSrcAlpha,
			// Multiply the pixel operand by ( 1 - As ) before applying the blend operation.
			DstAlpha,
			// Multiply the pixel operand by the destination alpha ( Ad ) before applying the blend operation.
			OneMinusDstAlpha,
			// Multiply the pixel operand by ( 1 - Ad ) before applying the blend operation.
			SrcAlphaSat,
			// Multiply the pixel operand by min( As, 1 - Ad ) before applying the blend operation.
			ConstBlendFactor,
			// Multiply the pixel operand by a constant blend factor before applying the blend operation. See @BlendState::SetConstBlendFactor.
			OneMinusBlendFactor,
			// Multiply the pixel operand by ( 1 - blend factor ) before applying the blend operation. See @BlendState::SetBlendFactor.
			Src1Color,
			// Multiply the pixel operand by the color of the 2nd output ( Cs1 ) from the pixel shader before applying the blend operation. @see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205120(v=vs.85).aspx#Blending @see https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
			OneMinusSrc1Color,
			// Multiply the pixel operand by ( 1 - Cs1 ) before applying the blend operation.
			Src1Alpha,
			// Multiply the pixel operand by the alpha value of the 2nd output ( As1 ) from the pixel shader before applying the blend operation.
			OneMinusSrc1Alpha // Multiply the pixel operand by ( 1 - As1 ) before applying the blend operation.
		};

		/**
		* Specify a logical pixel operation for rendering.
		* Supported since DirectX 11.1 and OpenGL 2.0+
		*/
		enum class LogicOperator
		{
			None,
			// No logical operator is performed.
			Clear,
			// Clears the render target (d = 0) at the current pixel.
			set,
			// set the destination render target to 1 (d = 1) at the current pixel.
			Copy,
			// Copy the source to the destination (d = s) at the current pixel.
			CopyInverted,
			// Copy the inverted source to the destination (d = ~s) at the current pixel.
			Invert,
			// Invert the color in the render target (d = ~d) at the current pixel.
			And,
			// Logical And the source and destination values (d = s & d) at the current pixel.
			Nand,
			// Logical !And the source and destination values (d = ~(s & d)) at the current pixel.
			Or,
			// Logical Or the source and destination values (d = s | d) at the current pixel.
			Nor,
			// Logical !Or the source and destination values (d = ~( s | d) at the current pixel.
			Xor,
			// Logical Xor the source and destination values (d = s ^ d) at the current pixel.
			Equiv,
			// Logical !Xor at the source and destination values (d = ~(s ^ d) at the current pixel.
			AndReverse,
			// Logical And the source and inverted destination values (d = s & ~d) at the current pixel.
			AndInverted,
			// Logical And the inverted source  and destination values (d = ~s & d) at the current pixel.
			OrReverse,
			// Logical Or the source and inverted destination values (d = s | ~d) at the current pixel.
			OrInverted // Logical Or the inverted source and destination values (d = ~s | d) at the current pixel.
		};


		struct BlendMode
		{
			bool BlendEnabled;


			bool LogicOpEnabled;


			BlendFactor SrcFactor;

			BlendFactor DstFactor;

			BlendOperation BlendOp;


			BlendFactor SrcAlphaFactor;


			BlendFactor DstAlphaFactor;


			BlendOperation AlphaOp;


			LogicOperator LogicOp;

			bool WriteRed;


			bool WriteGreen;


			bool WriteBlue;


			bool WriteAlpha;

			explicit BlendMode(bool enabled = false,
			                   bool logicOpEnabled = false,
			                   BlendFactor srcFactor = BlendFactor::One,
			                   BlendFactor dstFactor = BlendFactor::Zero,
			                   BlendOperation blendOp = BlendOperation::Add,
			                   BlendFactor srcAlphaFactor = BlendFactor::One,
			                   BlendFactor dstAlphaFactor = BlendFactor::Zero,
			                   BlendOperation alphaOp = BlendOperation::Add,
			                   LogicOperator logicOp = LogicOperator::None,
			                   bool writeRed = true,
			                   bool writeGreen = true,
			                   bool writeBlue = true,
			                   bool writeAlpha = true)
				: BlendEnabled(enabled)
				  , LogicOpEnabled(logicOpEnabled)
				  , SrcFactor(srcFactor)
				  , DstFactor(dstFactor)
				  , BlendOp(blendOp)
				  , SrcAlphaFactor(srcAlphaFactor)
				  , DstAlphaFactor(dstAlphaFactor)
				  , AlphaOp(alphaOp)
				  , LogicOp(logicOp)
				  , WriteRed(writeRed)
				  , WriteGreen(writeGreen)
				  , WriteBlue(writeBlue)
				  , WriteAlpha(writeAlpha)
			{
			}
		};

		virtual void set_blend_mode(const BlendMode& blendMode) = 0;
		// Use this method to set all blend modes at once. Only the first 8 are considered.
		virtual void set_blend_modes(const std::vector<BlendMode>& blendModes) = 0;
		virtual const std::vector<BlendMode>& get_blend_modes() const = 0;

		virtual void set_const_blend_factor(Float4& constantBlendFactor) = 0;
		virtual const Float4& get_const_blend_factor() const = 0;

		/**
		* The sample mask determines which samples get updated in all the active render targets.
		* When multisample anti-aliasing is enabled, the pixel color is determined at 2, 4, 8 or 16
		* subpixels within a single pixel and the final result is blended to achieve
		* an anti-aliased effect. The sample mask determines which subpixel locations are
		* used to determine the final pixel color.
		* The default value is 0xffffffff which enables all subpixel locations to be used
		* for the final color. Note that a 32-bit sample mask allows you to mask 32 samples. As far
		* as I know at the time of this writing, only 16 samples are supported so only
		* bits 0 - 15 in the sample mask are considered (but future API implementations may
		* support up to 32 samples per pixel!?)
		* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ff476462%28v=vs.85%29.aspx
		* @see https://www.opengl.org/sdk/docs/man/html/glSampleMaski.xhtml
		*/
		virtual void set_sample_mask(uint32_t sample_mask) = 0;
		virtual uint32_t get_sample_mask() const = 0;

		/**
		* Whether to enable alpha coverage.
		* @see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205072(v=vs.85).aspx#Alpha_To_Coverage
		* @see https://www.opengl.org/sdk/docs/man4/html/glSampleCoverage.xhtml
		*/
		virtual void set_alpha_coverage(bool enabled) = 0;
		virtual bool get_alpha_coverage() const = 0;

		/**
		* Enable independent blend modes for render target color buffers.
		* If set to true then the BlendMode settings for each color buffer bound
		* to the current render target will be used. If set to false, only the BlendMode
		* value set at index 0 will be used to blend all currently bound color buffers.
		* Independent blending is disabled by default and you should only enable it
		* if you have explicitly specified a blend mode for each render target buffer
		* that is bound, otherwise the results are undefined.
		*/
		virtual void set_independent_blend(bool b_enabled) = 0;
		virtual bool get_independent_blend() const = 0;
	};
}
