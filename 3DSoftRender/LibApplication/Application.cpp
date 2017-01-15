#include "LibApplicationPCH.h"
#include "Application.h"

using namespace Hikari;

Application* Application::TheApplication = 0;
Command* Application::TheCommand = 0;
std::string Application::Installpath;
std::string Application::ProjectPath;
Application::EntryPoint Application::Run = 0;

Application::Application()
{

}
Application::~Application()
{

}
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
			outFile << "Please Set the Path \n";
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