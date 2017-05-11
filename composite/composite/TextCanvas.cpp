#include "TextCanvas.h"

TextCanvas::TextCanvas(std::ostream & outStream)
	: m_outStream(outStream)
{
}

TextCanvas::~TextCanvas()
{
}

void TextCanvas::SetLineColor(RGBAColor color)
{
	m_outStream << "Line Color is '" << color << "' now!" << std::endl;
}

void TextCanvas::BeginFill(RGBAColor color)
{
	m_outStream << "Start Filling shape by '" << color << "' color" << std::endl;
}

void TextCanvas::EndFill()
{
	m_outStream << "Stop Filling" << std::endl;
}

void TextCanvas::MoveTo(double x, double y)
{
	m_outStream << "Set pen on ( " << x << ", " << y << " )" << std::endl;
}

void TextCanvas::LineTo(double x, double y)
{
	m_outStream << "Line to ( " << x << ", " << y << " )" << std::endl;
}

void TextCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto radiusX = width / 2.0;
	auto radiusY = height / 2.0;

	auto centreX = left + radiusX;
	auto centreY = top + radiusY;

	m_outStream << "Drawing ellipse when centre = (" << centreX << ", " << centreY 
		<< ") and radiuses = (" << radiusX << ", "<< radiusY << ") " << std::endl;

}