#pragma once
#include "Graphics\Graphics.h"
#include "Graphics\Mesh.h"

namespace Hikari
{
	class MeshDx : public Mesh
	{
	public:
		MeshDx(std::shared_ptr<DirectRenderer>& render);
		virtual ~MeshDx();

		virtual void AddVertexBuffer(const BufferBinding& binding, std::shared_ptr<BufferBase> buffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<BufferBase> buffer)override;
		virtual void SetMaterial(std::shared_ptr<Material> buffer) override;
		virtual void SetInstanceBuffer(std::shared_ptr<BufferBase> buffer)override;
		virtual std::shared_ptr<Material> GetMaterial() const override;

		virtual void Render(RenderEventArgs& renderArgs);
		virtual void Accept(Visitor& visitor);

	private:
		typedef std::map<BufferBinding, std::shared_ptr<BufferBase>> BufferMap;
		BufferMap m_VertexBuffers;
		std::shared_ptr<BufferBase> m_pIndexBuffer;
		std::shared_ptr<BufferBase> m_pInstanceBuffer;
		std::shared_ptr<Material> m_pMaterial;
		ID3D11Device2* m_pDevice;
		ID3D11DeviceContext2* m_pDeviceContext;
	};
}