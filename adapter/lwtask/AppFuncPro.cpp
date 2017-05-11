#include "stdafx.h"
#include "AppFuncPro.h"
#include "RectanglePro.h"
#include "TrianglePro.h"
#include "CanvasPro.h"
#include "ModernGraphicsRendererPro.h"
#include "CanvasAdaptorPro.h"

namespace app_pro
{
void PaintPicture(shape_drawing_lib_pro::CCanvasPainter & painter)
{
	using namespace shape_drawing_lib_pro;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 992111);
	CRectangle rectangle({ 30, 40 }, 18, 24, 101010);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib_pro::CCanvas simpleCanvas;
	shape_drawing_lib_pro::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(std::cout);
	CanvasAdaptor canvasAdaptor(renderer);

	shape_drawing_lib_pro::CCanvasPainter painter(canvasAdaptor);
	PaintPicture(painter);
}
}