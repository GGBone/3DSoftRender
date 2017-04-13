#pragma once
namespace Hikari
{

#include "Object.h"

	class Scene;
	class Node;
	class Mesh;

	class Visitor : public Object
	{
	public:
		virtual void Visit(Scene& scene) = 0;
		virtual void Visit(Node& node) = 0;
		virtual void Visit(Mesh& mesh) = 0;
	};
}