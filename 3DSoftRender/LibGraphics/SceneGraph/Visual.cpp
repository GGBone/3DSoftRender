#include "GraphicsPCH.h"
#include "Visual.h"
#include "Culler.h"
using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Visual);
IMPLEMENT_DEFAULT_NAMES(Object, Visual);

Visual::Visual(PrimitiveType type)
	:
	mType(type),
	miBuffer(nullptr),
	mvFormat(nullptr),
	mEffect(nullptr)
{
}

void Visual::SetVertexBuffer(Buffer* buffer)
{
	mvBuffer = buffer;
}

void Visual::SetIndexBuffer(Buffer* buffer)
{
	miBuffer = buffer;
}

Visual::Visual(PrimitiveType type, VertexFormat* vformat)
	: mType(type),
	  mvFormat(vformat),
	  mEffect(nullptr)
{
}

void Visual::UpdateModelSpace(UpdateType type)
{
}

void Visual::UpdateWorldBound()
{
}

void Visual::UpdateModelBound()
{
}

void Visual::GetVisibleSet(Culler& culler, bool noCull)
{
	culler.Insert(this);
}
