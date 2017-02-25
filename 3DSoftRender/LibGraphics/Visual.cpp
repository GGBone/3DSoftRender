#include "GraphicsLib.h"
#include "Visual.h"

using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Visual);
IMPLEMENT_DEFAULT_NAMES(Object, Visual);
Hikari::Visual::Visual(VertexBuffer * vBuffer, IndexBuffer* iBuffer)
	:mvBuffer(vBuffer),
	miBuffer(iBuffer),
	mType(PT_TRIANGLES)
{

}

void Hikari::Visual::UpdateWorldBound()
{
}
