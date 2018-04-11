#pragma once
#include "Core\CoreLib.h"
#ifdef HKR_USE_ASSERT
namespace Hikari
{
	class Assert
	{
	public:
		Assert(bool condition, const char* file, int line, const char* format,
			...);
		~Assert();
	private:
		enum
		{
			MAX_MESSAGE_BYTES = 1024
		};
		static const char* msDebugPrompt;
		static const size_t msDebugPromptLength;
		static const char* msMessagePrefix;

#ifdef HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX
		static const char* msMessageBoxTitle;
#endif
	};
}

#define assertion(condition,format,...)\
	Hikari::Assert(condition,__FILE__,__LINE__,format,__VA_ARGS__)
#else
#define assertion(condition,format,...)assert(condition)
#endif
