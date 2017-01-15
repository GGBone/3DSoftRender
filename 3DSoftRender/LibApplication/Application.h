#ifndef APPLICATION_H
#define APPLICATION_H
#include "Core.h"
#include "Command.h"

namespace Hikari
{
	class Application
	{
	protected:
		Application();
	public:
		virtual ~Application();
		static Application* TheApplication;
		
		static Command* TheCommand;
		static std::string Installpath;
		static std::string ProjectPath;

		typedef int(*EntryPoint)(int, char**);
		static EntryPoint Run;
	};
}

#endif // !APPLICATION_H
