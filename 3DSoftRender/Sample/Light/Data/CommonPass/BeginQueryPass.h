#pragma once

#include "AbstractPass.h"

namespace Hikari
{
	class Query;

	// A render pass to begin a GPU query.
	class BeginQueryPass : public AbstractPass
	{
	public:
		BeginQueryPass(std::shared_ptr<Query> query);
		virtual ~BeginQueryPass();

		void Render(RenderEventArgs& e) override;

	private:
		std::shared_ptr<Query> m_pQuery{};
	};
}
