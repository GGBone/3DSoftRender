#pragma once
#if defined(HKR_USE_ASSERT)
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
		static const char* ms_debug_prompt_;
		static const size_t ms_debug_prompt_length;
		static const char* ms_message_prefix_;

#ifdef HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX
		static const char* ms_message_box_title_;
#endif
	};
}

#define assertion(condition,format,...)\
	Hikari::Assert(condition,__FILE__,__LINE__,format,__VA_ARGS__)
#else
#define assertion(condition,format,...)assert(condition)
#endif
