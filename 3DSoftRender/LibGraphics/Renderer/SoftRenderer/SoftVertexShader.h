#if 0
#pragma once
#include "Dx11RenderLIB.h"
#include "Object.h"
#include "SoftRenderer.h"
#include "DefaultShader.h"
namespace Hikari
{
	class SoftVertexShader
	{
	public:
		SoftVertexShader(SoftRenderer*, const VertexShader*);

		void Process(std::vector<VInput>& in);
		std::vector<VInput>* GetVInput() const;
		std::vector<PInput>* GetPInput() const;
		Cell* GetCell(int index);
	private:
		Cell cell0;
		std::vector<PInput>* mPInput;
		std::vector<VInput>* mVInput;
		HRESULT CompileFromFile(std::string VertexProgramFilename);
	};
}

#endif