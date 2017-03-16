#include "stdafx.h"
#include <iostream>
#include "Canvas.h"


CTextCanvas::CTextCanvas()
{
}


CTextCanvas::~CTextCanvas() = default;

void CTextCanvas::SetColor(Color color)
{
	m_currentColor = color;
	std::cout << STR_COLOR_LIST.find(m_currentColor)->second << std::endl;
}

void CTextCanvas::DrawLine(Vec2 const & start, Vec2 const & end)
{
	std::cout << "-----Start LINE-----" << std::endl;
	std::cout << "First vertex = (" << start.x << ", " << start.y << " )" << std::endl;
	std::cout << "Second vertex = (" << end.x << ", " << end.y << " )" << std::endl;
	std::cout << "-----End LINE-----" << std::endl;
}

void CTextCanvas::DrawEllipse(Vec2 const & center, Vec2 const & size)
{
	std::cout << "-----Start Ellipse-----" << std::endl;
	std::cout << "Center = (" << center.x << ", " << center.y << " )" << std::endl;
	std::cout << "Radius = (" << size.x << ", " << size.y << " )" << std::endl;
	std::cout << "-----End Ellipse-----" << std::endl;
}
