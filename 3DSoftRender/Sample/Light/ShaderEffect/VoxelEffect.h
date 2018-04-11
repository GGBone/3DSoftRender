#pragma once
#include "Graphics\GraphicsLib.h"
#include "Graphics\VisualEffectInstance.h"
#include "Graphics\Dx11Shader.h"
#include "Loader\ConfigurationSetting.h"
#include "Graphics\Dx11RenderWindow.h"
namespace Hikari
{
	class Camera;
	class VoxelEffect :public VisualEffect,public std::enable_shared_from_this<VoxelEffect>
	{
	public:

		VoxelEffect(std::shared_ptr<RenderWindow> rwindow, std::shared_ptr<Renderer> renderer, std::shared_ptr<Scene> scene);
		virtual ~VoxelEffect();
		std::shared_ptr<VisualEffectInstance> CreateInstance() override;
		Camera* orthoCamera;
	
	};
}