#include "EndQueryPass.h"
#include "Resource/Query.h"
#define ENABLE_BOOST
#include "Event.h"
#undef ENABLE_BOOST
using namespace Hikari;

EndQueryPass::EndQueryPass(std::shared_ptr<Query> query)
	: m_pQuery(query)
{
}

EndQueryPass::~EndQueryPass()
= default;

void EndQueryPass::Render(RenderEventArgs& e)
{
	if (m_pQuery)
	{
		m_pQuery->End(e.FrameCounter);
	}
}
