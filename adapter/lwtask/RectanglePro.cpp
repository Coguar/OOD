#include "stdafx.h"
#include "RectanglePro.h"

namespace shape_drawing_lib_pro
{
CRectangle::CRectangle(const Point & leftTop, int width, int height, const uint32_t & color)
	: m_topLeft(leftTop)
	, m_width(width)
	, m_height(height)
	, m_color(color)
{
}

void CRectangle::Draw(graphics_lib_pro::ICanvas & canvas)const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_topLeft.x, m_topLeft.y);
	canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);
	canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y + m_height);
	canvas.LineTo(m_topLeft.x, m_topLeft.y + m_height);
	canvas.LineTo(m_topLeft.x, m_topLeft.y);
}
}