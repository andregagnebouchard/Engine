#pragma once
namespace Engine
{
	#if COMPILING_DLL
	#define EXPORT __declspec(dllexport)
	#else
	#define EXPORT __declspec(dllimport)
	#endif
}