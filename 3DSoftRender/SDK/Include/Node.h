#pragma once
#include "GraphicsLib.h"
#include "Spatial.h"
#include "Culler.h"

namespace Hikari
{
	class Mesh;
	class PipelineState;
	class RenderEventArgs;
	class Visitor;
	class Node : public Spatial
	{
		DECLARE_NAMES;
		DECLARE_RTTI;
	public:
		Node(const HMatrix& localTransform = HMatrix::IDENTITY);
		virtual ~Node();

		inline int GetNumChildren()const;
		const std::string& GetName() const;
		const HMatrix& GetLocalTransform() const;
		void SetLocalTransform(const HMatrix& matrix);

		const HMatrix& GetWorldTransform() const;
		void SetWorldTransform(const HMatrix& matrix);

		const HMatrix& GetInverseWorldTranform() const;


		void AttachChild(Node* child);
		void DetachChild(Node* child);
		void SetParent(Node* pNode);

		void AddMesh(Mesh* mesh);
		void RemoveMesh(Mesh* mesh);

		void Render(RenderEventArgs& args);

		void Accept(Visitor& visitor);
	protected:
		virtual void UpdateWorldData(double applicationTime);
		virtual void UpdateWorldBound();
		virtual void GetVisibleSet(Culler& culler, bool noCull);
		const HMatrix& GetParentWorldTransform() const;
	private:
		typedef std::vector<Node*> NodeList;
		typedef std::multimap<std::string, Node*> NodeNameMap;
		typedef std::vector<Mesh*> MeshList;

		std::string m_Name;
		
		Node* m_pParent;

		NodeList m_Children;
		NodeNameMap m_ChildrenByName;
		MeshList m_Meshes;
	};
	typedef Node* NodePtr;
#include "Node.inl"
}