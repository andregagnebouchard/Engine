#include "stdafx.h"
#include "Randomizer.h"
//=================================================================================================
Randomizer::Randomizer(void) :
	m_seed(1),
	m_mti(CMATH_N + 1)
{
}
//=================================================================================================
unsigned int Randomizer::RandomUInt(const uint upperLimitExcluded)
{
	ulong y;
	static ulong mag01[2] = { 0x0, CMATH_MATRIX_A };

	if (upperLimitExcluded == 0)
		return 0;

	// mag01[x] = x * MATRIX_A  for x=0,1
	if (m_mti >= CMATH_N) // Generate N words at one time
	{ 
		int kk;

		if (m_mti == CMATH_N + 1)   // If sgenrand() has not been called
			SetSeed(4357);					// A default initial seed is used

		for (kk = 0; kk < CMATH_N - CMATH_M; kk++) 
		{
			y = (m_mt[kk] & CMATH_UPPER_MASK) | (m_mt[kk + 1] & CMATH_LOWER_MASK);
			m_mt[kk] = m_mt[kk + CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		for (; kk < CMATH_N - 1; kk++) 
		{
			y = (m_mt[kk] & CMATH_UPPER_MASK) | (m_mt[kk + 1] & CMATH_LOWER_MASK);
			m_mt[kk] = m_mt[kk + (CMATH_M - CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}

		y = (m_mt[CMATH_N - 1] & CMATH_UPPER_MASK) | (m_mt[0] & CMATH_LOWER_MASK);
		m_mt[CMATH_N - 1] = m_mt[CMATH_M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

		m_mti = 0;
	}

	y = m_mt[m_mti++];
	y ^= CMATH_TEMPERING_SHIFT_U(y);
	y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
	y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
	y ^= CMATH_TEMPERING_SHIFT_L(y);

	return y % upperLimitExcluded;
}
//=================================================================================================
float Randomizer::RandomFloat()
{
	const float r = static_cast<float>(RandomUInt(INT_MAX));
	const float divisor = static_cast<float>(INT_MAX);
	return r / divisor;
}
//=================================================================================================
void Randomizer::SetSeed(const uint seed)
{
	// Setting initial seeds to mt[N] using the generator Line 25 of Table 1 in
	// [KNUTH 1981, The Art of Computer Programming Vol. 2 (2nd Ed.), pp102]
	m_mt[0] = seed & 0xffffffff;
	for (m_mti = 1; m_mti < CMATH_N; m_mti++)
		m_mt[m_mti] = (69069 * m_mt[m_mti - 1]) & 0xffffffff;

	m_seed = seed;
}
//=================================================================================================
unsigned int Randomizer::GetSeed() const
{
	return m_seed;
}
//=================================================================================================
void Randomizer::GenerateRandomSequence()
{
	SetSeed(static_cast<uint>(time(NULL)));
}
//=================================================================================================