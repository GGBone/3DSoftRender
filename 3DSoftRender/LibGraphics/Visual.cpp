#include "GraphicsLib.h"
#include "Visual.h"
#include "Buffer.h"
#include "Culler.h"
#include "VertexFormat.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Visual);
IMPLEMENT_DEFAULT_NAMES(Object, Visual);
Hikari::Visual::Visual(PrimitiveType type)
	:
	mType(type),
	mvFormat(0),
	miBuffer(0),
	mEffect(0)
{
}
void Hikari::Visual::SetVertexBuffer(Buffer * buffer)
{
	mvBuffer = buffer;
}
void Hikari::Visual::SetIndexBuffer(Buffer * buffer)
{
	miBuffer = buffer;
}

Hikari::Visual::Visual(PrimitiveType type, VertexFormat* vformat)
	:mEffect(0),
	mvFormat(vformat),
	mType(type)
{

}

void Hikari::Visual::UpdateModelSpace(UpdateType type)
{
}

void Hikari::Visual::UpdateWorldBound()
{
}

void Hikari::Visual::UpdateModelBound()
{
}

void Hikari::Visual::GetVisibleSet(Culler & culler, bool noCull)
{
	culler.Insert(this);
}
