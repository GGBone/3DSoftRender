#pragma once
#include "GraphicsLib.h"
#include "VisualPass.h"
namespace Hikari
{
	class VisualTechnique
	{
	public:
		VisualTechnique::VisualTechnique();
		VisualTechnique::~VisualTechnique();
		VertexShader* Hikari::VisualTechnique::GetVertexShader(int passIndex) const;
		PixelShader * Hikari::VisualTechnique::GetPixelShader(int passIndex) const;
		void Hikari::VisualTechnique::InsertPass(VisualPass * pass);
		int Hikari::VisualTechnique::GetNumPass() const;
		VisualPass * Hikari::VisualTechnique::GetPass(int i) const;
	private:
		std::vector<VisualPass*> mPasses;
	};
}