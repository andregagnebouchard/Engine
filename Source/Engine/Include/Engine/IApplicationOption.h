#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
using namespace std;

namespace Engine
{
  class Resource;
	class IEntity;
	class IApplicationOption
	{
	public:
		struct EntityDeclaration
		{
			vector<wstring> componentNames;
			wstring name;
		};

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
		virtual vector<shared_ptr<EntityDeclaration>> GetEntities() const = 0;
		virtual unordered_map<wstring, wstring> GetResourceNameToFilepath() const = 0;
		virtual void AddEntity(shared_ptr<IApplicationOption::EntityDeclaration> entity) = 0;

		static shared_ptr<IApplicationOption> Create();
	};
}