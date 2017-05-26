#include "Shape.h"



Shape::Shape()
{
}


Shape::~Shape()
{
}

OptionalStyle Shape::GetLineStyle() const
{
	return m_lineStyle;
}

void Shape::SetLineStyle(const CStyle & style)
{
	m_lineStyle = style;
}

OptionalStyle Shape::GetFillStyle() const
{
	return m_fillStyle;
}

void Shape::SetFillStyle(const CStyle & style)
{
	m_fillStyle = style;
}

RectD Shape::GetFrame() const
{
	return m_frame;
}

void Shape::SetFrame(const RectD & rect)
{
	m_frame = rect;
}

IGroupPtr Shape::GetGroup()
{
	return nullptr;
}
