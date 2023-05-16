#pragma once
#include <unordered_map>
#include <memory>
using namespace std;

namespace Engine
{
	class ApplicationOption
	{
	public:
		struct EntityDeclaration
		{
			vector<wstring> componentNames;
			wstring name;
		};

		ApplicationOption();
		~ApplicationOption() = default;

		void Load(const wstring &filename);
		int GetWindowWidth() const {return m_WindowWidth;}
		int GetWindowHeight() const { return m_WindowHeight; }
		string GetWindowName() const { return m_WindowName; }

		unordered_map<wstring, wstring> GetResourceNameToFilepath() const { return m_ResourceNameToFilepath; }

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		string m_WindowName;
		bool m_IsWindowVisible;
		unordered_map<wstring, wstring> m_ResourceNameToFilepath;
		vector<shared_ptr<EntityDeclaration>> m_Entities;
	};
}
