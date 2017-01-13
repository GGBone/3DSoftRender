#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <Windows.h>

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


//Common STL headers
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
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <D3D11.h>
#include <DXGI.h>
#include <D3Dcompiler.h>
#include <D3Dcommon.h>
#include <DirectXMath.h>


#define WINDOW_CLASS_NAME L"WIND3DCLASS"
#define WINDOW_TITLE L"T3D Games"

const int WIDTH = 640;
const int HEIGHT = 480;
const int WINDOW_X = 0;
const int WINDOW_Y = 0;
const bool SCREEN_FULLSCREEN = 0;
const bool SCREEN_WINDOWED = 1;
const int MAX_COLORS_PALETTE = 256;
const int SCREEN_BPP = 16;

const WORD BITMAP_ID = 0X4D42;
const int BITMAP_STATE_DEAD = 0;
const int BITMAP_STATE_ALIVE = 1;
const int BITMAP_ATTR_LOADED = 128;

const int BITMAP_EXTRACT_MODE_CELL = 0;
extern DWORD start_clock_count;



#define UNUSED(variable) (void)variable



#include <vector>
namespace Memory
{
	inline void MEM_SET_WORD(void* dest, USHORT data, int count)
	{
		_asm
		{
			mov edi, dest
			mov ecx, count
			mov ax, data
			rep stosw
		}
	};
	inline void Mem_Set_QUAR(void* dest, USHORT data, int count)
	{
		_asm
		{
			mov edi,dest
			mov ecx,count
			mov ax,data
			rep stosd
		}
	}

}


#endif