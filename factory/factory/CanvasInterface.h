#pragma once

struct Vec2
{
	Vec2() {};
	Vec2(double const& x, double const& y)
		: x(x)
		, y(y)
	{}
	double x = 0;
	double y = 0;
};

struct ICanvas
{
	virtual ~ICanvas() = default;
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Vec2 const& start, Vec2 const& end) = 0;
	virtual void DrawEllipse(Vec2 const& center, Vec2 const& size) = 0;
};