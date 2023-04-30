#pragma once
namespace Engine
{
	struct Point
	{
		float x;
		float y;
	};

	struct Square
	{
		float tl; // Top left
		float tr; // Top right
		float bl; // Bottom left
		float br; // Bottom Right
	};

	struct vec3
	{
		int x;
		int y; 
		int z;
	};
}