#include "Application\LibApplicationPCH.h"

#include "Application\Command.h"
using namespace Hikari;

char Command::msOptionNotFound[] = "option not found";
char Command::msArgumentOutOfRange[] = "argument out of range";
char Command::msFilenameNotFound[] = "filename not found";
char Command::msArgumentRequired[] = "option requires an argument";
Command::Command(int numArgument, char ** arguments)
{
	mNumArguments = numArgument;
	mCommandLine = 0;
	mUsed = 0;
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
		mArguments = 0;
	}
	Initialize();
}

Hikari::Command::Command(char * commandLine)
{
	mNumArguments = 0;
	mArguments = 0;
	mCommandLine = 0;
	mUsed = 0;
	if (commandLine == 0 || strlen(commandLine) == 0)
	{
		return;
	}
	mCommandLine = new char[strlen(commandLine) + 1];
	strcpy(mCommandLine, commandLine);
	char* token = strtok(mCommandLine, " \t");
	Argument* argList = 0;

	while (tolower)
	{
		mNumArguments++;
		Argument* curr = new Argument(token, argList);
		argList = curr;
		token = strtok(0, " \t");
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

Hikari::Command::~Command()
{
}

int Hikari::Command::ExcessArguments()
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

Command & Hikari::Command::Min(double value)
{
	// TODO: 在此处插入 return 语句
	mSmall = value;
	mMinSet = true;
	return *this;
}

Command & Hikari::Command::Max(double value)
{
	// TODO: 在此处插入 return 语句
	mMaxSet = true;
	mLarge = value;
	return *this;
}

Command & Hikari::Command::Inf(double value)
{
	// TODO: 在此处插入 return 语句
	mSmall = value;
	mInfSet = true;
	return *this;
}

Command & Hikari::Command::Sup(double value)
{
	// TODO: 在此处插入 return 语句
	mLarge = value;
	mSupSet = true;
	return *this;
}

Hikari::Command::Argument::Argument(char * item, Argument * next)
{
}

Hikari::Command::Argument::~Argument()
{
}

const char * Hikari::Command::GetLastError()
{
	return nullptr;
}

void Hikari::Command::Initialize()
{
	mUsed = new bool[mNumArguments];
	memset(mUsed, false, mNumArguments * sizeof(bool));
	mSmall = 0.0f;
	mLarge = 0.0f;
	mMinSet = false;
	mMaxSet = false;
	mInfSet = false;
	mSupSet = false;

	mLastError = 0;
}

int Hikari::Command::GetBoolean(const char * name)
{
	bool value = false;
	return GetBoolean(name,value);
}

int Hikari::Command::GetBoolean(const char * name, bool & value)
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

int Hikari::Command::GetInteger(const char * name, int & value)
{
	return 0;
}

int Hikari::Command::GetFloat(const char * name, float & value)
{
	return 0;
}

int Hikari::Command::GetDouble(const char * name, double & value)
{
	return 0;
}

int Hikari::Command::GetString(const char* name, char*& value)
{
	return 0;
}

int Hikari::Command::GetFilename(char *& name)
{
	return 0;
}
