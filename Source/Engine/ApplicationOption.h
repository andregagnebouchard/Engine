#pragma once
#include "Engine\IApplicationOption.h"
#include <unordered_map>
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
		void SetWindowWidth(int width) override;
		int GetWindowWidth() const override;
		void SetWindowHeight(int height) override;
		int GetWindowHeight() const override;
		void SetWindowName(const string &name) override;
		string GetWindowName() const override;

		vector<shared_ptr<EntityDeclaration>> GetEntities() const override;
		unordered_map<wstring, wstring> GetResourceNameToFilepath() const override;
		void AddEntity(shared_ptr<IApplicationOption::EntityDeclaration> entity) override;

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		string m_WindowName;
		bool m_IsWindowVisible;
		unordered_map<wstring, wstring> m_ResourceNameToFilepath;
		vector<shared_ptr<EntityDeclaration>> m_Entities;
	};
}
