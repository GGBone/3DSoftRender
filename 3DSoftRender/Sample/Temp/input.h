#ifndef INPUT_H
#define INPUT_H
#include "Global.h"
#include <dinput.h>
extern HRESULT WINAPI CreateDevice();
extern HRESULT WINAPI CreateDeviceFromSettings();
extern HRESULT WINAPI SetD3D9Device();
extern HRESULT WINAPI SetD3D11Device();
extern HRESULT WINAPI IsMouseButtonDown(BYTE vButton);
extern HRESULT WINAPI WasKeyPress(BYTE vKey);

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#endif // !INPUT_H
