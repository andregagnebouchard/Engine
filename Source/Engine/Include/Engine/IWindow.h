#pragma once
#include <memory>
using namespace std;
namespace Engine
{
	// This class implementation exposes Engine's dependencies, therefore the implementation is hidden
	class IWindow
	{
	public:
		~IWindow() = default;

		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void SetVisible(bool isVisible) = 0;
	};
}