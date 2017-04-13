#pragma once
#include "Object.h"
#include "Dx11RenderLIB.h"
#include "Shader.h"
namespace Hikari
{
	class VisualPass : public Object
	{
		DECLARE_RTTI;
		DECLARE_NAMES;
	public:
		VisualPass():
			mvShader(nullptr),
			mpShader(nullptr)
		{

		}
		~VisualPass() {}
		inline void SetVertexShader(Shader* vsShader)
		{
			mvShader = vsShader;
		}
		inline void SetPixelShader(Shader* psShader)
		{
			mpShader = psShader;
		}
		inline Shader* GetVertexShader() const
		{
			return mvShader;
		}
		inline Shader* GetPixelShader() const
		{
			return mpShader;
		}

	private:
		Shader* mvShader;
		Shader* mpShader;
		Shader* mgShader;
		Shader* mhShader;
		Shader* mcShader;

	};
	typedef VisualPass* VisualPassPtr;
}
