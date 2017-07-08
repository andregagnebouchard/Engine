#pragma once
#include "stdafx.h"
#include "Primitive.h"
//=================================================================================================
class IGraphic
{
public:
	virtual void FillBuffer(const IPrimitive* const primitive) = 0;
	virtual void DrawBuffer() = 0;
	virtual void ClearBuffer() = 0;
};
//=================================================================================================