#pragma once
#include "Dx11RenderLIB.h"
#include "SceneGraph/Mesh.h"
#include "Dx11Renderer.h"

namespace Hikari
{
	class MeshDx : public Mesh
	{
	public:
		explicit MeshDx(const std::shared_ptr<DirectRenderer>& render);
		virtual ~MeshDx() = default;

		void Render(RenderEventArgs& renderArgs) override;
		void Accept(Visitor& visitor) override;

	private:
		ID3D11Device* m_pDevice{};
		ID3D11DeviceContext* m_pDeviceContext{};
	};
}
