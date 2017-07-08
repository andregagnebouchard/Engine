#include "stdafx.h"
#include "Display.h"
//=================================================================================================
Display::Display(IExecutionContext *executionContext, IGraphic *graphic) :
	m_executionContext(executionContext),
	m_graphic(graphic)
{
}
//=================================================================================================
IExecutionContext* Display::GetExecutionContext() const
{
	return m_executionContext;
}
//=================================================================================================
IGraphic* Display::GetGraphic() const
{
	return m_graphic;
}
//=================================================================================================