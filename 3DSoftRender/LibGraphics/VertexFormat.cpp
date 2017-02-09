#include "GraphicsPCH.h"
#include "VertexFormat.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Object, VertexFormat);
IMPLEMENT_RTTI(Hikari, Object, VertexFormat);
Hikari::VertexFormat::VertexFormat()
{
	Type = AT_NONE;
	Usage = AU_NONE;
}

Hikari::VertexFormat::~VertexFormat()
{
}

void Hikari::VertexFormat::SetAttribute(AttributeType at, AttributeUsage au)
{
	Type = at;
	Usage = au;
}

VertexFormat* Hikari::VertexFormat::Create(AttributeType at, AttributeUsage au)
{
	VertexFormat* vFormat = new VertexFormat();
	vFormat->SetAttribute(at, au);
	return vFormat;
}