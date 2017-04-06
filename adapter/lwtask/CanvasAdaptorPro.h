#pragma once
#include "ICanvasPro.h"
#include "ModernGraphicsRendererPro.h"

namespace app_pro
{

class CanvasAdaptor : public graphics_lib_pro::ICanvas
{
public:
	CanvasAdaptor(modern_graphics_lib_pro::CModernGraphicsRenderer & renderer);

	void SetColor(uint32_t rgbColor) override;
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y)override;

private:
	modern_graphics_lib_pro::CModernGraphicsRenderer & m_renderer;
	modern_graphics_lib_pro::CRGBAColor m_currentColor;
	int m_x;
	int m_y;
};
}