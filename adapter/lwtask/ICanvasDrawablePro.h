#pragma once
#include "ICanvasPro.h"

namespace graphics_lib_pro
{
struct Point
{
	int x;
	int y;
};
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};
}