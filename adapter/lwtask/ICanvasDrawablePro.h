#pragma once
#include "ICanvasPro.h"

namespace shape_drawing_lib_pro
{
struct Point
{
	int x;
	int y;
};
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib_pro::ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};
}