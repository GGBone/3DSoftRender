#include "GraphicsPCH.h"

#include "SoftVertexShader.h"
#include "SoftRenderer.h"

using namespace Hikari;

Hikari::SoftVertexShader::SoftVertexShader(SoftRenderer *renderer, const VertexShader *vshader)
	:mPInput(nullptr),
	mVInput(nullptr)
{
	//Compiler Shader
	SoftRenderData* renderData = renderer->GetRendererData();

	//Default Name
	std::string name = vshader->GetProgramName();

	CompileFromFile(name);


}

void Hikari::SoftVertexShader::Process(std::vector<VInput>& in)
{
	mVInput = new std::vector<VInput>(in);
	if (mPInput == nullptr)
	{
		mPInput = new std::vector<PInput>();
	}

	for each (VInput var in in)
	{
		(*mPInput).push_back(cell0.VS_Main(var));
	}
}

std::vector<VInput>* Hikari::SoftVertexShader::GetVInput() const
{
	return mVInput;
}

std::vector<PInput>* Hikari::SoftVertexShader::GetPInput() const
{
	return mPInput;
}

Cell* Hikari::SoftVertexShader::GetCell(int index)
{
	if (index == 0)
		return static_cast<Cell*>((&cell0));
	else return nullptr;
}


HRESULT Hikari::SoftVertexShader::CompileFromFile(std::string VertexProgramFilename)
{
	//Interpreter
	return E_NOTIMPL;
}