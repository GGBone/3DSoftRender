#pragma once
#include "Core.h"
//#define ENABLE_DX_RENDERER
//#include "Renderer/DxRenderer/Dx11Renderer.h"
//
//#include "Renderer/DxRenderer/Dx11Shader.h"
//#include "Renderer/DxRenderer/Dx11RenderLIB.h"
//#include "Renderer/DxRenderer/Dx11Texture.h"
//#include "Renderer/DxRenderer/Dx11Buffer.h"
//#include "Renderer/DxRenderer/Dx11ShaderParameter.h"
//#undef ENABLE_DX_RENDERER
//
//#define ENABLE_SOFT_RENDERER
////
////#include "SoftFrameBuffer.h"
////#include "SoftPixelShader.h"
////#include "SoftRenderData.h"
////#include "SoftRenderer.h"
////#include "SoftRendererLIB.h"
////#include "SoftVertexBuffer.h"
////#include "SoftVertexShader.h"
////#include "WinSoftRenderer.h"
//
//#undef ENABLE_SOFT_RENDERER
//
//#define ENABLE_SCENE_GRAPH
//#include "SceneGraph/Camera.h"
//#include "SceneGraph/Spatial.h"
//#include "SceneGrapH/Visual.h"
//#include "SceneGraph/Node.h"
//#include "SceneGraph/VisualEffectInstance.h"
//#undef ENABLE_SCENE_GRAPH
//
//#define ENABLE_RENDER_RESOURCE
//Resource 
#include "Resource/BufferBinding.h"
#include "Resource/Buffer.h"
#include "Resource/RenderTarget.h"
#include "Resource/Texture.h"
#include "Resource/PipelineState.h"
#include "Resource/BufferBase.h"


//
//#define ENABLE_SHADER
#include "Shader/Shader.h"
#include "Shader/ShaderParameter.h"
//#undef ENABLE_SHADER

#ifndef ReportError
extern bool StringToWString(const std::string& str, std::wstring& wstr);

//wstring高字节不为0，返回FALSE
extern bool WStringToString(const std::wstring& wstr, std::string& str);

extern std::string ConvertString(const std::wstring& wstring);

extern void ReportErrorAndThrow(const std::string& file, int line, const std::string& function,
                                const std::string& message);
#define ReportError(msg) ReportErrorAndThrow(__FILE__,__LINE__,__FUNCTION__,(msg))
#endif
