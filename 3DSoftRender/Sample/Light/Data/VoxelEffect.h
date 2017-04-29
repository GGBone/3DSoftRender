#pragma once
#include "GraphicsLib.h"
#include "VisualEffectInstance.h"
#include "Dx11Shader.h"
#include "ConfigurationSetting.h"
namespace Hikari
{
	class Camera;
	class VoxelEffect :public VisualEffect
	{
	public:

		VoxelEffect(DirectRenderer* renderer, Scene* scene);
		virtual ~VoxelEffect();
		VisualEffectInstance* CreateInstance() const;
		Camera* orthoCamera;
	};
}