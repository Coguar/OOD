#include <cstdint>
#include "CommonTypes.h"
#include "TextCanvas.h"
#include "version1.h"

#include <boost/optional.hpp>
#include <memory>
#include <limits>
#include <functional>

using namespace version1;

int main()
{
	TextCanvas canvas(std::cout);
	CSlide slide;
	CStyle rectangleStyle;
	rectangleStyle.Enable(true);
	rectangleStyle.SetColor(0x000055);

	CStyle style1;
	style1.Enable(true);
	style1.SetColor(0x882210);

	CStyle style2;
	style2.Enable(true);
	style2.SetColor(0x001010);

	CRectangle rectangleShape(RectD{ 30, 10, 15, 15 });
	rectangleShape.SetFillStyle(rectangleStyle);
	rectangleShape.SetLineStyle(rectangleStyle);

	CEllipse ellipseShape(RectD{ 40, 35, 20, 30 });
	ellipseShape.SetFillStyle(style2);
	ellipseShape.SetLineStyle(style1);

	CTriangle triangleShape(RectD{ 10, 10, 20, 10 });
	triangleShape.SetLineStyle(style2);

	Composite group;
	group.AddComponent(&ellipseShape);
	group.AddComponent(&triangleShape);

	slide.InsertShape(&rectangleShape);
	slide.InsertShape(&group);
	slide.Draw(canvas);
}
