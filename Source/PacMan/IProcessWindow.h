#pragma once
#include "stdafx.h"
//=================================================================================================
struct ProcessWindowProperties
{
	ProcessWindowProperties(const std::string &_name, const uint _width, const uint _height) :
		name(_name),
		width(_width),
		height(_height)
	{}

	std::string name;
	uint width;
	uint height;
};
//=================================================================================================
class IProcessWindow
{
public:
	~IProcessWindow() {};
	virtual void UpdateDisplay() = 0;
	virtual void UpdateProperties(const ProcessWindowProperties &newProperties) = 0;
};
//=================================================================================================