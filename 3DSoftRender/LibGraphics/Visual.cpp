#include "GraphicsLib.h"
#include "Visual.h"

using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Visual);
IMPLEMENT_DEFAULT_NAMES(Object, Visual);
Hikari::Visual::Visual(PrimitiveType type)
	:
	mType(type),
	mvFormat(0),
	mvBuffer(0),
	miBuffer(0),
	mEffect(0)
{
}
Hikari::Visual::Visual(PrimitiveType type, VertexFormat* vformat,VertexBuffer * vBuffer, IndexBuffer* iBuffer)
	:mvBuffer(vBuffer),
	miBuffer(iBuffer),
	mEffect(0),
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
