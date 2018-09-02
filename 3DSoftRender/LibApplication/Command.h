#pragma once
namespace Hikari
{
	class Command
	{
	public:
		friend class Memory;
		Command(int numArguments, char** arguments);
		Command(char* commandLine);
		~Command();


		int ExcessArguments();

		Command& Min(double value);
		Command& Max(double value);
		Command& Inf(double value);
		Command& Sup(double value);

		int GetBoolean(const char* name);
		int GetBoolean(const char* name, bool& value);
		static int GetInteger(const char* name, int& value);
		static int GetFloat(const char* name, float& value);
		static int GetDouble(const char* name, double& value);
		static int GetString(const char* name, char*& value);
		static int GetFilename(char*& name);

		static const char* GetLastError();
	protected:
		class Argument
		{
		public:
			Argument(char* item, Argument* next);
			~Argument();

			char* Item{};
			Argument* Next{};
		};

		void Initialize();

		int mNumArguments;
		char** mArguments;
		char* mCommandLine;
		bool* mUsed;


		double mSmall{};
		double mLarge{};
		bool mMinSet{};
		bool mMaxSet{};
		bool mInfSet{};
		bool mSupSet{};

		const char* mLastError{};
		static char msOptionNotFound[];
		static char msArgumentRequired[];
		static char msArgumentOutOfRange[];
		static char msFilenameNotFound[];
	};
}
