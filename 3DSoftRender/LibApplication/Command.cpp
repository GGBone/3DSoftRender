#include "LibApplicationPCH.h"
#include "Command.h"

#pragma disable 4996
using namespace Hikari;

char Command::msOptionNotFound[] = "option not found";
char Command::msArgumentOutofRange[] = "argument out of range";
char Command::msFilenameNotFound[] = "filename not found";
char Command::msArgumentRequired[] = "option requires an argument";
Hikari::Command::Command(int numArgument, char ** arguments)
{
	mNumArgument = numArgument;
	mCommandLine = 0;
	mUsed = 0;
	if (mNumArgument > 0)
	{
		mArguments = new char*[mNumArgument];
		for (int i = 0; i < mNumArgument; ++i)
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
	mNumArgument = 0;
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
		mNumArgument++;
		Argument* curr = new Argument(token, argList);
		argList = curr;
		token = strtok(0, " \t");
	}
	mNumArgument++;
	mArguments = new char*[mNumArgument];
	mArguments[0] = mCommandLine;
	int i = mNumArgument - 1;
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
	for (int i = 0; i < mNumArgument; i++)
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
	mMinset = true;
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
	mUsed = new bool[mNumArgument];
	memset(mUsed, false, mNumArgument * sizeof(bool));
	mSmall = 0.0f;
	mLarge = 0.0f;
	mMinset = false;
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
	for (int i = 1; i < mNumArgument; ++i)
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

int Hikari::Command::GetString(const char * name, double & value)
{
	return 0;
}

int Hikari::Command::GetFilename(char *& name)
{
	return 0;
}
