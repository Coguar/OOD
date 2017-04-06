#include "stdafx.h"
#include "ModernGraphicsRendererPro.h"

using namespace std;

namespace modern_graphics_lib_pro
{
CRGBAColor::CRGBAColor(float r, float g, float b, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a) 
{
}

CModernGraphicsRenderer::CModernGraphicsRenderer(ostream & strm) : m_out(strm)
{
}

CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

// Ётот метод должен быть вызван в начале рисовани€
void CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << endl;
	m_drawing = true;
}

// ¬ыполн€ет рисование линии
void CModernGraphicsRenderer::DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
{
	if (!m_drawing)
	{
		throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y << endl;
	m_out << boost::format(R"(<color r="%1%" g="%2%" b="%3%" a="%4%" />)") % color.r % color.g % color.b % color.a << endl;
	m_out << "</line>" << endl;
}

// Ётот метод должен быть вызван в конце рисовани€
void CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << endl;
	m_drawing = false;
}
}