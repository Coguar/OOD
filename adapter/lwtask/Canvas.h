#pragma once
#include "ICanvas.h"

namespace graphics_lib
{
// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
};
}