#include "GraphicsPCH.h"
#include "Texture.h"

using namespace Hikari;

IMPLEMENT_DEFAULT_NAMES(Object,Texture);
IMPLEMENT_RTTI(Hikari, Object, Texture);
Hikari::Texture::~Texture()
{

}
Texture * Hikari::Texture::Load(const std::string & name)
{
	return nullptr;
}
void Hikari::Texture::Save(const std::string & name)
{
}

Hikari::Texture::Texture(Format tformat, Type type, Buffer::Usage usage, int numLevels)
{
	mFormat = tformat;
	mType = type;
	mUsage = usage;
	mNumLevels = numLevels;
}