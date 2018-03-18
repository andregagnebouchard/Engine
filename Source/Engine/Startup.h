#pragma once
#include "stdafx.h"
#include "SFML\System\String.hpp"
namespace Engine
{
class Startup
{
public:
	bool CheckStorage(const int64 diskSpaceNeeded);
	ulong ReadCPUSpeed();
	bool CheckMemory(const uint64 physicalRAMNeeded, const uint64 virtualRAMNeeded);
	bool IsOnlyInstance(const sf::String &gameTitle);
};
}