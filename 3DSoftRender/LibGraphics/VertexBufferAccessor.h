#pragma once
#include "Graphics\GraphicsLib.h"
#include "APoint.h"
#include "VertexFormat.h"

namespace Hikari

{
	class Visual;
	class VertexBufferAccessor
	{
	public:
		VertexBufferAccessor();
		VertexBufferAccessor(VertexFormat* vformat, Buffer* vbuffer);
		VertexBufferAccessor(Visual* visual);
		~VertexBufferAccessor();

		void ApplyTo(VertexFormat* vformat, Buffer* vbuffer);
		void ApplyTo(Visual* visual);
		inline char* GetData()const;
		inline int GetNumVertices()const;
		inline int GetStride()const;

		template<typename T>
		inline T& Position(int i);
		inline bool HasPosition()const;
		inline int GetPositionChannels()const;
		inline float* PositionTuple(int i);
		
		template<typename T>
		inline T& Normal(int i)const;
		inline bool HasNormal()const;
		inline int GetNormalChannels()const;
		inline float* NormalTuple(int i);


		template<typename T>
		inline T& Tangent()const;
		inline bool HasTangent()const;
		inline int GetTangentChannels()const;
		inline float* TangentTuple(int i);
		
		template <typename T>
		inline T& Binormal(int i);
		inline bool HasBinormal() const;
		inline int GetBinormalChannels() const;
		inline float* BinormalTuple(int i);

		template <typename T>
		inline T& TCoord(int unit, int i);
		inline bool HasTCoord(int unit) const;
		inline int GetTCoordChannels(int unit) const;
		inline float* TCoordTuple(int unit, int i);

		template <typename T>
		inline T& Color(int unit, int i);
		inline bool HasColor(int unit) const;
		inline int GetColorChannels(int unit) const;
		inline float* ColorTuple(int unit, int i);

	private:
		void Initialize();
		VertexFormat* mVFormat;
		Buffer* mVBuffer;
		int mStride;
		char* mData;

		char* mPosition;
		char* mNormal;
		char* mTanget;
		char* mBinormal;
		
		char* mColor[VertexFormat::AM_MAX_COLOR_UNITS];
		char* mTCoord[VertexFormat::AM_MAX_COLOR_UNITS];
		int mPositionChannel;
		int mNormalChannel;
		int mTangentChannel;
		int mBinormalChannel;
		int mTCoordChannels[VertexFormat::AM_MAX_TOORD_UNITS];
		int mColorChannels[VertexFormat::AM_MAX_COLOR_UNITS];
	};
	template<typename T>
	inline T & VertexBufferAccessor::Position(int i)
	{
		return *(T*)(mPosition + i * mStride);
	}
	template<typename T>
	inline T & VertexBufferAccessor::Normal(int i) const
	{
		return *(T*)(mNormal + i * mStride);
	}
	template<typename T>
	inline T & VertexBufferAccessor::Tangent() const
	{
		return *(T*)(mTanget + i * mStride);
	}
	template<typename T>
	inline T & VertexBufferAccessor::Binormal(int i)
	{
		return *(T*)(mBinormal + i * mStride);
	}
	template<typename T>
	inline T & VertexBufferAccessor::TCoord(int unit, int i)
	{
		return *(T*)(mTCoord[unit] + i*mStride);
	}
	template<typename T>
	inline T & VertexBufferAccessor::Color(int unit, int i)
	{
		return *(T*)(mColor[unit] + i * mStride);
	}
	inline int Hikari::VertexBufferAccessor::GetNumVertices() const
	{
		return mVBuffer->GetElementCount();
	}



	inline char * Hikari::VertexBufferAccessor::GetData() const
	{
		return mData;
	}

	inline int Hikari::VertexBufferAccessor::GetStride() const
	{
		return mStride;
	}

	inline bool Hikari::VertexBufferAccessor::HasPosition() const
	{
		return mPosition != 0;
	}

	inline int Hikari::VertexBufferAccessor::GetPositionChannels() const
	{
		return mPositionChannel;
	}

	inline float * Hikari::VertexBufferAccessor::PositionTuple(int i)
	{
		return (float*)(mPosition + i*mStride);
	}

	inline bool Hikari::VertexBufferAccessor::HasNormal() const
	{
		return mNormal != 0;
	}

	inline int Hikari::VertexBufferAccessor::GetNormalChannels() const
	{
		return mNormalChannel;
	}

	inline float * Hikari::VertexBufferAccessor::NormalTuple(int i)
	{
		return (float*)(mNormal + i*mStride);
	}

	inline bool Hikari::VertexBufferAccessor::HasTangent() const
	{
		return mTanget != 0;
	}

	inline int Hikari::VertexBufferAccessor::GetTangentChannels() const
	{
		return mTangentChannel;
	}

	inline float * Hikari::VertexBufferAccessor::TangentTuple(int i)
	{
		return (float*)(mTanget + i*mStride);
	}


	inline bool Hikari::VertexBufferAccessor::HasColor(int unit) const
	{
		return mColor[unit] != 0;

	}

	inline int Hikari::VertexBufferAccessor::GetColorChannels(int unit) const
	{
		return mColorChannels[unit];
	}

	inline float * Hikari::VertexBufferAccessor::ColorTuple(int unit, int i)
	{
		return (float*)(mColor[unit] + i* mStride);
	}
}