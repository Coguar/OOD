#pragma once
#include "ICanvasDrawablePro.h"

namespace shape_drawing_lib_pro
{
class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3, const uint32_t & color);

	void Draw(graphics_lib_pro::ICanvas & canvas)const override;
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_color;
};
}