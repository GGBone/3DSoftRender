#pragma once
namespace Hikari
{
	class Command
	{
	public:
		friend class Memory;
		Command(int numArgument, char** arguments);
		Command(char* commandLine);
		~Command();
		int ExcessArguments();

		Command& Min(double value);
		Command& Max(double value);
		Command& Inf(double value);
		Command& Sup(double value);

		int GetBoolean(const char* name);
		int GetBoolean(const char* name, bool& value);
		int GetInteger(const char* name, int& value);
		int GetFloat(const char* name, float& value);
		int GetDouble(const char* name, double& value);
		int GetString(const char* name, double& value);
		int GetFilename(char*& name);

		const char* GetLastError();

	protected:
		class Argument
		{
		public:
			Argument(char* item, Argument* next);
			~Argument();
			char* Item;
			Argument* Next;
		};
		void Initialize();
		int mNumArgument;
		char** mArguments;
		char* mCommandLine;
		bool* mUsed;

		double mSmall;
		double mLarge;
		bool mMinset;
		bool mMaxSet;
		bool mInfSet;
		bool mSupSet;


		const char* mLastError;
		static char* msOptionNotFound[];
		static char* msArgumentRequired[];
		static char* msArgumentOutofRange[];
		static char* msFilenameNotFound[];
	};
}