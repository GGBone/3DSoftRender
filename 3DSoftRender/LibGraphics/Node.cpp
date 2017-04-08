#include "GraphicsPCH.h"
#include "Node.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Spatial, Node);
IMPLEMENT_RTTI(Hikari, Spatial, Node);
Hikari::Node::Node()
{
}

Hikari::Node::~Node()
{
}

inline int Hikari::Node::GetNumChildren() const
{
	return mChild.size();
}

int Hikari::Node::AttachChild(Spatial * child)
{
	if (!child)
		return -1;
	if (child->GetParent())
		return -1;

	child->SetParent(this);
	std::vector<SpatialPtr>::iterator iter = mChild.begin();
	std::vector<SpatialPtr>::iterator end = mChild.end();

	for (int i = 0; iter != end; ++iter, ++i)
	{
		if (*iter == 0)
		{
			*iter = child;
			return i;
		}
	}
	const int numChildren = (int)mChild.size();
	mChild.push_back(child);
	return numChildren;
}

int Hikari::Node::DetachChild(Spatial * child)
{
	if (child)
	{
		std::vector<SpatialPtr>::iterator iter = mChild.begin();
		std::vector<SpatialPtr>::iterator end = mChild.end();
		for (int i = 0; iter != end; ++iter, ++i)
		{
			if (*iter == child)
			{
				(*iter)->SetParent(0);
				*iter = 0;
				return i;
			}
		}
	}
	return -1;
}

Spatial * Hikari::Node::DetachChildAt(int i)
{
	if (0 <= i && i < (int)mChild.size())
	{
		SpatialPtr child = mChild[i];
		if (child)
		{
			child->SetParent(0);
			mChild[i] = 0;
		}
		return child;
	}
	return 0;
}

Spatial * Hikari::Node::GetChild(int i)
{
	if (0 <= i && i < (int)mChild.size())
	{
		return mChild[i];
	}
	return 0;
}

void Hikari::Node::UpdateWorldData(double applicationTime)
{
	Spatial::UpdateWorldData(applicationTime);

	std::vector<SpatialPtr>::iterator iter = mChild.begin();
	std::vector<SpatialPtr>::iterator end = mChild.end();
	for (/**/; iter != end; ++iter)
	{
		Spatial* child = *iter;
		if (child)
		{
			child->Update(applicationTime, false);
		}
	}
}

void Hikari::Node::UpdateWorldBound()
{
}

void Hikari::Node::GetVisibleSet(Culler & culler, bool noCull)
{
	std::vector<SpatialPtr>::iterator iter = mChild.begin();
	std::vector<SpatialPtr>::iterator end = mChild.end();
	for (/**/; iter != end; ++iter)
	{
		Spatial* child = *iter;
		if (child)
		{
			child->OnGetVisibleSet(culler, noCull);
		}
	}
}
