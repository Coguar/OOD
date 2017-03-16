// factory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include "Painter.h"
#include "Designer.h"
#include "Canvas.h"
#include "SVGCanvas.h"

int main()
{
	CTextCanvas canvas;
	CPainter painter;
	CDesigner designer;
	CClient client(&designer, &painter);
	client.TurnToDesigner(std::cin);
	client.TurnToPainter(&canvas);

	std::ofstream oStrm(boost::filesystem::unique_path("Image%%%%.svg").string());
	CSVGCanvas svgCanvas(oStrm);
	client.TurnToPainter(&svgCanvas);
    return 0;
}

