#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "Shader/Shader.h"
#include "Shader/ShaderParameter.h"
#include "SceneGraph/ClearFlag.h"
#include "Base/Float4.h"

namespace Hikari
{
	class Float2;

	class Texture : public Object
	{
	public:
		enum class Dimension
		{
			Texture1D,
			Texture1DArray,
			Texture2D,
			Texture2DArray,
			Texture3D,
			TextureCube,
			UnorderedAccessTexture,
			UnorderedAccessTextureArray,
		};

		// The number of components used to create the texture.
		enum class Components
		{
			R,
			// One red component.
			RG,
			// Red, and green components.
			RGB,
			// Red, green, and blue components.
			RGBA,
			// Red, green, blue, and alpha components.
			Depth,
			// Depth component.
			DepthStencil // Depth and stencil in the same texture.
		};

		// The type of components in the texture.
		enum class Type
		{
			Typeless,
			// Typeless formats.
			// TODO: sRGB type
			UnsignedNormalized,
			// Unsigned normalized (8, 10, or 16-bit unsigned integer values mapped to the range [0..1])
			SignedNormalized,
			// Signed normalized (8, or 16-bit signed integer values mapped to the range [-1..1])
			Float,
			// Floating point format (16, or 32-bit).
			UnsignedInteger,
			// Unsigned integer format (8, 16, or 32-bit unsigned integer formats).
			SignedInteger,
			// Signed integer format (8, 16, or 32-bit signed integer formats).
		};

		struct TextureFormat
		{
			Components Components;
			Type Type;
			uint8_t NumSamples;

			uint8_t RedBits;
			uint8_t GreenBits;
			uint8_t BlueBits;
			uint8_t AlphaBits;
			uint8_t DepthBits;
			uint8_t StencilBits;

			TextureFormat(Texture::Components components = Components::RGBA,
			              Texture::Type type = Type::UnsignedNormalized,
			              uint8_t numSamples = 1,
			              uint8_t redBits = 8,
			              uint8_t greenBits = 8,
			              uint8_t blueBits = 8,
			              uint8_t alphaBits = 8,
			              uint8_t depthBits = 0,
			              uint8_t stencilBits = 0
			)
				: Components(components)
				  , Type(type)
				  , NumSamples(numSamples)
				  , RedBits(redBits)
				  , GreenBits(greenBits)
				  , BlueBits(blueBits)
				  , AlphaBits(alphaBits)
				  , DepthBits(depthBits)
				  , StencilBits(stencilBits)
			{
			}
		};

		enum class CubeFace
		{
			Right,
			// +X
			Left,
			// -X
			Top,
			// +Y
			Bottom,
			// -Y
			Front,
			// +Z
			Back,
			// -Z
		};

		virtual bool LoadTexture2D(const std::wstring& fileName) = 0;

		virtual bool LoadTextureCube(const std::wstring& fileName) = 0;

		/**
		* Bind this texture for use by the shaders.
		*/
		virtual void bind(uint32_t ID, Shader::ShaderType shaderType) =0;

		/**
		* Unbind the texture.
		*/
		virtual void unbind(uint32_t ID, Shader::ShaderType shaderType) =0;

		virtual void GenerateMipmaps() = 0;

		virtual std::shared_ptr<Texture> GetFace(CubeFace face) const = 0;

		virtual std::shared_ptr<Texture> GetSlice(unsigned int slice) const = 0;

		virtual uint16_t GetWidth() const = 0;

		virtual uint16_t GetHeight() const = 0;

		virtual uint16_t GetDepth() const = 0;

		virtual uint8_t GetBpp() const = 0;

		virtual bool IsTransparent() const = 0;

		virtual void Resize(uint16_t width, uint16_t height = 0, uint16_t depth = 0) = 0;

		template <typename T>
		void Plot(Float2& coord, const T& color);

		template <typename T>
		T FetchPixel(Float2& coord);

		virtual void Copy(Texture* other) = 0;

		virtual void Clear(ClearFlags clearFlags = ClearFlags::All, const Float4& color = Float4(0, 0, 0, 0),
		                   float depth = 1.0f, uint8_t stencil = 0) = 0;

	protected:
		virtual void Plot(Float2& coord, const uint8_t* pixel, size_t size) = 0;
		virtual void FetchPixel(Float2& coord, uint8_t*& pixel, size_t size) = 0;
	};

	template <typename T>
	void Texture::Plot(Float2& coord, const T& color)
	{
		Plot(coord, reinterpret_cast<const uint8_t*>(&color), sizeof(T));
	}

	template <typename T>
	T Texture::FetchPixel(Float2& coord)
	{
		uint8_t* pixel = nullptr;
		FetchPixel(coord, pixel, sizeof(T));

		return *reinterpret_cast<T*>(pixel);
	}
}
