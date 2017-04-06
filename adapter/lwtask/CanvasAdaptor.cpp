#include "stdafx.h"
#include "CanvasAdaptor.h"


namespace app
{
CanvasAdaptor::CanvasAdaptor(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
	, m_x(0)
	, m_y(0)
{
	m_renderer.BeginDraw();
}
CanvasAdaptor::~CanvasAdaptor()
{
	m_renderer.EndDraw();
}
void CanvasAdaptor::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}
void CanvasAdaptor::LineTo(int x, int y)
{
	m_renderer.DrawLine({ m_x, m_y }, { x, y });
	MoveTo(x, y);
}
}