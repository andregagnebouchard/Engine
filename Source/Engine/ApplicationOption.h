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
		void Init(const wstring &filename) override;
		void SetWindowWidth(int width) override;
		int GetWindowWidth() const override;
		void SetWindowHeight(int height) override;
		int GetWindowHeight() const override;
		void SetWindowName(const string &name) override;
		string GetWindowName() const override;
		void SetIsWindowVisible(bool isVisible) override;
		bool GetIsWindowVisible() const override;

	private:
		int m_WindowWidth;
		int m_WindowHeight;
		string m_WindowName;
		bool m_IsWindowVisible;
	};
}
