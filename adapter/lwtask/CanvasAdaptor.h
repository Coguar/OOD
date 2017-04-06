#pragma once
#include "ICanvas.h"
#include "ModernGraphicsRenderer.h"

namespace app
{
class CanvasAdaptor : public graphics_lib::ICanvas
{
public:
	CanvasAdaptor(modern_graphics_lib::CModernGraphicsRenderer & renderer);
	~CanvasAdaptor();
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;


private:
	modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
	int m_x;
	int m_y;
};
}

