#include "GraphicsPCH.h"
#include "Texture2D.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Texture, Texture2D);
IMPLEMENT_RTTI(Hikari, Texture, Texture2D);
Hikari::Texture2D::Texture2D(Format tformat, int dimension0, int dimension1, int numLevels, Buffer::Usage usage)
	:
	Texture(tformat,Texture::Type::TT_2D,usage,numLevels)
{
}

Hikari::Texture2D::~Texture2D()
{
}
