#pragma once
class IColor
{
public:
	virtual ~IColor() {};

	virtual const float* const GetColorArray() const = 0;
	virtual int GetVerticeArraySize() const = 0;
};
//=================================================================================================
class Red : public IColor
{
public:
	Red() :
		m_r(1.0),
		m_g(0.0),
		m_b(0.0)
	{
	}

	virtual const float* const GetColorArray() const override
	{
		return m_colors;
	}
	virtual int GetVerticeArraySize() const override
	{
		return 3;
	}

private:
	float m_r;
	float m_g;
	float m_b;
	float m_colors[3] = { m_r, m_g, m_b };
};
//=================================================================================================
class CustomColor : public IColor
{
public:
	CustomColor(const float r, const float g, const float b) :
		m_r(r),
		m_g(g),
		m_b(b)
	{
	}

	virtual const float* const GetColorArray() const override
	{
		return m_colors;
	}
	virtual int GetVerticeArraySize() const override
	{
		return 3;
	}

private:
	float m_r;
	float m_g;
	float m_b;
	float m_colors[3] = { m_r, m_g, m_b };
};