#include "stdafx.h"
#include "CanvasClassAdapter.h"

using namespace std;

namespace app
{
CanvasClassAdaptor::CanvasClassAdaptor(ostream & strm)
	: modern_graphics_lib::CModernGraphicsRenderer(strm)
	, m_x(0)
	, m_y(0)
{
	BeginDraw();
}

CanvasClassAdaptor::~CanvasClassAdaptor()
{
	EndDraw();
}

void CanvasClassAdaptor::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CanvasClassAdaptor::LineTo(int x, int y)
{
	DrawLine({ m_x, m_y }, { x, y });
	MoveTo(x, y);
}
}