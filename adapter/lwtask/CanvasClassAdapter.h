#pragma once
#include "ModernGraphicsRenderer.h"
#include "ICanvas.h"

namespace app
{

class CanvasClassAdaptor
	: public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CanvasClassAdaptor(std::ostream & strm);
	~CanvasClassAdaptor();
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;

private:
	int m_x;
	int m_y;
};
}