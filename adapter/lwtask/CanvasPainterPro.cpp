#include "stdafx.h"
#include "CanvasPainterPro.h"

namespace shape_drawing_lib_pro
{
CCanvasPainter::CCanvasPainter(graphics_lib_pro::ICanvas & canvas)
	: m_canvas(canvas)
{
}
void CCanvasPainter::Draw(const ICanvasDrawable & drawable)
{
	drawable.Draw(m_canvas);
}
}