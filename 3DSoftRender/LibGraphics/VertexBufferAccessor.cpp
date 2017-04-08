#include "GraphicsPCH.h"
#include "VertexBufferAccessor.h"
using namespace Hikari;

Hikari::VertexBufferAccessor::VertexBufferAccessor()
	:mVFormat(0),
	mVBuffer(0),
	mStride(0),
	mData(0),
	mPosition(0),
	mBinormal(0),
	mNormal(0),
	mPositionChannel(0),
	mNormalChannel(0),
	mTangentChannel(0),
	mBinormalChannel(0)
{
	int i;
	for (i = 0; i < VertexFormat::AM_MAX_COLOR_UNITS; ++i)
	{
		mColor[i] = 0;
		mColorChannels[i] = 0;
	}
}

Hikari::VertexBufferAccessor::VertexBufferAccessor(VertexFormat * vformat, VertexBuffer * vbuffer)
{
	ApplyTo(vformat, vbuffer);
}

Hikari::VertexBufferAccessor::VertexBufferAccessor(Visual * visual)
{
	ApplyTo(visual);
}

Hikari::VertexBufferAccessor::~VertexBufferAccessor()
{
}

void Hikari::VertexBufferAccessor::ApplyTo(VertexFormat * vformat, VertexBuffer * vbuffer)
{
	mVFormat = vformat;
	mVBuffer = vbuffer;
	Initialize();
}

void Hikari::VertexBufferAccessor::ApplyTo(Visual * visual)
{
	mVFormat = visual->GetVertexFormat();
	mVBuffer = visual->GetVertexBuffer();
	Initialize();
	
}

void Hikari::VertexBufferAccessor::Initialize()
{
	mStride = mVFormat->GetStride();
	mData = (char*)mVBuffer->GetData();

	int baseType = (int)VertexFormat::AU_NONE;
	int type;

	int index = mVFormat->GetIndex(VertexFormat::AU_POSITION);
	if (index >= 0)
	{
		mPosition = mData + mVFormat->GetOffset(index);
		type = (int)mVFormat->GetAttributeType(index);
		mPositionChannel = type - baseType;
		if (mPositionChannel > 4)
		{
			mPositionChannel = 0;
		}
	}
	else
	{
		mPosition = 0;
		mPositionChannel = 0;
	}
	index = mVFormat->GetIndex(VertexFormat::AU_NORMAL);
	if (index >= 0)
	{
		mNormal = mData + mVFormat->GetOffset(index);
		type = (int)mVFormat->GetAttributeType(index);
		mNormalChannel = type - baseType;

		if (mNormalChannel > 4)
		{
			mNormalChannel = 0;
		}
	}
	else

	{
		mNormal = 0;
		mNormalChannel = 0;
	}

	//index = mVFormat->GetIndex(VertexFormat::AU_TANGENT);
	//if (index >= 0)
	//{
	//	mTangent = mData + mVFormat->GetOffset(index);
	//	type = (int)mVFormat->GetAttributeType(index);
	//	mTangentChannels = type - baseType;
	//	if (mTangentChannels > 4)
	//	{
	//		mTangentChannels = 0;
	//	}
	//}
	//else
	//{
	//	mTangent = 0;
	//	mTangentChannels = 0;
	//}

	//index = mVFormat->GetIndex(VertexFormat::AU_BINORMAL);
	//if (index >= 0)
	//{
	//	mBinormal = mData + mVFormat->GetOffset(index);
	//	type = (int)mVFormat->GetAttributeType(index);
	//	mBinormalChannels = type - baseType;
	//	if (mBinormalChannels > 4)
	//	{
	//		mBinormalChannels = 0;
	//	}
	//}
	//else
	//{
	//	mBinormal = 0;
	//	mBinormalChannels = 0;
	//}
	for (unsigned int unit = 0; unit < VertexFormat::AM_MAX_COLOR_UNITS; ++unit)
	{
		index = mVFormat->GetIndex(VertexFormat::AU_COLOR, unit);
		if (index >= 0)
		{
			mColor[unit] = mData + mVFormat->GetOffset(index);
			type = (int)mVFormat->GetAttributeType(index);
			mColorChannels[unit] = type - baseType;
			if (mColorChannels[unit] > 4)
			{
				mColorChannels[unit] = 0;
			}
		}
		else
		{
			mColor[unit] = 0;
			mColorChannels[unit] = 0;
		}
	}
}
