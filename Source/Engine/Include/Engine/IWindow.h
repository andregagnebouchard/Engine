#pragma once
#include <Engine\Typedef.h>
#include <memory>
using namespace std;
namespace Engine
{
	class IWindow
	{
	public:
		~IWindow() = default;

		virtual void Resize(uint width, uint height) = 0;
		virtual void SetVisible(bool isVisible) = 0;
	};
}