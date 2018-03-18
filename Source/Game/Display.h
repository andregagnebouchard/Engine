#pragma once
//=================================================================================================
#include "IExecutionContext.h"
#include "IGraphic.h"
class Display
{
public:
	Display(IExecutionContext* executionContext, IGraphic* graphic);

	IExecutionContext* GetExecutionContext() const;
	IGraphic* GetGraphic() const;
private:
	IExecutionContext* m_executionContext;
	IGraphic* m_graphic;
};
//=================================================================================================