#pragma once
#include "Core\Object.h"
#include "Core\Event.h"
namespace Hikari
{

	class Node;
	class Camera;
	class RenderEventArgs;
	class Visitor;
	class Buffer;
	class Scene : public Object
	{
	public:
		
		//Loaded by Assimp,cant attach any scene created by Node class.

		virtual bool LoadFromFile(const std::wstring& fileName) = 0;
	
		virtual bool LoadFromString(const std::string& scene, const std::string& format) = 0;


		virtual void Render(RenderEventArgs& renderEventArgs) = 0;

		virtual std::shared_ptr<Node> GetRootNode()  = 0;

		virtual void Accept(Visitor& visitor) = 0;

		ProgressEvent LoadingProgress;
	protected:
		 virtual void OnLoadingProgress(ProgressEventArgs& e);
	};
}
