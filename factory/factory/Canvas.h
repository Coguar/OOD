#pragma once
#include "CanvasInterface.h"

class CTextCanvas :
	public ICanvas
{
public:
	CTextCanvas();
	~CTextCanvas();

	void SetColor(Color color) override;
	void DrawLine(Vec2 const& start, Vec2 const& end) override;
	void DrawEllipse(Vec2 const& center, Vec2 const& size) override;

private:
	Color m_currentColor;
};

