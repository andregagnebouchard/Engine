#pragma once
using namespace std;
namespace Engine
{
	class EntityIdCounter
	{
	public:
		static inline int GenerateEntityId() { return ++m_Counter; }
	private:
		static int m_Counter;
	};
}
