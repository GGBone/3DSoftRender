#pragma once
#include "GraphicsLib.h"
#include "Object.h"
#include "ShaderParameters.h"
#include "Buffer.h"	
#include "Float4.h"
namespace Hikari
{
	class Texture : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;

	public:
		enum Format
		{
			TF_NONE,
			//small color
			TF_R5G6B5,
			TF_A1R5G5B5,
			TF_A4R4G4B4,

			//8-bit integer formats
			TF_A8,
			TF_L8,
			TF_A8L8,
			TF_R8G8B8,
			TF_R8G8B8A8,
			TF_A8B8G8R8,

			//16bit
			TF_L16,
			TF_G16R16,
			TF_A16B16G16R16,

			//16bit floating-point formats
			TF_R16F,
			TF_G16R16F,
			TF_A16B16G16R16F,

			//32bit floating-point formats
			TF_R32F,
			TF_G32R32F,
			TF_A32B32G32R32F,

			//DXT compressed formats
			TF_DXT1,
			TF_DXT3,
			TF_DXT5,

			//Depth-stencil format
			TF_D24S8,
			TF_QUANTITY
		};

		enum Type
		{
			TT_1D,
			TT_2D,
			TT_3D,
			TT_CUBE,
			TT_QUANTITY
		};

		enum
		{
			MM_MAX_MIPMAP_LEVELS = 16
		};

	protected:
		Texture(Format tformat, Type type, Buffer::Usage usage, int numLevels);

	public:
		virtual ~Texture();

		inline Format GetFormat()const
		{
			return mFormat;
		}
		inline Type GetTextureType()const
		{
			return mType;
		}
		inline Buffer::Usage GetUsage()const
		{
			return mUsage;
		}
		inline int GetNumLevels()const
		{
			return mNumLevels;
		}
		inline int GetNumDimensions()const
		{
			return msNumDimensions[mType];
		}
		inline int GetDimension(int i, int level)const
		{
			return mDimension[i][level];
		}
		inline int GetNumLevelBytes(int level)const
		{
			return mNumLevelBytes[level];
		}
		inline int GetNumTotalBytes()const 
		{
			return mNumTotalBytes;
		}
		inline int GetLevelOffset(int level)const
		{
			return mLevelOffsets[level];
		}
		inline int GetPixelSize()const
		{
			return msPixelSize[mFormat];
		}

		inline static int GetPixelSize(Format tformat)
		{
			return msPixelSize[tformat];
		}
		inline bool IsCompressed()const
		{
			return mFormat == TF_DXT1 || mFormat == TF_DXT3 || mFormat == TF_DXT5;
		}
		inline bool IsMipmapable()const
		{
			return msMipmapable[mFormat];
		}


		inline const char* GetData()const
		{
			return mData;
		}
		enum { MAX_USER_FIELDS = 8 };
		inline void SetUserField(int i, int userField)
		{
			mUserField[i] = userField;
		}
		inline int GetUserField(int i)const
		{
			return mUserField[i];
		}
	protected:
		Format mFormat;
		Type mType;
		Buffer::Usage mUsage;
		int mNumLevels;

		int mDimension[3][MM_MAX_MIPMAP_LEVELS];
		int mNumLevelBytes[MM_MAX_MIPMAP_LEVELS];
		int mNumTotalBytes;
		int mLevelOffsets[MM_MAX_MIPMAP_LEVELS];

		int mUserField[MAX_USER_FIELDS];
		char* mData;

		static int msNumDimensions[TT_QUANTITY];
		static int msPixelSize[TF_QUANTITY];
		static bool msMipmapable[TF_QUANTITY];

		typedef void (*ConvertFrom)(int, const char*, Float4*);
		static ConvertFrom msConvertFrom[TF_QUANTITY];
		typedef void(*ConvertTo)(int, const Float4*, char*);
		static ConvertTo msConvertTo[TF_QUANTITY];

		public:
			static Texture* Load(const std::string& name);
			void Save(const std::string& name);
	};
	typedef Texture* TexturePtr;

}