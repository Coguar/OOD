#include "stdafx.h"
#include "TrianglePro.h"

namespace shape_drawing_lib_pro
{
CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3, const uint32_t & color)
	: m_vertex1(p1)
	, m_vertex2(p2)
	, m_vertex3(p3)
	, m_color(color)
{
}

void CTriangle::Draw(graphics_lib_pro::ICanvas & canvas)const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_vertex1.x, m_vertex1.y);
	canvas.LineTo(m_vertex2.x, m_vertex2.y);
	canvas.LineTo(m_vertex3.x, m_vertex3.y);
	canvas.LineTo(m_vertex1.x, m_vertex1.y);
}
}