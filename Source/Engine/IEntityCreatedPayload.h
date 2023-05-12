#pragma once
using namespace std;

namespace Engine
{
	class IEntityCreatedPayload
	{
	public:
		virtual ~IEntityCreatedPayload() = default;
		virtual int GetType() const = 0;
	private:
	};
}