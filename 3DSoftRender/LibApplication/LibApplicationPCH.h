#pragma once

#include "Application.h"
#include "ConsoleApplication.h"
#include "WindowApplicationBase.h"
#include "WindowApplicationSoft.h"
#include "WindowApplicationEngine.h"


#ifndef ReportError
extern BOOL StringToWString(const std::string& str, std::wstring& wstr);

//wstring高字节不为0，返回FALSE
extern BOOL WStringToString(const std::wstring& wstr, std::string& str);

extern std::string ConvertString(const std::wstring& wstring);

extern void ReportErrorAndThrow(const std::string& file, int line, const std::string& function,
                                const std::string& message);
#define ReportError(msg) ReportErrorAndThrow(__FILE__,__LINE__,__FUNCTION__,(msg))
#endif
