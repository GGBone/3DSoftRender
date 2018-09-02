#include "CorePCH.h"
#include "HKRAssert.h"

#ifdef HKR_USE_ASSERT

#ifdef HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
#include <windows.h>
#endif

#ifdef HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
#include <intrin.h>
#endif

using namespace Hikari;

const char* Assert::ms_debug_prompt_ = "Do you want to enable debugger?";
const size_t Assert::ms_debug_prompt_length = strnlen_s(Assert::ms_debug_prompt_,1024);
const char* Assert::ms_message_prefix_ = "\nAssert failed at %s(%d):\n";
#ifdef HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX
const char* Assert::ms_message_box_title_ = "Assert Failed";

#endif
Assert::Assert(bool condition, const char * file, int line, const char * format, ...)
{
	if (condition)
		return;
	char message[MAX_MESSAGE_BYTES];
	const auto max_prefix_bytes = MAX_MESSAGE_BYTES - ms_debug_prompt_length - 1;
	_snprintf_s(message, max_prefix_bytes, max_prefix_bytes,ms_message_prefix_, file, line);

	va_list arguments;
	va_start(arguments, format);
	const auto length = strlen(message);
	_vsnprintf_s(message + length, max_prefix_bytes - length, max_prefix_bytes - length,format, arguments);
	va_end(arguments);

#ifdef HKR_USE_ASSERT_LOG_TO_FILE
	FILE* logFile = fopen(msLogFileName, "at");
	if (logFile)
	{
		fprintf(logFile, message);
	}
	fclose(logFile);
#endif

#ifdef HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
	OutputDebugStringA(message);
#endif

#ifdef HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX
	strcat_s(message, ms_debug_prompt_);
	const auto selection = ::MessageBoxA(nullptr, message, ms_message_box_title_,
		MB_ICONERROR | MB_YESNOCANCEL | MB_APPLMODAL | MB_TOPMOST);
	switch (selection)
	{
	case IDYES:
		__debugbreak();
		break;
	case IDNO:
		break;
	case IDCANCEL:
	default:
		exit(0);
		break;

	}
#endif

}
Hikari::Assert::~Assert()
{
}
#endif
