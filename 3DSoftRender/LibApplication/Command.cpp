#include "LibApplicationPCH.h"

#include "Command.h"
using namespace Hikari;

char Command::msOptionNotFound[] = "option not found";
char Command::msArgumentOutOfRange[] = "argument out of range";
char Command::msFilenameNotFound[] = "filename not found";
char Command::msArgumentRequired[] = "option requires an argument";

Command::Command(int numArgument, char** arguments)
{
	mNumArguments = numArgument;
	mCommandLine = nullptr;
	mUsed = nullptr;
	if (mNumArguments > 0)
	{
		mArguments = new char*[mNumArguments];
		for (int i = 0; i < mNumArguments; ++i)
		{
			mArguments[i] = arguments[i];
		}
	}
	else
	{
		mArguments = nullptr;
	}
	Initialize();
}

Command::Command(char* commandLine)
{
	mNumArguments = 0;
	mArguments = nullptr;
	mCommandLine = nullptr;
	mUsed = nullptr;
	if (commandLine == nullptr || strlen(commandLine) == 0)
	{
		return;
	}
	mCommandLine = new char[strlen(commandLine) + 1];
	strcpy(mCommandLine, commandLine);
	char* token = strtok(mCommandLine, " \t");
	Argument* argList = nullptr;

	while (token)
	{
		mNumArguments++;
		Argument* curr = new Argument(token, argList);
		argList = curr;
		token = strtok(nullptr, " \t");
	}
	mNumArguments++;
	mArguments = new char*[mNumArguments];
	mArguments[0] = mCommandLine;
	int i = mNumArguments - 1;
	while (argList)
	{
		mArguments[i--] = argList->Item;
		Argument* save = argList->Next;
		delete argList->Next;
		argList = save;
	}
	Initialize();
}

Command::~Command()
= default;

int Command::ExcessArguments()
{
	for (int i = 0; i < mNumArguments; i++)
	{
		if (!mUsed)
		{
			return i;
		}
	}
	return 0;
}

Command& Command::Min(double value)
{
	// TODO: 在此处插入 return 语句
	mSmall = value;
	mMinSet = true;
	return *this;
}

Command& Command::Max(double value)
{
	// TODO: 在此处插入 return 语句
	mMaxSet = true;
	mLarge = value;
	return *this;
}

Command& Command::Inf(double value)
{
	// TODO: 在此处插入 return 语句
	mSmall = value;
	mInfSet = true;
	return *this;
}

Command& Command::Sup(double value)
{
	// TODO: 在此处插入 return 语句
	mLarge = value;
	mSupSet = true;
	return *this;
}

Command::Argument::Argument(char* item, Argument* next)
{
}

Command::Argument::~Argument()
= default;

const char* Command::GetLastError()
{
	return nullptr;
}

void Command::Initialize()
{
	mUsed = new bool[mNumArguments];
	memset(mUsed, false, mNumArguments * sizeof(bool));
	mSmall = 0.0f;
	mLarge = 0.0f;
	mMinSet = false;
	mMaxSet = false;
	mInfSet = false;
	mSupSet = false;

	mLastError = nullptr;
}

int Command::GetBoolean(const char* name)
{
	bool value = false;
	return GetBoolean(name, value);
}

int Command::GetBoolean(const char* name, bool& value)
{
	int matchFount = 0;
	value = false;
	for (int i = 1; i < mNumArguments; ++i)
	{
		char* tmp = mArguments[i];
		if (!mUsed[i] && tmp[0] == '-' && strcmp(name, ++tmp) == 0)
		{
			mUsed[i] = true;
			matchFount = i;
			value = true;
			break;
		}
	}
	if (matchFount == 0)
	{
		mLastError = msOptionNotFound;
	}
	return matchFount;
}

int Command::GetInteger(const char* name, int& value)
{
	return 0;
}

int Command::GetFloat(const char* name, float& value)
{
	return 0;
}

int Command::GetDouble(const char* name, double& value)
{
	return 0;
}

int Command::GetString(const char* name, char*& value)
{
	return 0;
}

int Command::GetFilename(char*& name)
{
	return 0;
}
