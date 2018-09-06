#pragma once
#include "Dx11RenderLIB.h"
#include "Resource/Query.h"

namespace Hikari
{
	class QueryDX11 : public Query
	{
	public:

		QueryDX11(ID3D11Device* pDevice, QueryType queryType, uint8_t numBuffers);
		virtual ~QueryDX11();

		void Begin(int64_t frame = 0L) override;
		void End(int64_t frame = 0L) override;
		bool QueryResultAvailable(int64_t frame = 0L) override;
		QueryResult GetQueryResult(int64_t frame = 0L) override;
		uint8_t GetBufferCount() const override;

	protected:

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext{};

		typedef std::vector<ID3D11Query*> QueryBuffer;
		QueryBuffer m_DisjointQueries;
		// For timer queries, we need 2 sets of buffered queries.
		QueryBuffer m_Queries[2];

		QueryType m_QueryType{};
		// How many queries will be used to prevent stalling the GPU.
		uint8_t m_NumBuffers;
	};
}
