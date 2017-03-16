#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(Vec2 const & center, Vec2 const & radius)
	: m_radius(radius)
	, m_center(center)
{
}

CEllipse::~CEllipse() = default;

void CEllipse::Draw(ICanvas * canvas) const
{
	if (canvas)
	{
		canvas->SetColor(GetColor());
		canvas->DrawEllipse(m_center, m_radius);
	}
}

Vec2 CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetHorizontalRadius() const
{
	return m_radius.x;
}

double CEllipse::GetVerticalRadius() const
{
	return m_radius.y;
}
