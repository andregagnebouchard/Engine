#pragma once
#include <string>
#include <memory>
using namespace std;

namespace Engine
{
	class IApplicationOption
	{
	public:
		virtual ~IApplicationOption() = default;

		// Load the values defined in a XML file
		virtual void Init(const wstring &filename) = 0;

		virtual void SetWindowWidth(int width) = 0;
		virtual int GetWindowWidth() const = 0;
		virtual void SetWindowHeight(int height) = 0;
		virtual int GetWindowHeight() const = 0;
		virtual void SetWindowName(const string &name) = 0;
		virtual string GetWindowName() const = 0;
		virtual void SetIsWindowVisible(bool isVisible) = 0;
		virtual bool GetIsWindowVisible() const = 0;

		static shared_ptr<IApplicationOption> Create();
	};
}