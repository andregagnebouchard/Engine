#pragma once
#include <string>
#include <memory>
#include <vector>
using namespace std;

namespace Engine
{
  class Resource;
	class IApplicationOption
	{
	public:
		virtual ~IApplicationOption() = default;

		// Load the values defined in a XML file
    // Throw if any of the following parameter are not found
    // - Window (Height, Width, Name, IsVisible)
		virtual void Load(const wstring &filename) = 0;

		virtual void SetWindowWidth(int width) = 0;
		virtual int GetWindowWidth() const = 0;
		virtual void SetWindowHeight(int height) = 0;
		virtual int GetWindowHeight() const = 0;
		virtual void SetWindowName(const string &name) = 0;
		virtual string GetWindowName() const = 0;

    // Might be empty
    virtual vector<shared_ptr<Resource>> GetResources() const = 0;

		static shared_ptr<IApplicationOption> Create();
	};
}