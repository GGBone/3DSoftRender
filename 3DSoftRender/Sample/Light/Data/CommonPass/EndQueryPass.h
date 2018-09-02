#pragma once

#include "AbstractPass.h"


namespace Hikari
{
	class Query;

	// A render pass to begin a GPU query.
	class EndQueryPass : public AbstractPass
	{
	public:
		EndQueryPass(std::shared_ptr<Query> query);
		virtual ~EndQueryPass();

		void Render(RenderEventArgs& e) override;

	private:
		std::shared_ptr<Query> m_pQuery{};
	};
}
