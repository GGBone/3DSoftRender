#include "GraphicsPCH.h"
#include "SceneBase.h"
using namespace Hikari;

bool Hikari::SceneBase::LoadFromFile(const std::string & fileName)
{
	return false;
}

bool Hikari::SceneBase::LoadFromString(const std::string & scene, const std::string & format)
{
	return false;
}

void Hikari::SceneBase::Render(RenderEventArgs & renderArgs)
{
}

Node * Hikari::SceneBase::GetRootNode() const
{
	return nullptr;
}

void Hikari::SceneBase::Accept(Visitor & visitor)
{
}

Hikari::SceneBase::SceneBase()
{
}

Hikari::SceneBase::~SceneBase()
{
}

void Hikari::SceneBase::ImportMaterial(const aiMaterial & material, std::string parentPath)
{
}

void Hikari::SceneBase::ImportMesh(const aiMesh & mesh)
{
}

Node * Hikari::SceneBase::ImportSceneNode(Node * parent, aiNode * aiNode)
{
	return nullptr;
}
