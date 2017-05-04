#pragma once
#include "ICanvasDrawablePro.h"

namespace shape_drawing_lib_pro
{
class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point & leftTop, int width, int height, const uint32_t & color);

	void Draw(graphics_lib_pro::ICanvas & canvas)const override;
private:
	Point m_topLeft;
	int m_width;
	int m_height;
	uint32_t m_color;
};
}