#pragma once
#include "GraphicsLib.h"
#include "Spatial.h"
#include "Culler.h"

namespace Hikari
{
	class Node : public Spatial
	{
		DECLARE_NAMES;
		DECLARE_RTTI;
	public:
		Node();
		virtual ~Node();

		inline int GetNumChildren()const;

		int AttachChild(Spatial* child);

		int DetachChild(Spatial* child);

		Spatial* DetachChildAt(int i);

		Spatial* GetChild(int i);

	protected:
		virtual void UpdateWorldData(double applicationTime);
		virtual void UpdateWorldBound();
		virtual void GetVisibleSet(Culler& culler, bool noCull);

		std::vector<Spatial*> mChild;
	};
	typedef Node* NodePtr;
#include "Node.inl"
}