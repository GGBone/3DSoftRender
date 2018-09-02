#include "GraphicsPCH.h"
#define ENABLE_BOOST
#include "Event.h"
#undef ENABLE_BOOST
#include "BeginQueryPass.h"
#include "Resource/Query.h"
using namespace Hikari;

BeginQueryPass::BeginQueryPass(std::shared_ptr<Query> query)
	: m_pQuery(query)
{
}

BeginQueryPass::~BeginQueryPass()
= default;

void BeginQueryPass::Render(RenderEventArgs& e)
{
	if (m_pQuery)
	{
		m_pQuery->Begin(e.FrameCounter);
	}
}
