#pragma once
#include "GraphicsLib.h"
#include "Spatial.h"
#include "Culler.h"
#include "Visitor.h"

namespace Hikari
{
	class Mesh;
	class PipelineState;
	class RenderEventArgs;

	class Node : public Spatial, public std::enable_shared_from_this<Node>
	{
	DECLARE_NAMES;
	DECLARE_RTTI;
		//Create by user,it is usually used for test effect. 
	public:
		Node(const HMatrix& localTransform = HMatrix::IDENTITY);
		virtual ~Node();

		inline int GetNumChildren() const;
		const HMatrix GetLocalTransform() const;
		void SetLocalTransform(const HMatrix& matrix);

		const HMatrix GetWorldTransform() const;
		void SetWorldTransform(const HMatrix& matrix);

		const HMatrix GetInverseWorldTranform() const;


		void AttachChild(std::shared_ptr<Node> child);
		void DetachChild(std::shared_ptr<Node> child);
		void SetParent(std::shared_ptr<Node> pNode);

		void AddMesh(std::shared_ptr<Mesh> mesh);
		void RemoveMesh(std::shared_ptr<Mesh> mesh);

		void Render(RenderEventArgs& args);

		void Accept(Visitor& visitor);
	protected:
		void UpdateWorldData(double applicationTime) override;
		void UpdateWorldBound() override;
		void GetVisibleSet(Culler& culler, bool noCull) override;
		const HMatrix GetParentWorldTransform() const;
	private:
		typedef std::vector<std::shared_ptr<Node>> NodeList;
		typedef std::multimap<std::string, std::shared_ptr<Node>> NodeNameMap;
		typedef std::vector<std::shared_ptr<Mesh>> MeshList;

		std::shared_ptr<Node> m_pParent;

		NodeList m_Children{};
		NodeNameMap m_ChildrenByName{};
		MeshList m_Meshes{};
	};

	typedef Node* NodePtr;
}
