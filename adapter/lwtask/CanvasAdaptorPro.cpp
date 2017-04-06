#include "stdafx.h"
#include "CanvasAdaptorPro.h"
#include "ModernGraphicsRendererPro.h"

using namespace std;

namespace app_pro
{
CanvasAdaptor::CanvasAdaptor(modern_graphics_lib_pro::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
	, m_currentColor(0, 0, 0, 1)
	, m_x(0)
	, m_y(0)
{

}

void CanvasAdaptor::SetColor(uint32_t rgbColor)
{
	auto tempRgbColor = rgbColor;
	m_currentColor.b = ((tempRgbColor) * 0x0000FF) / 256.f;
	m_currentColor.g = ((tempRgbColor >>= 8) * 0x0000FF) / 256.f;
	m_currentColor.r = ((tempRgbColor >>= 8) * 0x0000FF) / 256.f;
}

void CanvasAdaptor::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}
void CanvasAdaptor::LineTo(int x, int y)
{
	m_renderer.BeginDraw();
	m_renderer.DrawLine({ m_x, m_y }, { x, y }, m_currentColor);
	m_renderer.EndDraw();
	MoveTo(x, y);
}
}