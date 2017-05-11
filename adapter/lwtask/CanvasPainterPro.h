#pragma once
#include "ICanvasDrawablePro.h"

namespace shape_drawing_lib_pro
{
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib_pro::ICanvas & canvas);
	void Draw(const ICanvasDrawable & drawable);
private:
	graphics_lib_pro::ICanvas & m_canvas;
};
}