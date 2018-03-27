#pragma once
#include <SFML\Window.hpp>
#include <memory>
using namespace std;

namespace Engine
{
	class System;

	class Application
	{
	public:
		static shared_ptr<Application> Get();

		void Init();
		void Shutdown();
		void AddSystem(shared_ptr<System> system);

	private:
    Application() = default;

		static shared_ptr<Application> m_Instance;
		vector<shared_ptr<System>> m_Systems;
	};
}
