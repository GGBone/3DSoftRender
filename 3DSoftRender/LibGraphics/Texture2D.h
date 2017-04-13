#pragma once
#include "GraphicsLib.h"
#include "Texture.h"
namespace Hikari
{
	class Texture2D : public Texture
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		

	protected:
		void ComputeNumLevelBytes();
		void GenerateNexMipmap(int width, int height, const char* texels,
			int widthNext, int heightNext, char* texelsNext, Float4* rgba);
	public:
		static Texture2D* Load(const std::string& name);
	};
	typedef Texture2D* Texture2DPtr;
}