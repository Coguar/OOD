#include "stdafx.h"
#include "RectanglePro.h"

namespace graphics_lib_pro
{
CRectangle::CRectangle(const Point & leftTop, int width, int height)
	: m_topLeft(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas & canvas)const
{
	canvas.MoveTo(m_topLeft.x, m_topLeft.y);
	canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);
	canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y + m_height);
	canvas.LineTo(m_topLeft.x, m_topLeft.y + m_height);
	canvas.LineTo(m_topLeft.x, m_topLeft.y);
}
}