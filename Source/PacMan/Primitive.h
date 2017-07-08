#pragma once
//=================================================================================================
class IPrimitive
{
public:
	virtual ~IPrimitive() {};

	virtual const float* const GetVerticesArray() const = 0;
	virtual int GetVerticeArraySize() const = 0;
};
//=================================================================================================
class Point : public IPrimitive
{
public:
	Point(const float _x, const float _y) :
		x(_x),
		y(_y)
	{}

	virtual const float* const GetVerticesArray() const override
	{
		return vertices;
	}

	virtual int GetVerticeArraySize() const override
	{
		return 2;
	}

	float x;
	float y;
	float vertices[2] = { x, y };
};
//=================================================================================================
class Triangle : public IPrimitive
{
public:
	Triangle(const Point _p1, const Point _p2, const Point _p3) :
		p1(_p1),
		p2(_p2),
		p3(_p3)
		{}

	virtual const float* const GetVerticesArray() const override
	{
		return vertices;
	}

	virtual int GetVerticeArraySize() const override
	{
		return 6;
	}

	Point p1;
	Point p2;
	Point p3;
	float vertices[6] = { p1.vertices[0], p1.vertices[1], p2.vertices[0], p2.vertices[1], p3.vertices[0], p3.vertices[1] };
};
//=================================================================================================