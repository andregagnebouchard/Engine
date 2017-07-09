#pragma once
#include "stdafx.h"
#include "IShaderProgram.h"
#include "Primitive.h"
#include "Colors.h"
//=================================================================================================
class IGraphic
{
public:

	virtual void BindShaderProgram(IShaderProgram* const shaderProgram) = 0;
	virtual void UnbindShaderProgram() = 0;
	virtual void FillVertexBuffer(const IPrimitive* const primitive) = 0;
	virtual void FillColorBuffer(const IColor* const color) = 0;

	virtual void Draw() const = 0;
	virtual void Clear() = 0;
};
//=================================================================================================