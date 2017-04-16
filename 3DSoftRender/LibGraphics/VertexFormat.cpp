//#include "GraphicsPCH.h"
//#include "VertexFormat.h"
//using namespace Hikari;
//IMPLEMENT_DEFAULT_NAMES(Object, VertexFormat);
//IMPLEMENT_RTTI(Hikari, Object, VertexFormat);
//int VertexFormat::msComponent[AT_QUANTITY] = 
//{
//	0,
//	4,
//	4,
//	4,
//	4
//};
//
//int VertexFormat::msNumComponents[AT_QUANTITY] =
//{
//	0,
//	1,
//	2,
//	3,
//	4
//};
//
//int VertexFormat::msTypeSize[AT_QUANTITY] =
//{
//	0,
//	4,
//	8,
//	12,
//	16
//};
//Hikari::VertexFormat::VertexFormat(int numAttributes)
//	:mNumAttributes(numAttributes),
//	mStride(0)
//{
//	for (int i = 0; i < AM_MAX_ATTRIBUTES; ++i)
//	{
//		mElements[i].StreamIndex = 0;
//		mElements[i].Offset = 0;
//		mElements[i].Type = AT_NONE;
//		mElements[i].Usage = AU_NONE;
//		mElements[i].UsageIndex = 0;
//	}
//}
//
//Hikari::VertexFormat::~VertexFormat()
//{
//	Renderer::UnBindAll(this);
//}
//
//VertexFormat * Hikari::VertexFormat::Create(int numAttributes, ...)
//{
//	VertexFormat* vformat = new VertexFormat(numAttributes);
//	va_list arguments;
//	va_start(arguments, numAttributes);
//	unsigned int offset = 0;
//	for (int i = 0; i < numAttributes; ++i)
//	{
//		int usage = va_arg(arguments, int);
//		int type = va_arg(arguments, int);
//		unsigned int usageIndex = va_arg(arguments, unsigned int);
//		vformat->SetAttribute(i, 0, offset,(AttributeType)type, (AttributeUsage)usage, usageIndex);
//		offset += msTypeSize[type];
//	}
//	vformat->SetStride((int)offset);
//	va_end(arguments);
//	return vformat;
//}
//
//void Hikari::VertexFormat::SetAttribute(int attribute, unsigned int streamIndex, unsigned int offset, AttributeType type, AttributeUsage usage, unsigned int usageIndex)
//{
//	Element& element = mElements[attribute];
//	element.StreamIndex = streamIndex;
//	element.Offset = offset;
//	element.Type = type;
//	element.Usage = usage;
//	element.UsageIndex = usageIndex;
//}
//
//void Hikari::VertexFormat::SetStride(int stride)
//{
//	mStride = stride;
//}
//
//
//void Hikari::VertexFormat::GetAttribute(int attribute, unsigned int & streamIndex, unsigned int & offset, AttributeType & type, AttributeUsage & usage, unsigned int & usageIndex) const
//{
//	const Element& element = mElements[attribute];
//	streamIndex = element.StreamIndex;
//	offset = element.Offset;
//	type = element.Type;
//	usage = element.Usage;
//	usageIndex = element.UsageIndex;
//}
//
//
//int Hikari::VertexFormat::GetIndex(AttributeUsage usage, unsigned int usageIndex) const
//{
//	for (int i = 0; i < mNumAttributes; ++i)
//	{
//		if (mElements[i].Usage == usage &&
//			mElements[i].UsageIndex == usageIndex)
//			return i;
//	}
//	return -1;
//}
//
