#include "stdafx.h"
#include "SVGCanvas.h"

CSVGCanvas::CSVGCanvas(std::ofstream & strm)
	: m_oStrm(strm)
{
	m_oStrm << "<svg xmlns='http://www.w3.org/2000/svg'>" << std::endl;
}

CSVGCanvas::~CSVGCanvas()
{
	m_oStrm << "</svg>";
}

void CSVGCanvas::SetColor(Color color)
{
	m_currentColor = color;
}

void CSVGCanvas::DrawLine(Vec2 const & start, Vec2 const & end)
{
	m_oStrm << "<line x1= '" << start.x << "' y1= '" << start.y << "' x2= '" << end.x << "' y2= '" << end.y
		<< "' stroke-width= '1' fill = 'white' stroke= '" << STR_COLOR_LIST.find(m_currentColor)->second << "' />" << std::endl;
}

void CSVGCanvas::DrawEllipse(Vec2 const & center, Vec2 const & size)
{
	m_oStrm << "<ellipse cx= '" << center.x << "' cy= '" << center.y << "' rx= '" << size.x << "' ry= '" << size.y 
		<< "' stroke-width= '1' fill = 'white' stroke= '" << STR_COLOR_LIST.find(m_currentColor)->second << "' />" << std::endl;
}
