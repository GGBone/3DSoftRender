#pragma once
#include "Graphics\Transform.h"

#include "Graphics\VisualEffect.h"
#include "Graphics\Renderer.h"

#include "Graphics\Dx11Shader.h"
#include "Graphics\Dx11Renderer.h"
#include "Graphics\Dx11RenderLIB.h"
#include "Graphics\Dx11Texture.h"
#ifndef FREEIMAGE_LIB
#define FREEIMAGE_LIB // Static linking
#endif
#include <FreeImage.h>
#include "Graphics\Dx11Buffer.h"
//
//#include "SoftFrameBuffer.h"
//#include "SoftPixelShader.h"
//#include "SoftRenderData.h"
//#include "SoftRenderer.h"
//#include "SoftRendererLIB.h"
//#include "SoftVertexBuffer.h"
//#include "SoftVertexShader.h"
//#include "WinSoftRenderer.h"


//Resource 
#include "Graphics\Buffer.h"
//#include "Graphics\RenderTarget.h"
#include "Graphics\Texture.h"
//#include "Texture2D.h"

#include "Graphics\Camera.h"
#include "Graphics\Spatial.h"
#include "Graphics\Visual.h"


#include "Graphics\Shader.h"



#include "Graphics\Node.h"

#ifndef ReportError
extern BOOL StringToWString(const std::string &str, std::wstring &wstr);

//wstring高字节不为0，返回FALSE
extern BOOL WStringToString(const std::wstring &wstr, std::string &str);

extern std::string ConvertString(const std::wstring& wstring);

extern void ReportErrorAndThrow(const std::string& file, int line, const std::string& function, const std::string& message);
#define ReportError(msg) ReportErrorAndThrow(__FILE__,__LINE__,__FUNCTION__,(msg)) 
#endif