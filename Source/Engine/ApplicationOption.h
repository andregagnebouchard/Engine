#pragma once
#include "Engine\IApplicationOption.h"
#include <unordered_map>
#include <memory>
using namespace std;

namespace Engine
{
	class ApplicationOption : public IApplicationOption
	{
	public:
		ApplicationOption();
		~ApplicationOption() = default;

		// IApplicationOption
		void Load(const wstring &filename) override;
		int GetWindowWidth() const override {return m_WindowWidth;}
		int GetWindowHeight() const override { return m_WindowHeight; }
		string GetWindowName() const override { return m_WindowName; }

		unordered_map<wstring, wstring> GetResourceNameToFilepath() const override { return m_ResourceNameToFilepath; }

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		string m_WindowName;
		bool m_IsWindowVisible;
		unordered_map<wstring, wstring> m_ResourceNameToFilepath;
		vector<shared_ptr<EntityDeclaration>> m_Entities;
	};
}
