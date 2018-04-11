#include "Graphics\GraphicsPCH.h"

#include "Core\Event.h"
#include "Graphics\Query.h"
#include "BeginQueryPass.h"
using namespace Hikari;

BeginQueryPass::BeginQueryPass(std::shared_ptr<Query> query)
	: m_pQuery(query)
{}

BeginQueryPass::~BeginQueryPass()
{}

void BeginQueryPass::Render(RenderEventArgs& e)
{
	if (m_pQuery)
	{
		m_pQuery->Begin(e.FrameCounter);
	}
}
