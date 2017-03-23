#pragma once
#include "Shape.h"
class CEllipse :
	public CAbstractShape
{
public:
	CEllipse(Vec2 const& center, Vec2 const& radius);
	~CEllipse();

	void Draw(ICanvas & canvas) const override;

	Vec2 GetCenter() const;
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;
private:
	Vec2 m_radius;
	Vec2 m_center;
};

