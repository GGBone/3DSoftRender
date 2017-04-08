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
		Texture2D(Format tformat, int dimension0, int dimension1, int numLevels, Buffer::Usage usage = Buffer::BU_STATIC);
		virtual ~Texture2D();
		inline int GetWidth()const
		{
			return GetDimension(1, 0);
		}
		inline int GetHeight()const
		{
			return GetDimension(2, 0);
		}
		void GenerateMipmaps()
		{

		}
		bool HasMipmaps()const
		{
			return false;
		}
		char* GetData(int level)const
		{
			return mData + mLevelOffsets[level];
		}

	protected:
		void ComputeNumLevelBytes();
		void GenerateNexMipmap(int width, int height, const char* texels,
			int widthNext, int heightNext, char* texelsNext, Float4* rgba);
	public:
		static Texture2D* Load(const std::string& name);
	};
	typedef Texture2D* Texture2DPtr;
}