#pragma once
//=================================================================================================
class RandomVisiter
{
public:
	RandomVisiter(const int elementsQty);
	
	int GetNext(const bool restart = false);

	inline bool Done();
	inline void Restart();

private:
	static int m_primeAarray[];

	int m_skip;
	int m_currentPosition;
	int m_maxElements;
	int *m_currentPrime;
	int m_searches;
};
//=================================================================================================