#include "Graphics\GraphicsPCH.h"

#include "Core\Event.h"
#include "Graphics\Query.h"
#include "EndQueryPass.h"
using namespace Hikari;
EndQueryPass::EndQueryPass(std::shared_ptr<Query> query)
	: m_pQuery(query)
{}

EndQueryPass::~EndQueryPass()
{}

void EndQueryPass::Render(RenderEventArgs& e)
{
	if (m_pQuery)
	{
		m_pQuery->End(e.FrameCounter);
	}
}
