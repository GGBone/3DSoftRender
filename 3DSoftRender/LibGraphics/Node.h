#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\Spatial.h"
#include "Graphics\Culler.h"
#include "Graphics\Visitor.h"
namespace Hikari
{
	class Mesh;
	class PipelineState;
	class RenderEventArgs;
	class Node : public Spatial,public std::enable_shared_from_this<Node>
	{
		DECLARE_NAMES;
		DECLARE_RTTI;
		//Create by user,it is usually used for test effect. 
	public:
		Node(const HMatrix& localTransform = HMatrix::IDENTITY);
		virtual ~Node();

		inline int GetNumChildren()const;
		const std::string& GetName() const;
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
		virtual void UpdateWorldData(double applicationTime);
		virtual void UpdateWorldBound();
		virtual void GetVisibleSet(Culler& culler, bool noCull);
		const HMatrix GetParentWorldTransform() const;
	private:
		typedef std::vector<std::shared_ptr<Node>> NodeList;
		typedef std::multimap<std::string, std::shared_ptr<Node>> NodeNameMap;
		typedef std::vector<std::shared_ptr<Mesh>> MeshList;

		std::string m_Name;
		
		std::shared_ptr<Node> m_pParent;

		NodeList m_Children;
		NodeNameMap m_ChildrenByName;
		MeshList m_Meshes;
	};
	typedef Node* NodePtr;
}