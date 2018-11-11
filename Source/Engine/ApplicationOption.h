#pragma once
#include "Engine\IApplicationOption.h"
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

    vector<shared_ptr<Resource>> GetResources() const override;
		vector<shared_ptr<EntityDeclaration>> GetEntities() const override;
		void AddResource(shared_ptr<Resource> resource) override;
		void AddEntity(shared_ptr<IApplicationOption::EntityDeclaration> entity) override;

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		string m_WindowName;
		bool m_IsWindowVisible;
    vector<shared_ptr<Resource>> m_Resources;
		vector<shared_ptr<EntityDeclaration>> m_Entities;
	};
}
