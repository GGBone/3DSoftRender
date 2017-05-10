#pragma once
#include "Graphics.h"
#include "Mesh.h"

namespace Hikari
{
	class MeshDx : public Mesh
	{
	public:
		MeshDx(DirectRenderer* render);
		virtual ~MeshDx();

		virtual void AddVertexBuffer(const BufferBinding& binding, Buffer* buffer) override;
		virtual void SetIndexBuffer(Buffer* buffer)override;
		virtual void SetMaterial(Material* buffer) override;
		virtual void SetInstanceBuffer(Buffer* buffer)override;
		virtual Material* GetMaterial() const override;

		virtual void Render(RenderEventArgs& renderArgs);
		virtual void Accept(Visitor& visitor);

	private:
		typedef std::map<BufferBinding, Buffer*> BufferMap;
		BufferMap m_VertexBuffers;
		Buffer* m_pIndexBuffer;
		Buffer* m_pInstanceBuffer;
		Material* m_pMaterial;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
	};
}