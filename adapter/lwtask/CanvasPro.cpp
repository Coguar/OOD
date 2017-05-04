#include "stdafx.h"
#include "CanvasPro.h"

using namespace std;

namespace graphics_lib_pro
{
void CCanvas::SetColor(uint32_t rgbColor)
{
	cout << "#" << hex << setw(6) << setfill('0') << rgbColor << endl;
}
void CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}
void CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}
}