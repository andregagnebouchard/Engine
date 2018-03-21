#pragma once
#include <Engine\Export.h>
#include <SFML\Window.hpp>
#include <memory>
namespace Engine
{
	class System;

	class EXPORT Application
	{
	public:
		static shared_ptr<Application> Get();

		void Init();
		void Shutdown();
		void AddSystem(shared_ptr<System> system);

	private:
		static shared_ptr<Application> m_Instance;
		vector<shared_ptr<System>> m_Systems;
	};
}
