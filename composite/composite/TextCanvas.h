#pragma once
#include "Canvas.h"
#include <iostream>

class TextCanvas :
	public ICanvas
{
public:
	TextCanvas(std::ostream& outStream);
	~TextCanvas();
	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;

private:
	void ShowTextedColor(RGBAColor color);

	std::ostream& m_outStream;
};

