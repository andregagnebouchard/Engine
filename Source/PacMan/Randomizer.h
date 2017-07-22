#pragma once
#include "stdafx.h"
//=================================================================================================
// Period parameters
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   // constant vector a 
#define CMATH_UPPER_MASK 0x80000000 // most significant w-r bits
#define CMATH_LOWER_MASK 0x7fffffff // least significant r bits

// Tempering parameters
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)
//=================================================================================================
class Randomizer
{
public:
	Randomizer();

	void GenerateRandomSequence();

	uint RandomUInt(const uint upperLimitExcluded);
	float RandomFloat();

	void SetSeed(const uint seed);
	uint GetSeed() const;
private:
	uint m_seed;
	ulong m_mt[CMATH_N];	// State vector array
	int m_mti;						// m_Mti==N+1 means m_Mt[N] is not initialized
};
//=================================================================================================