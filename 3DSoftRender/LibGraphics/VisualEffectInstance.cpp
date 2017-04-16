//#include "GraphicsPCH.h"
//#include "VisualEffectInstance.h"
//using namespace Hikari;
//Hikari::VisualEffectInstance::VisualEffectInstance(const VisualEffect * effect, int techniqueIndex)
//	:mEffect(const_cast<VisualEffect*>(effect)),
//	mTechniqueIndex(techniqueIndex)
//{
//	VisualTechnique* techi = mEffect->GetTechnique(mTechniqueIndex);
//	mNumPasses = techi->GetNumPass();
//	mVertexParameters = new ShaderParameter*[mNumPasses];
//	mPixelParameters = new ShaderParameter*[mNumPasses];
//
//	for (int i = 0; i < mNumPasses; ++i)
//	{
//		VisualPass* pass = techi->GetPass(i);
//		mVertexParameters[i] = new ShaderParameter(pass->GetVertexShader());
//
//		mPixelParameters[i] = new ShaderParameter(pass->GetPixelShader());
//	}
//}
//
//Hikari::VisualEffectInstance::~VisualEffectInstance()
//{
//
//}
//
//const VisualPass* Hikari::VisualEffectInstance::GetPass(int pass) const
//{
//	return mEffect->GetTechnique(mTechniqueIndex)->GetPass(pass);
//}
//
//ShaderParameter * Hikari::VisualEffectInstance::GetVertexShaderParam(int pass) const
//{
//	return mVertexParameters[pass];
//}
//
//ShaderParameter * Hikari::VisualEffectInstance::GetPixelShaderParam(int pass) const
//{
//	return mPixelParameters[pass];
//}
//
//int Hikari::VisualEffectInstance::SetVertexConstant(int pass, const std::string & name, ShaderFloat * sfloat)
//{
//	return mVertexParameters[pass]->SetConstant(name, sfloat);
//}
//
//int Hikari::VisualEffectInstance::SetPixelConstant(int pass, const std::string & name, ShaderFloat * sfloat)
//{
//	return mPixelParameters[pass]->SetConstant(name, sfloat);
//}
//
//void Hikari::VisualEffectInstance::SetVertexConstant(int pass, int handle, ShaderFloat * sfloat)
//{
//	if (0 <= pass && pass <= mNumPasses)
//	{
//		return mVertexParameters[pass]->SetConstant(handle, sfloat);
//	}
//	else
//		MessageBoxA(NULL, "_____VisualEffect->SetVertexConstant", "Error", MB_OK);
//}
//
//void Hikari::VisualEffectInstance::SetPixelConstant(int pass, int handle, ShaderFloat * sfloat)
//{
//	if (0 <= pass && pass <= mNumPasses)
//	{
//		return mPixelParameters[pass]->SetConstant(handle, sfloat);
//	}
//	else
//		MessageBoxA(NULL, "_____VisualEffect->SetPixelConstant", "Error", MB_OK);
//
//}