#include "stdafx.h"
#include "Shape.h"


CAbstractShape::CAbstractShape()
{
}


CAbstractShape::~CAbstractShape()
{
}

void CAbstractShape::SetColor(Color color)
{
	m_color = color;
}

Color CAbstractShape::GetColor() const
{
	return m_color;
}

void CAbstractShape::Draw(ICanvas & canvas) const
{

}
