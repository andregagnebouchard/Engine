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
	Point(const float x, const float y) :
		m_x(x),
		m_y(y)
	{}

	virtual const float* const GetVerticesArray() const override
	{
		return vertices;
	}

	virtual int GetVerticeArraySize() const override
	{
		return 2;
	}

	float m_x;
	float m_y;
	float vertices[2] = { m_x, m_y };
};
//=================================================================================================
class Triangle : public IPrimitive
{
public:
	Triangle(const Point p1, const Point p2, const Point p3) :
		m_p1(p1),
		m_p2(p2),
		m_p3(p3)
		{}

	virtual const float* const GetVerticesArray() const override
	{
		return vertices;
	}

	virtual int GetVerticeArraySize() const override
	{
		return 6;
	}

	Point m_p1;
	Point m_p2;
	Point m_p3;
	float vertices[6] = { m_p1.vertices[0], m_p1.vertices[1], m_p2.vertices[0], m_p2.vertices[1], m_p3.vertices[0], m_p3.vertices[1] };
};
//=================================================================================================