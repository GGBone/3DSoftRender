#pragma once

#include "Object.h"

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
		
		virtual bool LoadFromFile(const std::wstring& fileName) = 0;
	
		virtual bool LoadFromString(const std::string& scene, const std::string& format) = 0;


		virtual void Render(RenderEventArgs& renderEventArgs) = 0;

		virtual Node* GetRootNode() const = 0;

		virtual void Accept(Visitor& visitor) = 0;
	};
}
