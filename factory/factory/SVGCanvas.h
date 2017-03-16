#pragma once
#include "CanvasInterface.h"
#include <fstream>

class CSVGCanvas :
	public ICanvas
{
public:
	CSVGCanvas(std::ofstream & strm);
	~CSVGCanvas();

	void SetColor(Color color) override;
	void DrawLine(Vec2 const& start, Vec2 const& end) override;
	void DrawEllipse(Vec2 const& center, Vec2 const& size) override;
private:
	Color m_currentColor;
	std::ofstream & m_oStrm;
};

