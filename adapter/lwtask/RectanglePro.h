#pragma once
#include "ICanvasDrawablePro.h"

namespace graphics_lib_pro
{
class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point & leftTop, int width, int height);

	void Draw(ICanvas & canvas)const override;
private:
	Point m_topLeft;
	int m_width;
	int m_height;
};
}