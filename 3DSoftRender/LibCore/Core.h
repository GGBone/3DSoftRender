#pragma once


#include <climits>
#include <cstdint>

//Standard library headers
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstring>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

#include <atomic>
// Common STL headers.
#include <algorithm>
#include <deque>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <Windows.h>

#include <process.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <comdef.h>
#include <CommCtrl.h> // For windows controls (progress bar)
#include <mmsystem.h> // For joystick controls
#include <memory>

#pragma comment(lib,"winmm.lib")


#include "Tuple.h"
#include "InitTerm.h"
#include "Names.h"
#include "HKRMutex.h"
#include "HKRMutexType.h"
#include "HKRScopedCS.h"
#include "HKRThread.h"

#include "Table.h"
#include "Object.h"
#include "InitTerm.h"

#include "HKRAssert.h"
#include "HKRTime.h"
