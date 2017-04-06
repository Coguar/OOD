#pragma once
#include "ICanvasDrawablePro.h"

namespace graphics_lib_pro
{
class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3);

	void Draw(ICanvas & canvas)const override;
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;

};
}