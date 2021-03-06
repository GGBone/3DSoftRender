#pragma once
#include "Core.h"
#include "ReadDirectoryChanges.h"
#include "Command.h"

namespace Hikari
{
	class Application : public Object
	{
	protected:
		Application();
	public:
		virtual ~Application();
		static Application* TheApplication;

		static Command* TheCommand;
		static std::string Installpath;
		static std::string ProjectPath;

		typedef int (*EntryPoint)(int, char**);
		static EntryPoint Run;
	};
}
