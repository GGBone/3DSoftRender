#include "LibApplicationPCH.h"
#include "Application.h"

using namespace Hikari;

Application* Application::TheApplication = nullptr;
Command* Application::TheCommand = nullptr;
std::string Application::Installpath;
std::string Application::ProjectPath;
Application::EntryPoint Application::Run = nullptr;

Application::Application()
= default;

Application::~Application()
= default;

int main(int numArguments, char* arguments[])
{
	//To-Do
	//Memory::Initialize();

	Application::Installpath = ".";

	if (Application::Installpath == "")
	{
		//Error
		std::ofstream outFile("ApplicationError.txt");
		if (outFile)
		{
			outFile << "Please set the Path \n";
			outFile.close();
		}
		return INT_MAX;
	}
	Application::Installpath += "/";
	InitTerm::ExecuteInitializers();

	std::string directory;
	//Envernment::....

	Application::TheCommand = new Command(numArguments, arguments);
	int exitCode = Application::Run(numArguments, arguments);

	delete (Application::TheCommand);

	//Enviroment
	InitTerm::ExecuteTerminators();
	//Memory::Terminator();

	return exitCode;
}
