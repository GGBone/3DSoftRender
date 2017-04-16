#include "GraphicsPCH.h"
#include "Node.h"
#include "Mesh.h"
#include "Visitor.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Spatial, Node);
IMPLEMENT_RTTI(Hikari, Spatial, Node);
Hikari::Node::Node(const HMatrix& localTransform)
{
	this->localTransform.SetMatrix(localTransform);
}

Hikari::Node::~Node()
{
}

inline int Hikari::Node::GetNumChildren() const
{
	return m_Children.size();
}

const std::string & Hikari::Node::GetName() const
{
	return m_Name;
}

const HMatrix& Hikari::Node::GetLocalTransform() const
{
	return localTransform.GetMatrix();
}

void Hikari::Node::SetLocalTransform(const HMatrix & matrix)
{
	localTransform.SetMatrix(matrix);
	inverseTransform.SetMatrix(matrix.Inverse());
}

const HMatrix& Hikari::Node::GetWorldTransform() const
{
	return GetWorldTransform() * localTransform.GetMatrix();
}

void Hikari::Node::SetWorldTransform(const HMatrix & matrix)
{
	HMatrix _inverseParentTranform = GetParentWorldTransform().Inverse();
	SetLocalTransform(_inverseParentTranform);
}

const HMatrix& Hikari::Node::GetInverseWorldTranform() const
{
	return GetWorldTransform().Inverse();
}

void Hikari::Node::AttachChild(Node * child)
{
	if (child)
	{
		NodeList::iterator iter = std::find(m_Children.begin(), m_Children.end(), child);
		if (iter == m_Children.end())
		{
			child->GetWorldTransform();
			m_Children.push_back(child);
		}
	}
}

void Hikari::Node::DetachChild(Node * pNode)
{
	if (pNode)
	{
		NodeList::iterator iter = std::find(m_Children.begin(), m_Children.end(), pNode);
		if (iter != m_Children.end())
		{
			pNode->SetParent(nullptr);

			m_Children.erase(iter);

			// Also remove it from the name map.
			NodeNameMap::iterator iter2 = m_ChildrenByName.find(pNode->GetName());
			if (iter2 != m_ChildrenByName.end())
			{
				m_ChildrenByName.erase(iter2);
			}
		}
		else
		{
			// Maybe this node appears lower in the hierarchy...
			for (auto child : m_Children)
			{
				child->DetachChild(pNode);
			}
		}
	}
}

void Hikari::Node::SetParent(Node * pNode)
{
	if (pNode == nullptr)
		mParent = pNode;
	else
		pNode->AttachChild(this);

}

void Hikari::Node::AddMesh(Mesh * mesh)
{
	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
	if (iter == m_Meshes.end())
		m_Meshes.push_back(mesh);
}

void Hikari::Node::RemoveMesh(Mesh * mesh)
{
	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
	if (iter != m_Meshes.end())
	{
		m_Meshes.erase(iter);
	}
}

void Hikari::Node::Render(RenderEventArgs& args)
{
	for (auto mesh : m_Meshes)
	{
		mesh->Render(args);
	}
	for (auto child : m_Children)
	{
		child->Render(args);
	}
}

void Hikari::Node::UpdateWorldData(double applicationTime)
{
	
}

void Hikari::Node::UpdateWorldBound()
{
}

void Hikari::Node::GetVisibleSet(Culler & culler, bool noCull)
{
	
}

const HMatrix& Node::GetParentWorldTransform() const
{
	return m_pParent->GetWorldTransform();
}

void Node::Accept(Visitor& visitor)
{
	visitor.Visit(*this);
	
	// Visit meshes.
	for (auto mesh : m_Meshes)
	{
		mesh->Accept(visitor);
	}

	// Now visit children
	for (auto child : m_Children)
	{
		child->Accept(visitor);
	}
}
