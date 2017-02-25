#include "GraphicsPCH.h"
#include "Shader.h"
using namespace Hikari;

Hikari::Shader::Shader()
	:mNumConstants(0),
	mNumInputs(0),
	mNumOutputs(0),
	mNumSamplers(0),
	mInputName(0),
	mInputType(0),
	mInputSemantic(0),
	mConstantName(0),
	mNumRegistersUsed(0),
	mSamplerName(0),
	mprogramFileName(0),
	mOutputName(0),
	mOutputType(0),
	mOutputSemantic(0)
{
}

Hikari::Shader::Shader(const std::string & programName, int numInputs, int numOutputs, int numConstants, int numSamples, bool profileOwner)
	:mprogramFileName(programName),
	mNumInputs(numInputs),
	mNumConstants(numConstants),
	mNumOutputs(numOutputs),
	mNumSamplers(numSamples)
{
	SetName(programName);
	if (mNumInputs > 0)
	{
		mInputName = new std::string[mNumInputs];
		mInputType = new VariableType[mNumInputs];
		mInputSemantic = new VariableSemantic[mNumInputs];
	}
	if (mNumOutputs > 0)
	{
		mOutputName = new std::string[mNumOutputs];
		mOutputType = new VariableType[mNumOutputs];
		mOutputSemantic = new VariableSemantic[mNumOutputs];
	}

	if (mNumConstants > 0)
	{
		mConstantName = new std::string[mNumConstants];
		mNumRegistersUsed = new int[mNumConstants];

	}
}

Hikari::Shader::~Shader()
{
	delete[] mInputName;
	delete[] mOutputName;
}

void Hikari::Shader::SetInput(int i, const std::string & name, VariableType type, VariableSemantic semantic)
{
	mInputName[i] = name;
}

void Hikari::Shader::SetOutput(int i, const std::string & name, VariableType type, VariableSemantic semantic)
{
}

void Hikari::Shader::SetConstant(int i, const std::string & name, int numRegistersUsed)
{
}

const std::string& Hikari::Shader::GetInputName(int i) const
{
	// TODO: insert return statement here
	return mInputName[i];
}

Shader::VariableType Shader::GetInputType(int i) const
{
	return mInputType[i];
}

Shader::VariableSemantic Shader::GetInputSemantic(int i) const
{
	return mInputSemantic[i];
}

const std::string & Hikari::Shader::GetConstantName(int i) const
{
	// TODO: insert return statement here
	return mConstantName[i];
}

const std::string Hikari::Shader::GetFileName() const
{
	return mprogramFileName;
}