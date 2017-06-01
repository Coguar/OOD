#include "CommonTypes.h"
#include "SFMLCanvas.h"
#include "Slide.h"
#include "TypedShapes.h"
#include "Group.h"

#include <boost/optional.hpp>
#include <memory>
#include <limits>
#include <functional>
#include <cstdint>

#include <SFML\Graphics.hpp>

const int DEFAULT_MARGIN = 30;

using namespace sf;

int main()
{
	CSlide slide;
	CStyle redStyle;
	redStyle.Enable(true);
	redStyle.SetColor(0xFF0000);

	CStyle greenStyle;
	greenStyle.Enable(true);
	greenStyle.SetColor(0x00FF00);

	CStyle blueStyle;
	blueStyle.Enable(true);
	blueStyle.SetColor(0x0000FF);

	auto rectangleShape = std::make_shared<CRectangle>(RectD{ 30, 200, 200, 150 });
	rectangleShape->SetFillStyle(redStyle);
	rectangleShape->SetLineStyle(greenStyle);

	auto ellipseShape = std::make_shared<CEllipse>(RectD{ 105, 125, 50, 50 });
	ellipseShape->SetFillStyle(blueStyle);
	ellipseShape->SetLineStyle(greenStyle);

	auto triangleShape = std::make_shared<CTriangle>(RectD{ 30, 50, 200, 150 });
	triangleShape->SetLineStyle(blueStyle);

	auto group = std::make_shared<Group>();
	group->AddShape(ellipseShape);
	group->AddShape(triangleShape);

	slide.AddShape(rectangleShape);
	slide.AddShape(group);
	slide.SetBackgroundColor(0xFFFFFF);

	RenderWindow window(VideoMode(int(slide.GetWidth()) + DEFAULT_MARGIN, int(slide.GetHeight()) + DEFAULT_MARGIN), "Composite");
	SFMLCanvas canvas(window);
	auto bgColor = SFMLCanvas::ConvertUintToRGB(slide.GetBackgroundColor());
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		slide.Draw(canvas);
		window.display();
		window.clear(bgColor);
	}
}
