#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(Vec2 const& topLeft, Vec2 const& size)
	: m_topLeft(topLeft)
	, m_size(size)
{
}


CRectangle::~CRectangle() = default;

void CRectangle::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_topLeft, { m_topLeft.x + m_size.x, m_topLeft.y });
	canvas.DrawLine({ m_topLeft.x + m_size.x, m_topLeft.y }, { m_topLeft.x + m_size.x, m_topLeft.y + m_size.y });
	canvas.DrawLine({ m_topLeft.x + m_size.x, m_topLeft.y + m_size.y }, { m_topLeft.x, m_topLeft.y + m_size.y });
	canvas.DrawLine({ m_topLeft.x, m_topLeft.y + m_size.y }, m_topLeft);
}

Vec2 CRectangle::GetLeftTop() const
{
	return m_topLeft;
}

Vec2 CRectangle::GetRightBottom() const
{
	return {m_topLeft.x + m_size.x, m_topLeft.y + m_size.y };
}
