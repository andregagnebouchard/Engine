#pragma once
#include <memory>
//=================================================================================================
template<class T>
void SafeDelete(T*& pVal)
{
	if (pVal != nullptr)
	{
		delete pVal;
		pVal = NULL;
	}
}
//=================================================================================================
template<class T>
void SafeDeleteArray(T*& pVal)
{
	if (pVal != nullptr)
	{
		delete[] pVal;
		pVal = null;
	}
}
//=================================================================================================
template <class Type>
std::shared_ptr<Type> MakeStrongPtr(std::weak_ptr<Type> pWeakPtr)
{
	if (!pWeakPtr.expired())
		return shared_ptr<Type>(pWeakPtr);
	else
		return shared_ptr<Type>();
}
//=================================================================================================
#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif
//=================================================================================================
#if defined(_DEBUG)
#	define NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define NEW new
#endif
//=================================================================================================