#include "Core\CorePCH.h"
#include "Core\HKRAssert.h"

#ifdef HKR_USE_ASSERT

#ifdef HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
#include <windows.h>
#endif

#ifdef HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
#include <intrin.h>
#endif

using namespace Hikari;

const char* Assert::msDebugPrompt = "Do you want to enable debugger?";
const size_t Assert::msDebugPromptLength = strnlen_s(Assert::msDebugPrompt,1024);
const char* Assert::msMessagePrefix = "\nAssert failed at %s(%d):\n";
#ifdef HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX
const char* Assert::msMessageBoxTitle = "Assert Failed";

#endif
Assert::Assert(bool condition, const char * file, int line, const char * format, ...)
{
	if (condition)
		return;
	char message[MAX_MESSAGE_BYTES];
	const size_t maxPrefixBytes = MAX_MESSAGE_BYTES - msDebugPromptLength - 1;
	_snprintf_s(message, maxPrefixBytes, maxPrefixBytes,msMessagePrefix, file, line);

	va_list arguments;
	va_start(arguments, format);
	size_t length = strlen(message);
	_vsnprintf_s(message + length, maxPrefixBytes - length, maxPrefixBytes - length,format, arguments);
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
	strcat_s(message, msDebugPrompt);
	int selection = ::MessageBoxA(0, message, msMessageBoxTitle,
		MB_ICONERROR | MB_YESNOCANCEL | MB_APPLMODAL | MB_TOPMOST);
	switch (selection)
	{
	case IDYES:
		__debugbreak;
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


