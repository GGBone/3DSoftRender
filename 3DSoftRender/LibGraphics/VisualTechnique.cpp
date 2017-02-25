#include "VisualTechnique.h"
using namespace Hikari;
Hikari::VisualTechnique::VisualTechnique()
{
	mPasses.reserve(10);
}
Hikari::VisualTechnique::~VisualTechnique()
{
}
VertexShader* Hikari::VisualTechnique::GetVertexShader(int passIndex) const
{
	if (passIndex > mPasses.size())
		return nullptr;
	return mPasses[passIndex]->GetVertexShader();
}
PixelShader * Hikari::VisualTechnique::GetPixelShader(int passIndex) const
{
	if (passIndex > mPasses.size())
		return nullptr;
	return mPasses[passIndex]->GetPixelShader();

}
void Hikari::VisualTechnique::InsertPass(VisualPass * pass)
{
	if (pass != nullptr)
	{
		mPasses.push_back(pass);
	}
}

int Hikari::VisualTechnique::GetNumPass() const
{
	return mPasses.size();
}

VisualPass * Hikari::VisualTechnique::GetPass(int i) const
{
	return mPasses[i];
}