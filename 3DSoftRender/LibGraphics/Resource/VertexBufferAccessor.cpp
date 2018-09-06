#include "GraphicsPCH.h"
#include "VertexBufferAccessor.h"
using namespace Hikari;

VertexBufferAccessor::VertexBufferAccessor()
	: mVFormat(nullptr),
	  mVBuffer(nullptr),
	  mStride(0),
	  mData(nullptr),
	  mPosition(nullptr),
	  mNormal(nullptr),
	  mBinormal(nullptr),
	  mPositionChannel(0),
	  mNormalChannel(0),
	  mTangentChannel(0),
	  mBinormalChannel(0)
{
	int i;
	for (i = 0; i < VertexFormat::AM_MAX_COLOR_UNITS; ++i)
	{
		mColor[i] = nullptr;
		mColorChannels[i] = 0;
	}
	for (i = 0; i < VertexFormat::AM_MAX_TOORD_UNITS; ++i)
	{
		mTCoord[i] = nullptr;
		mTCoordChannels[i] = 0;
	}
}

VertexBufferAccessor::VertexBufferAccessor(VertexFormat* vformat, VertexBuffer* vbuffer)
{
	ApplyTo(vformat, vbuffer);
}

VertexBufferAccessor::VertexBufferAccessor(Visual* visual)
{
	ApplyTo(visual);
}

VertexBufferAccessor::~VertexBufferAccessor()
= default;

void VertexBufferAccessor::ApplyTo(VertexFormat* vformat, VertexBuffer* vbuffer)
{
	mVFormat = vformat;
	mVBuffer = vbuffer;
	Initialize();
}

void VertexBufferAccessor::ApplyTo(Visual* visual)
{
	mVFormat = visual->GetVertexFormat();
	mVBuffer = visual->GetVertexBuffer();
	Initialize();
}

void VertexBufferAccessor::Initialize()
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
		mPosition = nullptr;
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
		mNormal = nullptr;
		mNormalChannel = 0;
	}
	unsigned int unit = 0;

	for (unit = 0; unit < VertexFormat::AM_MAX_TOORD_UNITS; ++unit)
	{
		index = mVFormat->GetIndex(VertexFormat::AU_TEXCOORD, unit);
		if (index >= 0)
		{
			mTCoord[unit] = mData + mVFormat->GetOffset(index);
			type = (int)mVFormat->GetAttributeType(index);
			mTCoordChannels[unit] = type - baseType;
			if (mTCoordChannels[unit] > 4)
			{
				mTCoordChannels[unit] = 0;
			}
		}
		else
		{
			mTCoord[unit] = nullptr;
			mTCoordChannels[unit] = 0;
		}
	}
	for (unit = 0; unit < VertexFormat::AM_MAX_COLOR_UNITS; ++unit)
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
			mColor[unit] = nullptr;
			mColorChannels[unit] = 0;
		}
	}
}
