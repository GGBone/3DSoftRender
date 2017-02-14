#include "GraphicsLib.h"
#include "Visual.h"

using namespace Hikari;
IMPLEMENT_RTTI(Hikari, Object, Visual);
IMPLEMENT_DEFAULT_NAMES(Object, Visual);
Hikari::Visual::Visual(VertexBuffer * vBuffer, VisualPass* pass)
	:mvBuffer(vBuffer),
	mPass(pass),
	mType(PT_TRIANGLES)
{

}

void Hikari::Visual::UpdateWorldBound()
{
}
