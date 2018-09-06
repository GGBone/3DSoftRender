#include "GraphicsPCH.h"
#include "Node.h"
#include "Mesh.h"
#include "Visitor.h"
using namespace Hikari;
IMPLEMENT_DEFAULT_NAMES(Spatial, Node);
IMPLEMENT_RTTI(Hikari, Spatial, Node);

Node::Node(const HMatrix& localTransform)
	: m_pParent(nullptr)
{
	this->localTransform.SetMatrix(localTransform);
}

Node::~Node()
= default;

inline int Node::GetNumChildren() const
{
	return m_Children.size();
}

const std::string& Node::GetName() const
{
	return m_Name;
}

const HMatrix Node::GetLocalTransform() const
{
	return localTransform.GetMatrix();
}

void Node::SetLocalTransform(const HMatrix& matrix)
{
	localTransform.SetMatrix(matrix);
	inverseTransform.SetMatrix(matrix.Inverse());
}

const HMatrix Node::GetWorldTransform() const
{
	return GetParentWorldTransform() * localTransform.GetMatrix();
}

void Node::SetWorldTransform(const HMatrix& matrix)
{
	HMatrix _inverseParentTranform = GetParentWorldTransform().Inverse();
	SetLocalTransform(_inverseParentTranform);
}

const HMatrix Node::GetInverseWorldTranform() const
{
	return GetParentWorldTransform().Inverse();
}

void Node::AttachChild(std::shared_ptr<Node> child)
{
	if (child)
	{
		NodeList::iterator iter = std::find(m_Children.begin(), m_Children.end(), child);
		if (iter == m_Children.end())
		{
			HMatrix worldTransform = child->GetWorldTransform();

			child->m_pParent = shared_from_this();
			HMatrix localTransform = GetInverseWorldTranform();
			child->SetLocalTransform(localTransform);
			m_Children.push_back(child);
			if (!child->GetName().empty())
			{
				m_ChildrenByName.insert(NodeNameMap::value_type(child->GetName(), child));
			}
		}
	}
}

void Node::DetachChild(std::shared_ptr<Node> pNode)
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

void Node::SetParent(std::shared_ptr<Node> pNode)
{
	if (pNode != nullptr)
		pNode->AttachChild(shared_from_this());
	else if (m_pParent != nullptr)
	{
		m_pParent = pNode;
		HMatrix worldTransform = GetWorldTransform();
		m_pParent->DetachChild(shared_from_this());
		m_pParent = nullptr;
		SetLocalTransform(worldTransform);
	}
}

void Node::AddMesh(std::shared_ptr<Mesh> mesh)
{
	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
	if (iter == m_Meshes.end())
		m_Meshes.push_back(mesh);
}

void Node::RemoveMesh(std::shared_ptr<Mesh> mesh)
{
	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), mesh);
	if (iter != m_Meshes.end())
	{
		m_Meshes.erase(iter);
	}
}

void Node::Render(RenderEventArgs& args)
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

void Node::UpdateWorldData(double applicationTime)
{
}

void Node::UpdateWorldBound()
{
}

void Node::GetVisibleSet(Culler& culler, bool noCull)
{
}

const HMatrix Node::GetParentWorldTransform() const
{
	if (m_pParent == nullptr)
		return HMatrix::IDENTITY;
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
